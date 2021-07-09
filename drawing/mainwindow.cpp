#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <math.h>
#include "canvas.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->widget->t_max = 0.1;
    ui->widget->U_max = 800.0;
    ui->widget->margin_bottom = 40;
    ui->widget->margin_left = 100;
    ui->widget->reset();
}

MainWindow::~MainWindow()
{
    delete ui;
}


