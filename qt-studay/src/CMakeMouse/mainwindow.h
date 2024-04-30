#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QColor>
#include <QString>
#include <QKeyEvent>
#include <iostream>
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};

public:
    //绘制窗口内容，包括窗口大小和鼠标位置
    void paintEvent(QPaintEvent* painter1) override;
    //鼠标移动事件，获取鼠标位置
    void mouseMoveEvent(QMouseEvent* event);
    //绘制窗口大小，宽度和高度
    void drawSize(void);
    //绘制鼠标位置，位置由鼠标移动事件获得
    void drawMouse();
    //按F12在全屏和正常模式之间切换
    void keyPressEvent(QKeyEvent* event) override;
private:
    Ui::MainWindow *ui;
    //存放鼠标移动的当前位置，在鼠标移动事件中修改该位置
    QPoint m_mousePos;
};

#endif // MAINWINDOW_H
