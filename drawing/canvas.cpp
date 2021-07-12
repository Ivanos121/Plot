#include <QPainter>
#include <QPoint>
#include <QtMath>
#include <QWheelEvent>
#include <QDebug>

#include <iostream>

#include "canvas.h"
#include "ui_canvas.h"

Canvas::Canvas(QWidget *parent) :
    QWidget(parent),
    t_offset(0),
    U_offset(0),
    gridStep(20),
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
    apen.setWidth(4);
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
    apen2.setWidthF(0.5);
    apen2.setStyle(Qt::DotLine);
    painter.setPen(apen2);

    for (double i=margin_left - gridStep * 5.0; i <= width() - 20 + gridStep * 5.0; i += gridStep)
    {
        double offset = t_offset / t_max_v * (width() -20 - margin_left);
        while (offset >= gridStep * 5.0)
        {
            offset -= gridStep * 5.0;
        }
        while (offset <= -gridStep * 5.0)
        {
            offset += gridStep * 5.0;
        }
        if (!(((i - offset) <= margin_left) || ((i - offset) >= (width() -20))))
        {
           painter.drawLine(i - offset,20,i - offset,height() - margin_bottom);
        }
    }

    for (double j=height() - margin_bottom + gridStep * 5.0; j >= 20 - gridStep * 5.0; j -= gridStep)
    {
        double offset = U_offset / U_max_v * (height() -20 - margin_bottom);
        while (offset >= gridStep * 5.0)
        {
            offset -= gridStep * 5.0;
        }
        while (offset <= -gridStep * 5.0)
        {
            offset += gridStep * 5.0;
        }
        if (!(((j - offset) <= 20) || ((j - offset) >= (height() - margin_bottom))))
        {
            painter.drawLine(QLine(margin_left,j-offset,width() - 20,j-offset));
        }
    }
}

void Canvas::drawMainGrid()
{
    QPainter painter(this);
    QColor coordLineColor3(255, 255, 255);

    QPen apen3 = QPen(coordLineColor3);
    apen3.setWidthF(0.5);
    painter.setPen(apen3);

    for (double i=margin_left; i <= width() - 20 + gridStep * 5.0; i += gridStep * 5.0)
    {
        double offset = t_offset / t_max_v * (width() -20 - margin_left);
        while (offset >= gridStep * 5.0)
        {
            offset -= gridStep * 5.0;
        }
        while (offset <= -gridStep * 5.0)
        {
            offset += gridStep * 5.0;
        }
        if (!(((i - offset) <= margin_left) || ((i - offset) >= (width() -20))))
        {
           painter.drawLine(i - offset,20,i - offset,height() - margin_bottom);
        }
    }

    for (double j=height() - margin_bottom; j >= 20 - gridStep * 5.0; j -= gridStep * 5.0)
    {
        double offset = U_offset / U_max_v * (height() -20 - margin_bottom);
        while (offset >= gridStep * 5.0)
        {
            offset -= gridStep * 5.0;
        }
        while (offset <= -gridStep * 5.0)
        {
            offset += gridStep * 5.0;
        }
        if (!(((j - offset) <= 20) || ((j - offset) >= (height() - margin_bottom))))
        {
            painter.drawLine(QLine(margin_left,j-offset,width() - 20,j-offset));
        }
    }
}

