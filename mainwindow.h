#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QString>
#include <QButtonGroup>
#include <QPushButton>
#include <QTime>
#include <QMessageBox>
#include <QKeyEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent *);
    void init();
    void keyPressEvent(QKeyEvent *event);
    void PressUp();
    void PressDown();
    void PressLeft();
    void PressRight();
    void myRand();
    QPushButton *button;
    int s[4][4];
    int score = 0;
    bool state;
    struct Ns{
        int i;
        int j;
    };

public slots: //槽函数
    void slotStart();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
