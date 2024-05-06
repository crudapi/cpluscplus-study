#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QPoint>
#include <QPen>
#include <QColor>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent * paintEvent)
    {
        QPainter painter(this);

        QColor color(255,  0,  0);//红
        QPoint start_point(10, 30);
        this->paint(painter, color, start_point);


        QColor color2(0,  255,  0);//绿
        QPoint start_point2(140, 30);
        this->paint(painter, color2, start_point2);

        QColor color3(0,  0,  255);//蓝
        QPoint start_point3(270, 30);
        this->paint(painter, color3, start_point3);

        QColor color4(0,  0, 0);//黑
        QPoint start_point4(400, 30);
        this->paint(painter, color4, start_point4);

        QColor color5(255,  255, 255);//白
        QPoint start_point5(530, 30);
        this->paint(painter, color5, start_point5);
    }

    void paint(QPainter& painter, QColor color, QPoint start_point)
    {
        auto pen = QPen(color, 1);
        painter.setPen(pen);

        int height = 200;
        int width = 100;
        //水平方向 x
        //垂直方向 y
        for (int x = 0; x < width; ++x) {
            for (int y = 0; y < height; ++y) {
                painter.drawPoint(start_point+QPoint(x,y));
            }
        }
    }
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
