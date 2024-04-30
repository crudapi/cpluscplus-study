#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.showFullScreen();//程序启动就全屏显示，按esc退出全屏
    return a.exec();
}
