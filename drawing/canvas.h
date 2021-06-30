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

    int margin_bottom;
    int margin_left;

    int pixel_offset = 500;

    double t_max;
    double U_max;
    double t_offset;
    double U_offset;

private:
    Ui::Canvas *ui;

    void paintEvent(QPaintEvent *);
    void wheelEvent(QWheelEvent *event);

    void drawBackground();
    void drawBorder();
    void drawGrid();
    void drawMainGrid();
    void drawAxisText();

//    void timerEvent(QTimerEvent *event);
};

#endif // CANVAS_H
