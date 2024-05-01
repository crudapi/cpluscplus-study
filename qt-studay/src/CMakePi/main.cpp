#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    size_t haveToDrawCount = 100000*10;//一共要撒的点的数量
    size_t drawStep = 10000;//每次更新界面撒多少新的点在界面上
    int square_side_length = 800;//窗口的长和宽
    MainWindow w(haveToDrawCount, drawStep, square_side_length);
    w.show();
    return a.exec();
}
