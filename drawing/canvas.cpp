#include <QPainter>
#include <QPoint>
#include <QtMath>
#include <QWheelEvent>

#include <iostream>

#include "canvas.h"
#include "ui_canvas.h"

Canvas::Canvas(QWidget *parent) :
    QWidget(parent),
    t_offset(0),
    U_offset(0),
    ui(new Ui::Canvas)
{
    ui->setupUi(this);
}

Canvas::~Canvas()
{
    delete ui;
}

void Canvas::drawBorder()
{
    QPainter painter(this);
    QColor coordLineColor(255,255,255);

    QPen apen = QPen(coordLineColor);
    apen.setWidth(5);
    painter.setPen(apen);

    painter.drawLine(QLine(margin_left + 1,20,width() - 20 - 1,20));
    painter.drawLine(QLine(margin_left,20,margin_left,height() - margin_bottom));
    painter.drawLine(QLine(margin_left + 1,height() - margin_bottom,width() - 20 - 1,height() - margin_bottom));
    painter.drawLine(QLine(width() - 20,20,width() - 20,height() - margin_bottom));
}

void Canvas::drawGrid()
{
    QPainter painter(this);
    QColor coordLineColor2(255, 255, 255);

    QPen apen2 = QPen(coordLineColor2);
    apen2.setWidth(1);
    apen2.setStyle(Qt::DotLine);
    painter.setPen(apen2);

    for (int i=margin_left; i <= width() - 20; i += 20)
    {
        painter.drawLine(QLine(i,20,i,height() - margin_bottom));
    }

    for (int j=height() - margin_bottom; j >= 20; j -= 20)
    {
        painter.drawLine(QLine(margin_left,j,width() - 20,j));
    }
}

void Canvas::drawMainGrid()
{
    QPainter painter(this);
    QColor coordLineColor3(255, 255, 255);

    QPen apen3 = QPen(coordLineColor3);
    apen3.setWidth(2);
    painter.setPen(apen3);

    for (int i=margin_left; i <= width() - 20; i += 100)
    {
        painter.drawLine(QLine(i,20,i,height() - margin_bottom));
    }

    for (int j=height() - margin_bottom; j >= 20; j -= 100)
    {
        painter.drawLine(QLine(margin_left,j,width() - 20,j));
    }
}

void Canvas::drawAxisText()
{
    QPainter painter(this);
    QColor coordLineColor(255, 255, 255);

    QPen apen = QPen(coordLineColor);
    apen.setWidth(2);
    painter.setPen(apen);

    for (int i=margin_left; i <= width() - 20; i += 100)
    {
        painter.setFont(QFont("helvetica", 10));
        double t = (double)(i - margin_left) / (double)(width() - margin_left - 20) * t_max;
        painter.drawText(QPoint(i,height()), QString("%1").arg(t, 0, 'f', 4));
    }

    for (int j = height() - margin_bottom; j >= 20; j -= 100)
    {
        painter.setFont(QFont("helvetica", 10));
        double U = (double)(-j + height() - margin_bottom) / (double)(height() - margin_bottom - 20) * U_max;
        painter.drawText(QPoint(0,j), QString("%1").arg(U, 0, 'f', 4));
    }
    painter.setFont(QFont("helvetica", 10));
    painter.drawText(QPoint(400,10), "График чего-то там");
    painter.drawText(QPoint(400,1030), "Ось x");
}

void Canvas::drawBackground()
{
    QPainter painter(this);
    painter.fillRect(0,0,width(),height(), QBrush(QColor(0,0,0)));
}

void Canvas::paintEvent(QPaintEvent *)
{
    drawBackground();
    drawBorder();
    drawGrid();
    drawMainGrid();
    drawAxisText();

    QPainter painter(this);
    painter.setPen(QPen(QColor(255,50,50), 2));

    double w = 2.0 * M_PI * 50.0;
    double A = 311;

    for (int x = margin_left + 1; x <=(width() - 20); x ++)
    {
        double t1 = (double)(x - 1 - margin_left)/(double)(width() - margin_left - 20) * t_max;
        double t2 = (double)(x - margin_left)/(double)(width() - margin_left - 20) * t_max;
        double U1 = A * sin(w * (t1 + t_offset)) + U_offset;
        double U2 = A * sin(w * (t2 + t_offset)) + U_offset;
        //std::cout << U << std::endl;

        int y1 = (double)(-U1 / U_max * (double)(height() - margin_bottom - 20) + height() - margin_bottom - pixel_offset);
        int y2 = (double)(-U2 / U_max * (double)(height() - margin_bottom - 20) + height() - margin_bottom - pixel_offset);
        if (y1 < 20) y1 = 20;
        if (y1 > height() - margin_bottom) y1 = height() - margin_bottom;
        if (y2 < 20) y2 = 20;
        if (y2 > height() - margin_bottom) y2 = height() - margin_bottom;

        painter.drawLine(x-1,y1,x,y2);
    }

}

void Canvas::wheelEvent(QWheelEvent *event)
{
    double t_max_new = t_max * (-event->angleDelta().y() / 1000.0 + 1.0);
    double delta_t = (double)(event->position().x() - margin_left)/(double)(width() - margin_left - 20) * t_max_new -
            (double)(event->position().x() - margin_left)/(double)(width() - margin_left - 20) * t_max;
    t_offset -= delta_t;
    t_max = t_max_new;

    double U_n = (double)(-event->position().y() - pixel_offset + height() - margin_bottom) / (double)(height() - margin_bottom - 20) * U_max;
    double U_max_new = U_max * (-event->angleDelta().y() / 1000.0 + 1.0);
    double delta_U = U_n / U_max_new * U_max - U_n;
    U_max = U_max_new;
    U_offset -= delta_U;

    repaint();
}


//void timerEvent(QTimerEvent *event)
//{

//}
