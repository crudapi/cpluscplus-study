#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QTimer>
#include<QPoint>
#include<list>
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct CaculatePi
{
    //计算新点是否在圆形内部，如果是就计数+1
    void addOnePoint(double x, double y)
    {
        auto r = sqrt(x * x + y * y);
        if (r < 1)
        {
            //(4) your code
            ++n;
        }
        ++N;
    }

    double getPi(void)
    {
        auto pi = n * 4.0 / N;
        return pi;
    }
    //caculate pi
    double Pi = 0;
    long long n = 0;//count point in circle
    long long N = 0;//total point
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(size_t haveToDrawCount, size_t drawStep, int square_side_length, QWidget *parent = nullptr);
    ~MainWindow();
    //绘制窗口内容，包括窗口大小和鼠标位置
    void paintEvent(QPaintEvent* painter1) override;
private:
    void OnTimeOut(void);
    void drawPointer(void);
    void drawCircle(void);
    void drawPi(void);
    void CreateRandomPoint(long long drawStep);
private:
   QTimer* m_pTimer;
   Ui::MainWindow *ui;
   size_t m_haveToDrawCount = 0;
   size_t m_drawStep = 0;
   int m_square_side_length;//窗口的长=宽
   list<QPoint> m_pointList;
   CaculatePi m_caculatePi;
};
#endif // MAINWINDOW_H
