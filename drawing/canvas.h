#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>

namespace Ui {
class Canvas;
}

class Canvas : public QWidget
{
    Q_OBJECT

public:
    explicit Canvas(QWidget *parent = nullptr);
    ~Canvas();
    void paintEvent(QPaintEvent *);

    void reset();

    int margin_bottom;
    int margin_left;

    double t_max;
    double U_max;

    double t_max_v;
    double U_max_v;
    double t_offset;
    double U_offset;

    double gridStep;

private:
    Ui::Canvas *ui;
    QPoint p1,p2;
    bool leftButtonPressed = false;

    void wheelEvent(QWheelEvent *event);

    void drawBackground();
    void drawBorder();
    void drawGrid();
    void drawMainGrid();
    void drawAxisText();

protected:
    virtual void mouseDoubleClickEvent(QMouseEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *e);
    virtual void mouseMoveEvent(QMouseEvent *event);

//    void timerEvent(QTimerEvent *event);
};

#endif // CANVAS_H
