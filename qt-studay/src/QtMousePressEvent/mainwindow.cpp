#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMouseEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::mousePressEvent(QMouseEvent *event)
{
    ui->label_mouse_position->move(event->pos());//鼠标点击哪里，label就在哪里显示
    auto pos = event->pos();//获得鼠标点击的位置
    QString text = QString("mouse postion (%1, %2)").arg(pos.x()).arg(pos.y());//生成文本内容
    ui->label_mouse_position->setText(text);//设置label的内容，用于显示
    ui->label_mouse_position->adjustSize();//根据内容调整label的大小，以显示全部内容
}


void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape)
    {
        this->close();
    }
}
