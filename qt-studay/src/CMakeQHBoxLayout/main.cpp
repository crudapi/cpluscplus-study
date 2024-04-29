#include "widget.h"

#include <QApplication>
#include <QtWidgets>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Widget window;
  //! [create, lay out widgets and show]
      QLabel *label = new QLabel(QApplication::translate("windowlayout", "Name:"));
      QLineEdit *lineEdit = new QLineEdit();

      QHBoxLayout *layout = new QHBoxLayout();
      layout->addWidget(label);
      layout->addWidget(lineEdit);
      window.setLayout(layout);
  //! [create, lay out widgets and show]
      window.setWindowTitle(
          QApplication::translate("windowlayout", "Window layout"));
    window.show();
    return a.exec();
}
