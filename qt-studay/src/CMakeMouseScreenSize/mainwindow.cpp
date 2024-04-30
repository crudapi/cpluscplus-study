#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDesktopWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    auto t = (QMainWindow*)this;
    t->centralWidget()->setMouseTracking(true);
    this->setMouseTracking(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

inline void MainWindow::paintEvent(QPaintEvent* painter1)
{
    auto text = "mouse=" + std::to_string(m_mousePos.x() + 1) + "," + std::to_string(m_mousePos.y() + 1);

    cout << "paintEvent" << text << endl;
    drawSize();
    drawMouse();
}

void MainWindow::mouseMoveEvent(QMouseEvent* event)
{
    m_mousePos = event->pos();
    auto text = "mouse=" + std::to_string(m_mousePos.x() + 1) + "," + std::to_string(m_mousePos.y() + 1);

    cout << "mouseMoveEvent" << text << endl;
    update();//repaint
}

void MainWindow::drawMouse()
{
    QPainter painter(this);
    auto text = "mouse=" + std::to_string(m_mousePos.x() + 1) + "," + std::to_string(m_mousePos.y() + 1);
    painter.drawText(QPoint(10, 15), QString(text.c_str()));
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    cout << "keyPressEvent " << event->key() << endl;
    if (event->key() == Qt::Key_Escape)
    {
        cout << "showNormal" << endl;
        showNormal();
    }
    update();//repaint
}

void MainWindow::drawSize(void)
{
    int left = 10;
    int row = 40;
    int row_height = 80;
    int row_index = 1;
    QPainter painter(this);
    painter.drawText(QPoint(left, row), QString(("Window width=" + std::to_string(width())).c_str()));
    painter.drawText(QPoint(left, row + row_height * row_index++), QString(("Window height=" + std::to_string(height())).c_str()));
    painter.drawText(QPoint(left, row + row_height * row_index++), QString("desktop width=") + QString::number(QApplication::desktop()->width()));
    painter.drawText(QPoint(left, row + row_height * row_index++), QString("desktop height=") + QString::number(QApplication::desktop()->height()));
}
