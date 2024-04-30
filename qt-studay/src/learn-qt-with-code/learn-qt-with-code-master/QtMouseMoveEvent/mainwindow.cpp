#include "mainwindow.h"
#include "ui_mainwindow.h"
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
