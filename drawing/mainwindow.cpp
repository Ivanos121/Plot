#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <math.h>
#include "canvas.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , t(0.0)
{
    ui->setupUi(this);
    ui->widget->t_max = 0.1;
    ui->widget->U_max = 800.0;
    ui->widget->margin_bottom = 40;
    ui->widget->margin_left = 100;
    ui->widget->reset();

    ui->widget->addDataLine(QColor(255,0,0), 0);
    ui->widget->addDataLine(QColor(0,255,0), 200.0);

    connect(&timer, &QTimer::timeout, this, &MainWindow::on_timer_timeout);
    timer.start(100);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_timer_timeout()
{
    double w = 2.0 * M_PI * 50.0;
    double A = 311;
    if (t >= 0.1)
    {
        A *= 100;
    }
    ui->widget->addPoint(0, t, A * sin(w * t));
    ui->widget->addPoint(1, t, A * cos(w * t));
    t += 1.0 / 200.0 * ui->widget->t_max;
}

