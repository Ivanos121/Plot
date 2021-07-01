#include "plot.h"
#include <QCursor>
#include <QPainter>
#include <QMouseEvent>



Plot::Plot(QWidget *parent) : Canvas(parent)
{
   // setMouseTracking(true);

}

//определение нажатой клавиши мыши
void Plot::mousePressEvent(QMouseEvent *e)
{
    if (e->buttons() & Qt::LeftButton)
    {
        setCursor(Qt::CrossCursor);
        p1=e->pos();
        p2 = p1;
        leftButtonPressed = true;
    }
}

//реакция на нажатую клавишу
void Plot::mouseReleaseEvent(QMouseEvent *e)
{
    QPainter painter(this);
    QColor coordLineColor2(255, 255, 255);

    QPen apen2 = QPen(coordLineColor2);
    apen2.setWidthF(0.5);
    apen2.setStyle(Qt::DotLine);
    painter.setPen(apen2);



    setCursor(Qt::ArrowCursor);

    double w = abs(p1.x()-p2.x());
    double h = abs(p1.y()-p2.y());

    if (w > 50 && h > 50) {
         if (e->button() == Qt::LeftButton)
         {

             if ((p2.x() - p1.x() < 0) &&
                 (p2.y() - p1.y() < 0))
             {
                // rescaleAxes(true);
                // replot();
                 repaint();
             } else {
                 double deltax = 0.;
                 double deltay = 0.;
                 deltax = w/(width()-20-margin_left);
                 deltay = h/(height()-20-margin_bottom);

                 painter.drawRect(deltax,deltay,(p1.x()+p2.x())/2.0,(p1.y()+p2.y())/2.0);
             }
         }
     }
    leftButtonPressed = false;
    repaint();
}


void Plot::mouseMoveEvent(QMouseEvent *e)
{
    if (e->buttons() & Qt::LeftButton)
    {
        p2 = e->pos();
        repaint();
    }
}

//отрисовка рамки выделения
void Plot::paintEvent(QPaintEvent *event)
{
    Canvas::paintEvent(event);
    if (leftButtonPressed)
    {
        QPainter painter(this);
        QPen pen(Qt::white, 1, Qt::DotLine);
        painter.setPen(pen);
        painter.drawRect(p1.x(),p1.y(),p2.x() - p1.x(),p2.y() - p1.y());
    }
}

//восстановление первичного масштаба
void Plot::mouseDoubleClick(QMouseEvent *event)
{
//    ui->Plot->xAxis->setRange(ui->Plot->graph(0)->data()->firstKey(), ui->customPlot->graph(0)->data()->firstKey()+3600);
//    ui->Plot->xAxis->setTickStep(3600/5);
//    ui->Plot->replot();
//    isScaled = false;
}
