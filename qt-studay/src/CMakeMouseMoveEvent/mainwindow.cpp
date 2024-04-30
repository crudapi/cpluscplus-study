#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMouseEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    //下面的两句话如果不加上，鼠标只有点击的时候才会响应移动事件，这样就不方便了。
    //加上之后，鼠标无需点击，无需拖动，只要移动鼠标，就可以看到界面实时更新了
    setMouseTracking(true);
    this->centralWidget()->setMouseTracking(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    auto pos = event->pos();
    ui->moveLabel->move(event->pos());
    QString text = QString("mouse postion (%1, %2)").arg(pos.x()).arg(pos.y());//生成文本内容
    ui->moveLabel->setText(text);//设置label的内容，用于显示
    ui->moveLabel->adjustSize();//根据内容调整label的大小，以显示全部内容
}
