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

        QColor color(255,  255,   255);//RGB三个分量都是255，三种颜色组成白色
        auto pen = QPen(color, 1);
        painter.setPen(pen);

        QPoint start_point(20, 30);
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
