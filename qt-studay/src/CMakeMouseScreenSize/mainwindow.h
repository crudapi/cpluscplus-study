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
public:
        void paintEvent(QPaintEvent* painter1) override;
        void mouseMoveEvent(QMouseEvent* event);
        void drawSize(void);
        void drawMouse();
        void keyPressEvent(QKeyEvent* event) override;
private:
    Ui::MainWindow *ui;
    QPoint m_mousePos;
};

#endif // MAINWINDOW_H
