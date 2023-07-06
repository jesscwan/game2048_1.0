#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //初始化
    init();
    button = new QPushButton("开始游戏",this);
    button->setGeometry(60,400,200,50);

    button->setFocusPolicy(Qt::NoFocus);

    qsrand(uint(QTime(0,0,0).secsTo(QTime::currentTime())));

    connect(button,SIGNAL(clicked()),this,SLOT(slotStart()));

    setFocus();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()
{
    for (int i = 0;i<4;i++)
        for (int j = 0;j<4;j++)
            s[i][j] = 0;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setFont(QFont("微软雅黑",20,700,false));
    p.drawText(QPoint(20,60),"分数： "+QString::number(score));

    //设定颜色字体
    for (int i = 0;i<4;i++)
    {
        for (int j = 0;j<4;j++)
        {
            p.setBrush(QColor(255,255+40*(s[i][j]%3),255+40*(s[i][j]%3),255));
            p.drawRect(i*60+40,j*60+120,55,55);
            if (s[i][j]!=0)
            {
                p.setPen(Qt::black);
                p.setFont(QFont("微软雅黑",10,700,false));
                p.drawText(QRectF(i*60+40,j*60+120,55,55),QString::number(s[i][j]),QTextOption(Qt::AlignCenter));
            }
        }
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (!state){
        return;
    }
    switch (event->key()) {
        case Qt::Key_W:
        case Qt::Key_Up:
            PressUp();
            break;

        case Qt::Key_S:
        case Qt::Key_Down:
            PressDown();
            break;

        case Qt::Key_A:
        case Qt::Key_Left:
            PressLeft();
            break;

        case Qt::Key_D:
        case Qt::Key_Right:
            PressRight();
            break;

        default:
            return;
    }
    myRand();
    update();
}

void MainWindow::slotStart()
{
    QMessageBox::about(this,"游戏规则:","WSAD，上下左右都行");
    score = 0;
    for (int i = 0;i<4;i++)
        for (int j = 0;j<4;j++)
            s[i][j] = 0;
    button->setText("不服！再来一局");
    int randi = qrand()%4;
    int randj = qrand()%4;
    s[randi][randj] = 2;

    state = true;
    update();
}

void MainWindow::PressUp(){
    //移动
    for (int i=0;i<4;i++) {
        for (int j=1;j<4;j++) {
            if(s[i][j]==0)continue;
            for (int p=0;p<j;p++) {
                //查看前面是否有空格子可移动
                if(s[i][p]==0){
                    s[i][p]=s[i][j];
                    s[i][j]=0;
                    break;
                }
            }
        }
    }
    //相加
    for (int i=0;i<4;i++) {
        for (int j=0;j<3;j++) {
            if(s[i][j]==s[i][j+1]){
                s[i][j]=2*s[i][j];
                s[i][j+1]=0;
                score+=s[i][j];
                for (int p=j+2;p<4;p++) {
                    s[i][p-1]=s[i][p];
                }
            }
        }
    }
}
void MainWindow::PressDown(){
    //移动
    for (int i=0;i<4;i++) {
        for (int j=2;j>=0;j--) {
            if(s[i][j]==0)continue;
            for (int p=3;p>j;p--) {
                //查看前面是否有空格子可移动
                if(s[i][p]==0){
                    s[i][p]=s[i][j];
                    s[i][j]=0;
                    break;
                }
            }
        }
    }
    //相加
    for (int i=0;i<4;i++) {
        for (int j=3;j>0;j--) {
            if(s[i][j]==s[i][j-1]){
                s[i][j]=2*s[i][j];
                s[i][j-1]=0;
                score+=s[i][j];
                for (int p=j-2;p>=0;p--) {
                    s[i][p+1]=s[i][p];
                }
            }
        }
    }
}
void MainWindow::PressLeft(){
    //移动
    for (int j=0;j<4;j++) {
        for (int i=1;i<4;i++) {
            if(s[i][j]==0){
                continue;
            }
            for (int p=0;p<i;p++) {
                //查看前面是否有空格可移入
                if(s[p][j] == 0){
                    s[p][j] = s[i][j];
                    s[i][j] = 0;
                    break;
                }
            }
        }
    }
    //相加
    for (int j=0;j<4;j++) {
        for (int i=0;i<3;i++) {
            if(s[i][j]==s[i+1][j]){
                s[i][j]=s[i][j]*2;
                score+=s[i][j];
                s[i+1][j]=0;
                for(int p=i+2;p<4;p++){
                    s[p-1][j] = s[p][j];
               }
            }
        }
    }
}
void MainWindow::PressRight(){
    //移动
    for (int j=0;j<4;j++) {
        for (int i=2;i>=0;i--) {
            if(s[i][j]==0){
                continue;
            }
            for (int p=3;p>i;p--) {
                //查看前面是否有空格可移入
                if(s[p][j] == 0){
                    s[p][j] = s[i][j];
                    s[i][j] = 0;
                    break;
                }
            }
        }
    }
    //相加
    for (int j=0;j<4;j++) {
        for (int i=3;i>=0;i--) {
            if(s[i][j]==s[i-1][j]){
                s[i][j]=s[i][j]*2;
                s[i-1][j]=0;
                score+=s[i][j];
                for(int p=i-2;p>=0;p--){
                    s[p+1][j] = s[p][j];
                }
            }
        }
    }
}
void MainWindow::myRand(){
    int i=0,j=0;
    //找出格子
    struct Ns n[15];
    int ni=0;
    for (i=0;i<4;i++) {
        for (j=0;j<4;j++) {
            if(s[i][j]==0){
                n[ni].i=i;
                n[ni].j=j;
                ni++;
            }
        }
    }

    //判断游戏是否结束
    if (ni==0) {
        for (i=0;i<4;i++) {
            for (j=0;j<3;j++) {
                if(s[i][j]==s[i][j+1]){
                    return;
                }
            }
        }
        for (j=0;j<4;j++) {
            for (i=0;i<3;i++) {
                if(s[i][j]==s[i+1][j]){
                    return;
                }
            }
        }
        QMessageBox::about(this,"游戏失败","分数为："+QString::number(score)+" ");
        return;
    }
    int rand=qrand()%ni;
    s[n[rand].i][n[rand].j]=2;
}
