#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "snake.h"
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    // QWidget interface
protected:
    void keyPressEvent(QKeyEvent *event);

private slots:
    void moveSlot();
    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event);
    void move(int key);

private:
    Ui::MainWindow *ui;
    Snake m_snake;
    int m_pictureSize = 200;
    int m_key = -1;
    QTimer m_timer;
};
#endif // MAINWINDOW_H
