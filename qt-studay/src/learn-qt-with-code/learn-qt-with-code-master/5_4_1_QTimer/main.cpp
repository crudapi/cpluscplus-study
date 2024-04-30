#include <QCoreApplication>
#include <QTimer>
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTimer timer;
    timer.setInterval(1000);
    QObject::connect(&timer, &QTimer::timeout, [](){static int i=0; cout<<"Hello"<<++i<<endl;});
    timer.start();

    return a.exec();
}
