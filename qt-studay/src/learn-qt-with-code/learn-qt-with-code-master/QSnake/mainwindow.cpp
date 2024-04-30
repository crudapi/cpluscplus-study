#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <cassert>
#include <QKeyEvent>
#include <QPainter>
#include <QDebug>
#include <QMessageBox>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    bool  load_result = false;
    //(4) your code. load data from data.txt file by Snake's member function LoadPlayDataFromFile
    load_result = m_snake.LoadPlayDataFromFile("data.txt");
    assert(load_result);

    //(5) your code.  set window title with "Snake Game"
    //https://zhuanlan.zhihu.com/p/669799427
    this->setWindowTitle(
           QApplication::translate("toplevel", "Snake Game"));
    //(6) your code. set window size by the col number and row number in Snake object.
    //every pixmap size is the same : width * height = m_pictureSize * m_pictureSize
    //use setFixedSize()
    int w = m_snake.GetCol() * m_pictureSize;
    int h = m_snake.GetRow() * m_pictureSize;
    setFixedSize(w,  h);


    m_timer.setInterval(500);

    connect(&m_timer, SIGNAL(timeout()), this, SLOT(moveSlot()));

    m_timer.start();
}

void MainWindow::moveSlot() {
    qDebug()<<"moveSlot";
    move(m_key);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    qDebug() << "keyPressEvent "<< event->key();

    m_key = event->key();

    this->move(event->key());
}

void MainWindow::move(int key)
{
    qDebug()<<"move " << key;
    if (key < 0) {
        return;
    }

    qDebug()<<"user pressed key "<< key;
    bool gameover = false;

    switch (key)
    {
    case Qt::Key_Up :
    {
        //(3) your code. the player enter a key
        //, you have to update the game by call member function Play in Snake.
        gameover = m_snake.Play('w');

        update();//this will tell Qt to call paintEvent.
        break;
    }
    case Qt::Key_Down :
    {
        //(3) your code.
        gameover = m_snake.Play('s');
        update();
        break;
    }
    case Qt::Key_Left :
    {
        //(3) your code.
        gameover = m_snake.Play('a');
        update();
        break;
    }
    case Qt::Key_Right :
    {
        //(3) your code.
        gameover = m_snake.Play('d');
        update();
        break;
    }
    }
    if(gameover)
    {
        //(2) your code. use QMessageBox to tell the player the game is over.
        // https://zhuanlan.zhihu.com/p/671461612
        QMessageBox messageBox;
        messageBox.setWindowTitle(tr("game is over"));
        messageBox.setText(tr("Do you really want to quit?"));
        messageBox.setStandardButtons(QMessageBox::Yes);
        if (messageBox.exec() == QMessageBox::Yes)
            qApp->quit();
    }
}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    //(1) your code. use Snake PrintMatrix to drew the game
    m_snake.PrintMatrix(painter, m_pictureSize);
}