void Canvas::drawAxisText()
{
    QPainter painter(this);
    QColor coordLineColor(255, 255, 255);

    QPen apen = QPen(coordLineColor);
    apen.setWidth(2);
    painter.setPen(apen);

    for (double i=margin_left; i <= width() - 20 + gridStep * 5.0; i += gridStep * 5.0)
    {
        double offset = t_offset / t_max_v * (width() -20 - margin_left);
        while (offset >= gridStep * 5.0)
        {
            offset -= gridStep * 5.0;
        }
        while (offset <= -gridStep * 5.0)
        {
            offset += gridStep * 5.0;
        }
        if (!(((i - offset) <= margin_left) || ((i - offset) >= (width() -20))))
        {
           double t = (double)(i - margin_left) / (double)(width() - margin_left - 20) * t_max_v + t_offset;
           painter.drawText(QPoint(i -20 -offset,height()-15), QString("%1").arg(t, 0, 'f', 4));
        }
    }

    for (double j=height() - margin_bottom; j >= 20 - gridStep * 5.0; j -= gridStep * 5.0)
    {
        double offset = U_offset / U_max_v * (height() -20 - margin_bottom);
        while (offset >= gridStep * 5.0)
        {
            offset -= gridStep * 5.0;
        }
        while (offset <= -gridStep * 5.0)
        {
            offset += gridStep * 5.0;
        }
        if (!(((j - offset) <= 20) || ((j - offset) >= (height() - margin_bottom))))
        {
            double U = (double)(-j + height() - margin_bottom) / (double)(height() - margin_bottom - 20) * U_max_v - U_offset;
            painter.drawText(QPoint(20,j+5-offset), QString("%1").arg(U, 0, 'f', 4));
        }
    }

    painter.setFont(QFont("helvetica", 10));
    painter.drawText(QPoint(400,10), "График чего-то там");

}

void Canvas::drawBackground()
{
    QPainter painter(this);

    QLinearGradient linearGrad;
    linearGrad.setColorAt( 0 , QColor(80, 80, 80));
    linearGrad.setColorAt( 1 , QColor(50, 50, 50));
    painter.fillRect(0, 0, width(), height(), linearGrad);
}

void Canvas::paintEvent(QPaintEvent *)
{
    drawBackground();
    drawGrid();
    drawMainGrid();
    drawAxisText();

    QPainter painter(this);

    for (DataLine& line : dataLines)
    {
        painter.setPen(QPen(QColor(line.color), 2));

        for (int i=0 , n=line.data.size(); i < n - 1 - 1; i++)
        {
            double t1 = line.data[i].t;
            double t2 = line.data[i + 1].t;

            int x1 = (t1 - t_offset) / t_max_v * (width() -20 - margin_left) + margin_left;
            int x2 = (t2 - t_offset) / t_max_v * (width() -20 - margin_left) + margin_left;

            if ((x1 < margin_left) && (x2 < margin_left)) continue;
            if ((x1 > (width() - 20)) && (x2 > (width() - 20))) continue;

            double U1 = line.data[i].U + U_offset + line.lineOffset;
            double U2 = line.data[i + 1].U + U_offset + line.lineOffset;

            int y1 = (double)(-U1 / U_max_v * (double)(height() - margin_bottom - 20) + height() - margin_bottom );
            int y2 = (double)(-U2 / U_max_v * (double)(height() - margin_bottom - 20) + height() - margin_bottom );

            if ((y1 < 20) && (y2 < 20)) continue;
            if ((y1 > height() -margin_bottom) && (y2 > height() -margin_bottom)) continue;

            if (x1 < margin_left)
            {
                double k = (double)(y2 - y1) / (double)(x2 - x1);
                double b = y1 - k * x1;
                x1 = margin_left;
                y1 = k * x1 + b;
            }

            if (x2 > width() -20)
            {
                double k = (double)(y2 - y1) / (double)(x2 - x1);
                double b = y1 - k * x1;
                x2 = width() - 20;
                y2 = k * x2 + b;
            }

            if (y1 < 20)
            {
                double k = (double)(y2 - y1) / (double)(x2 - x1);
                double b = y1 - k * x1;
                x1 = (20.0 - b) / k;
                y1 = 20;
            }
            if (y1 > height() - margin_bottom)
            {
                double k = (double)(y2 - y1) / (double)(x2 - x1);
                double b = y1 - k * x1;
                x1 = (height() - margin_bottom - b) / k;
                y1 = height() - margin_bottom;
            }
            if (y2 < 20)
            {
                double k = (double)(y2 - y1) / (double)(x2 - x1);
                double b = y2 - k * x2;
                x2 = (20.0 - b) / k;
                y2 = 20;
            }
            if (y2 > height() - margin_bottom)
            {
                double k = (double)(y2 - y1) / (double)(x2 - x1);
                double b = y2 - k * x2;
                x2 = (height() - margin_bottom - b) / k;
                y2 = height() - margin_bottom;
            }

            if (x1 < margin_left) continue;
            if (x2 > width() -20) continue;

            painter.drawLine(x1,y1,x2,y2);
        }
    }

    if (leftButtonPressed)
    {
        QPen pen(Qt::white, 1, Qt::DotLine);
        painter.setPen(pen);
        painter.drawRect(p1.x(),p1.y(),p2.x() - p1.x(),p2.y() - p1.y());
    }

    drawBorder();
}

