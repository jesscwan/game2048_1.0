#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setFixedSize(320,480);        //设置窗体固定的长宽
    w.setWindowTitle("2048");       //设置窗体名
    w.show();
    return a.exec();
}
