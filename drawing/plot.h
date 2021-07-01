#ifndef PLOT_H
#define PLOT_H

#include "canvas.h"

class Plot : public Canvas
{
    Q_OBJECT
public:
    Plot(QWidget *parent);

    QPoint p1,p2;

protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *e);
    virtual void mouseMoveEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    void mouseDoubleClick(QMouseEvent *event);

private:
    bool leftButtonPressed = false;
};

#endif // PLOT_H
