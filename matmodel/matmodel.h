#ifndef MATMODEL_H
#define MATMODEL_H

#include <QtWidgets/QMainWindow>
#include<QPushButton>
#include "ui_matmodel.h"
#include"qcustomplot.h"
#include<ctime>
class wave_equation
{
private:
	QVector<QVector<double>>u_sol;
	QVector<double>x_vec;
	QVector<double>t_vec;
	QVector<double>analit_sol;
	int n;
	int m;
	double h;
	double t;
	double l;
protected:
	double fi_x_(double x)
	{
		return x*(x - 2);
	}
	void init()
	{
		u_sol.resize(m);
		for (auto &x : u_sol)
		{
			x.resize(n);
		}
		x_vec.resize(n);
		t_vec.resize(n);
		analit_sol.resize(n);
		for (int i = 0; i < n; i++)
		{
			x_vec[i] = h*i;
		}
		for (int i = 0; i < n; i++)
		{
			t_vec[i] = t*i;
		}
	}
public:
	wave_equation() = default;
	wave_equation(const wave_equation&) = default;
	void set_m(int M)
	{
		m = M;
	}
	void set_n(int N)
	{
		n = N;
	}
	void set_l(double bl)
	{
		l = bl;
	}
	void set_h(double bh)
	{
		h = bh;
	}
	void set_t(double bt)
	{
		t = bt;
		
	}
	QVector<QVector<double>> & get_sol()
	{
		return u_sol;
	}
	QVector<double>& get_x_vec()
	{
		return x_vec;
	}
	QVector<double>& get_t_vec()
	{
		return t_vec;
	}
	QVector<double>&get_anal_sol()
	{
		return analit_sol;
	}
	void sol_anal(double bt,int v)
	{
		double sum = 0;
		//analit_sol[0] = 0;
		for (int i = 0; i < n; i++)
		{
			for (int j = 1; j < v; j++)
			{
				sum += (16 / (j*j*j*3.14*3.14*3.14))*(cos(j*3.15) - 1)*cos(j*3.15 * 3 * bt / 2)*sin(j*3.14*i*h / 2);
			}
			analit_sol[i] = sum;
			sum = 0;
		}
		
	}
	void solution()
	{
		init();
		double L = 3 * t / h;
		for (int i = 0; i < m; i++)
		{
			u_sol[i][0] = 0;
			u_sol[i][n - 1] = 0;
		}
		for (int i = 1; i < n - 1; i++)
		{
			u_sol[0][i] = fi_x_(h*i);
			u_sol[1][i] = fi_x_(h*i);
		}
		for (int i = 1; i < m - 1; i++)
		{
			for (int j = 1; j < n - 1; j++)
			{
				u_sol[i + 1][j] = 2 * (1 - L*L)*u_sol[i][j] + L*L*(u_sol[i][j + 1] + u_sol[i][j - 1]) - u_sol[i - 1][j];
			}
		}
	}
	~wave_equation() {}
};
class thermal_equation
{
private:
	QVector<QVector<double>>u_sol;
	QVector<double>x_vec;
	QVector<double>t_vec;
	QVector<double>analit_sol;
	double l;
	double dx;
	double dt;
	int n;
	int m;
protected:
	void init()
	{
		u_sol.resize(m);
		for (auto& x : u_sol)
			x.resize(n);
		x_vec.resize(n);
		t_vec.resize(m);
		for (int i = 0; i < n; i++)
		{
			x_vec[i] = dx*i;
		}
		for (int i = 0; i < m; i++)
		{
			t_vec[i] = dt*i;
		}
		analit_sol.resize(n);
	}
	double _f_x(double x)
	{
		if (0 <= x&&x <= 3)
		{
			return x*x / 3;
		}
		if (3 < x&&x <= l)
		{
			return 6 - x;
		}
	}
public:
	thermal_equation() = default;
	thermal_equation(const thermal_equation&) = default;
	void set_l(double bl)
	{
		l = bl;
	}
	void set_n(int nb)
	{
		n = nb+1;
	}
	void set_m(int mb)
	{
		m = mb+1;
	}
	void set_dx(double h)
	{
		dx = h;
	}
	void set_dt(double tay)
	{
		dt = tay;
	}
	QVector<QVector<double>>& get_u_sol()
	{
		return u_sol;
	}
	QVector<double>& get_x_vec()
	{
		return x_vec;
	}
	QVector<double>& get_t_vec()
	{
		return t_vec;
	}
	QVector<double>& get_anal()
	{
		return analit_sol;
	}
	void solution()
	{
		init();
		double L = 16.0*dt / (dx*dx);
		for (int i = 1; i < n - 1; i++)
		{
			u_sol[0][i] = _f_x(dx*i);
		}
		for (int i = 0; i < m; i++)
		{
			u_sol[i][0] = 0;
			u_sol[i][n - 1] = 0;
		}
		for (int i = 0; i < m - 1; i++)
		{
			for (int j = 1; j < n - 1; j++)
			{
				u_sol[i + 1][j] = L*(u_sol[i][j + 1] - 2 * u_sol[i][j] + u_sol[i][j - 1]) + u_sol[i][j];
			}
		}
	}
	void an_sol(double tb,int v)
	{
		double sum = 0;
		for (int i = 0; i < n; i++)
		{
			for (int j = 1; j < v; j++)
			{
				sum += 36 / (3.14*3.14*j*j)*sin(3.14*j / 2)*exp(((-3.14*3.14*j*j * 16) / 36)*tb)*sin(3.14*j*x_vec[i] / 6);
			}
			analit_sol[i] = sum;
			sum = 0;
		}
	}
		
