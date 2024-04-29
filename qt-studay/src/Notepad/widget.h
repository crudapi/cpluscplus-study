#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtWidgets>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
private slots:
    void quit();
private:
    QTextEdit *textEdit;
    QPushButton *quitButton;
};
#endif // WIDGET_H