void Canvas::wheelEvent(QWheelEvent *event)
{
    double t_max_new = t_max_v * (-event->angleDelta().y() / 2000.0 + 1.0);
    double delta_t = (double)(event->position().x() - margin_left)/(double)(width() - margin_left - 20) * t_max_new -
            (double)(event->position().x() - margin_left)/(double)(width() - margin_left - 20) * t_max_v;
    t_offset -= delta_t;
    t_max_v = t_max_new;

    double U_max_new = U_max_v * (-event->angleDelta().y() / 2000.0 + 1.0);
    double delta_U = (double)(-event->position().y() + height() - margin_bottom) / (double)(height() - margin_bottom - 20) *
            (U_max_new - U_max_v);

    U_max_v = U_max_new;
    U_offset += delta_U;

    gridStep /= (-event->angleDelta().y() / 2000.0 + 1.0);
    if (gridStep > 40.0)
    {
        gridStep /= 2.0;
    }
    if (gridStep < 10.0)
    {
        gridStep *= 2.0;
    }

    repaint();
}

void Canvas::mouseDoubleClickEvent(QMouseEvent *)
{
    reset();
    repaint();
}

void Canvas::reset()
{
    t_offset = 0.0;
    U_offset = 0.0;
    gridStep = 20.0;
    t_max_v = t_max;
    U_max_v = U_max;
}

void Canvas::mousePressEvent(QMouseEvent *e)
{
    if (e->buttons() & Qt::LeftButton)
    {
        setCursor(Qt::CrossCursor);
        p1=e->pos();
        p2 = p1;
        leftButtonPressed = true;
    }
}

void Canvas::mouseReleaseEvent(QMouseEvent *)
{
    if ((p1.x() == p2.x() || (p1.y() == p2.y())))
    {
        return;
    }

    if (p1.x() > p2.x())
    {
        int temp = p1.x();
        p1.setX(p2.x());
        p2.setX(temp);
    }

    if (p1.y() > p2.y())
    {
        int temp = p1.y();
        p1.setY(p2.y());
        p2.setY(temp);
    }

    leftButtonPressed = false;
    double t1 = (double)(p1.x() - margin_left)/(double)(width() - margin_left - 20) * t_max_v;
    t_offset += t1;
    t_max_v *= (p2.x() - p1.x()) / (double)(width() - margin_left - 20);

    double U1 = (double)(-p2.y() + height() - margin_bottom) / (double)(height() - margin_bottom - 20) * U_max_v;
    U_offset -= U1;
    U_max_v *= (p2.y() - p1.y()) / (double)(height() - margin_bottom - 20);
    repaint();
}

void Canvas::mouseMoveEvent(QMouseEvent *e)
{
    if (e->buttons() & Qt::LeftButton)
    {
        p2 = e->pos();
        repaint();
    }
}

void Canvas::addPoint(size_t lineNumber, double t, double U)
{
    if (lineNumber >= dataLines.size())
    {
        return;
    }

    dataLines[lineNumber].data.push_back(DataPoint(t, U));

    double t_m = t_max_v + t_offset;
    if (t > t_m)
    {
        t_offset = t - t_max_v;
    }

    if ((U + dataLines[lineNumber].lineOffset) > (U_max_v - U_offset))
    {
        U_max_v = U + dataLines[lineNumber].lineOffset + U_offset;
    }

    if ((U + dataLines[lineNumber].lineOffset) < (-U_offset))
    {
        double newOffset = -(U + dataLines[lineNumber].lineOffset);
        U_max_v = U_max_v - U_offset + newOffset;
        U_offset = newOffset;
    }

    repaint();
}

void Canvas::addDataLine(QColor color, double lineOffset)
{
    DataLine newLine(color, lineOffset);
    dataLines.push_back(newLine);
}