	~thermal_equation() {}
};

class matmodel : public QWidget
{
	Q_OBJECT
public:
	matmodel(QWidget *parent = nullptr):wave(nullptr),thermal(nullptr)
	{
		customPlot= new QCustomPlot(this);
		customPlot->move(10, 10);
		customPlot->resize(750, 550);
		customPlot->xAxis->setLabel("x");
		customPlot->yAxis->setLabel("U(x,t)");

		btn1 = new QPushButton("Run");
		btn1->setParent(this);
		btn1->move(800, 550);
		btn1->setMinimumWidth(100);
		QObject::connect(btn1, SIGNAL(clicked()), this, SLOT(slotBtn1()));

		btn_clear = new QPushButton("Clear");
		btn_clear->setParent(this);
		btn_clear->move(950, 550);
		btn_clear->setMinimumWidth(100);
		QObject::connect(btn_clear, SIGNAL(clicked()), this, SLOT(slotBtn_clear()));

		cmbox = new QComboBox(this);
		QStringList lst;
		lst << "-"<<"wave equation" << "thermal equation";
		cmbox->addItems(lst);
		cmbox->move(800, 50);

		l_n = new QLabel(this);
		l_n->setText("Steps n: ");
		l_n->move(800, 150);
		_n = new QLineEdit(this);
		_n->move(900, 150);

		l_m = new QLabel(this);
		l_m->setText("Time m:");
		l_m->move(800, 200);
		_m = new QLineEdit(this);
		_m->move(900, 200);

		l_l = new QLabel(this);
		l_l->setText(" l: ");
		l_l->move(800, 250);
		_l = new QLineEdit(this);
		_l->move(900, 250);
		
		l_dx = new QLabel(this);
		l_dx->setText("dx: ");
		l_dx->move(800, 300);
		_dx = new QLineEdit(this);
		_dx->move(900, 300);

		l_dt = new QLabel(this);
		l_dt->setText("dt: ");
		l_dt->move(800, 350);
		_dt = new QLineEdit(this);
		_dt->move(900, 350);

		l_anal_t = new QLabel(this);
		l_anal_t->setText("Step time: ");
		l_anal_t->move(800, 400);
		_an_t = new QSpinBox(this);
		_an_t->move(900, 400);
		_an_t->setMinimumWidth(50);
		_an_t->setRange(0, 0);
		QObject::connect(_an_t, SIGNAL(valueChanged(int)), this, SLOT(slotAnalit(int)));

		counter = new QSpinBox(this);
		counter->setMinimumWidth(50);
		counter->move(900, 450);
		counter->setRange(0, 0);
		QObject::connect(counter, SIGNAL(valueChanged(int)), this, SLOT(slotCounter(int)));
	}
	~matmodel() {};
	public slots:
	void slotBtn1()
	{
		if (cmbox->currentText() == "wave equation")
		{
			_n->setEnabled(false);
			_m->setEnabled(false);
			_l->setEnabled(false);
			_dx->setEnabled(false);
			_dt->setEnabled(false);
			cmbox->setEnabled(false);
			wave = new wave_equation();
			wave->set_n(_n->text().toInt());
			wave->set_m(_m->text().toDouble());
			wave->set_l(_l->text().toDouble());
			wave->set_h(_dx->text().toDouble());
			wave->set_t(_dt->text().toDouble());
			//проверка условий куранта
			wave->solution();
			wave->sol_anal(wave->get_t_vec()[0],500);
			counter->setRange(0, _m->text().toDouble() - 2 * _dt->text().toDouble());
			_an_t->setRange(0, _m->text().toDouble() - 2 * _dt->text().toDouble());
			customPlot->addGraph();
			customPlot->addGraph();
			customPlot->xAxis->setRange(0, _l->text().toInt() + 1);
			customPlot->yAxis->setRange(-2.5, 3);
			customPlot->graph(0)->setPen(QColor(50, 50, 50, 255));
			customPlot->graph(0)->setLineStyle(QCPGraph::lsNone);
			customPlot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 4));
			customPlot->graph(0)->setData(wave->get_x_vec(), wave->get_sol()[0]);
			customPlot->graph(1)->setPen(QColor(250, 0, 0, 255));
			customPlot->graph(1)->setLineStyle(QCPGraph::lsNone);
			customPlot->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 4));
			customPlot->graph(1)->setData(wave->get_x_vec(), wave->get_anal_sol());
			customPlot->replot();

		}
		if (cmbox->currentText() == "thermal equation")
		{
			_l->setText("6");
			_n->setEnabled(false);
			_m->setEnabled(false);
			_l->setEnabled(false);
			_dx->setEnabled(false);
			_dt->setEnabled(false);
			cmbox->setEnabled(false);
			thermal = new thermal_equation;
			thermal->set_n(_n->text().toInt());
			thermal->set_m(_m->text().toDouble());
			thermal->set_l(_l->text().toDouble());
			thermal->set_dx(_dx->text().toDouble());
			thermal->set_dt(_dt->text().toDouble());
			//проверка условий куранта
			thermal->solution();
			thermal->an_sol(thermal->get_t_vec()[0],500);
			_an_t->setRange(0, _m->text().toDouble() - 2 * _dt->text().toDouble());
			counter->setRange(0, _m->text().toDouble() - 2 * _dt->text().toDouble());
			customPlot->addGraph();
			customPlot->addGraph();
			customPlot->xAxis->setRange(0, _l->text().toInt() + 1);
			customPlot->yAxis->setRange(0, 5);
			customPlot->graph(0)->setPen(QColor(50, 50, 50, 255));
			customPlot->graph(0)->setData(thermal->get_x_vec(), thermal->get_u_sol()[0]);
			customPlot->graph(1)->setPen(QColor(250, 0, 0, 255));
			customPlot->graph(1)->setData(thermal->get_x_vec(), thermal->get_anal());
			customPlot->replot();
		}
	}
	void slotBtn_clear()
	{
		counter->setValue(0);
		_an_t->setValue(0);
		counter->setRange(0, 0);
		_an_t->setRange(0, 0);
		if (wave != nullptr)
			delete wave;
		if (thermal != nullptr)
			delete thermal;
		thermal = nullptr;
		wave = nullptr;
		_n->clear();
		_m->clear();
		_l->clear();
		_dx->clear();
		_dt->clear();
		_n->setEnabled(true);
		_m->setEnabled(true);
		_l->setEnabled(true);
		_dx->setEnabled(true);
		_dt->setEnabled(true);
		cmbox->setEnabled(true);
		customPlot->clearGraphs();
		customPlot->replot();
	}
	void slotCounter(int a)
	{
		if (cmbox->currentText() == "wave equation"&wave!=nullptr)
		{
			customPlot->graph(0)->setData(wave->get_x_vec(), wave->get_sol()[a]);
			customPlot->replot();
		}
		if (cmbox->currentText() == "thermal equation"&thermal != nullptr)
		{
			customPlot->graph(0)->setData(thermal->get_x_vec(), thermal->get_u_sol()[a]);
			customPlot->replot();
		}

	}
	void slotAnalit(int a)
	{
		if (cmbox->currentText() == "wave equation")
		{
			wave->sol_anal(wave->get_t_vec()[a], 500);
			customPlot->graph(1)->setData(wave->get_x_vec(), wave->get_anal_sol());
			customPlot->replot();
		}
		if (cmbox->currentText() == "thermal equation")
		{
			thermal->an_sol(thermal->get_t_vec()[a], 500);
			customPlot->graph(1)->setData(thermal->get_x_vec(), thermal->get_anal());
			customPlot->replot();
		}

	}
private:
	QCustomPlot* customPlot;
	QPushButton* btn1;
	QPushButton* btn_clear;
	QComboBox* cmbox;

	QLabel* moment_to_time;
	QLabel *l_n;
	QLineEdit *_n;
	QLabel *l_m;
	QLineEdit *_m;
	QLabel *l_l;
	QLineEdit *_l;
	QLabel *l_dx;
	QLabel *l_dt;
	QLineEdit *_dx,*_dt;
	QLabel *l_anal_t;
	QSpinBox *_an_t;

	QSpinBox *counter;
	wave_equation *wave;
	thermal_equation *thermal;
};

#endif // MATMODEL_H
