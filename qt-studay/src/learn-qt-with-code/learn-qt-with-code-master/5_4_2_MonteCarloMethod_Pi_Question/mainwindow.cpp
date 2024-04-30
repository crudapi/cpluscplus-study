#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPainter>
#include <QDebug>
#include <ctime>
#include<QFont>
#include <random>

MainWindow::MainWindow(size_t haveToDrawCount, size_t drawStep, int square_side_length
                       , QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_haveToDrawCount(haveToDrawCount)
    , m_drawStep(drawStep)
    , m_square_side_length(square_side_length)
{
    ui->setupUi(this);

    m_pTimer = new QTimer(this);
    m_pTimer->setInterval(300);
    m_pTimer->start();
    connect(m_pTimer, &QTimer::timeout, this, &MainWindow::OnTimeOut);
    //(1) your code 使用resize 成员函数设置窗口的长和宽
    resize(square_side_length, square_side_length);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_pTimer;
}

void MainWindow::paintEvent(QPaintEvent *painter1)
{
    drawCircle();
    drawPointer();
    drawPi();
}

void MainWindow::OnTimeOut()
{
    //让窗口重绘
    if(m_pointList.size() < m_haveToDrawCount)
    {
        CreateRandomPoint(m_drawStep);
        static int i = 0;
        ++i;
        qDebug()<<"update() "<<i;
        update();
    }
    else
    {
        m_pTimer->stop();
    }
}

void MainWindow::drawPointer()
{
    QPainter painter(this);
    static long long drawCount = 0;
    long long drawStep = 0;
    auto itr = m_pointList.begin();
    while (itr != m_pointList.end())
    {
        auto point = *itr;
        painter.drawPoint(point);
        ++itr;
    }
}

void MainWindow::drawCircle()
{
    //(5) your code 使用drawEllipse绘制一个中心在窗口中心，半径为窗口宽度一半的圆
    QPainter painter(this);

}

void MainWindow::drawPi(void)
{
    auto currentPi = m_caculatePi.getPi();
    QPainter painter(this);
    QFont font;
    font.setPointSize(15);
    painter.setFont(font);
    QString text = QString("n=%1, N=%2, current pi=%3").arg(m_caculatePi.n).arg(m_caculatePi.N).arg(currentPi);
    setWindowTitle(text);
//    painter.drawText(this->width()/2-150, this->height()/2, text);
}
void MainWindow::CreateRandomPoint(long long drawStep)
{
    for (long long i = 0; i < drawStep && m_pointList.size() < m_haveToDrawCount; ++i)
    {
        //(2) your code 获得一个范围在[0-500) 之间的整数x, y https://zhuanlan.zhihu.com/p/659439130
        //取值为0-1之间的随机数x, y
        std::default_random_engine e;
        std::uniform_real_distribution<double> u(-1.0, 1.0); // 左闭右闭区间，产生均匀分布的实数
        e.seed(time(0));
        double x = u(e);//取值为0-1之间的随机数
        double y = u(e);


        QPoint point;
        //将0~1的两个随机值x, y先变成0~窗口宽度（高度）之间的两个整数b1, b2
        //将两个随机整数b1, b2作为point的x y值(请自行搜索QPoint的相关成员函数)
        //https://doc.qt.io/qt-6/qpoint.html
        //(3) your code
        int w = m_square_side_length * x;
        int h = m_square_side_length * y;
        point.setX(w);
        point.setY(h);

        m_pointList.push_back(point);

        m_caculatePi.addOnePoint(x, y);
    }
}
