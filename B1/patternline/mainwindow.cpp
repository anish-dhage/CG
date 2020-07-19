#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<cmath>
#include<QtGui>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::dda(QImage &I,int x1,int y1,int x0,int y0,int c)
{
    int len,count=0;
    float wy;
    int w=ui->textEdit_2->toPlainText().toUInt();
    int yp;
    int dy=(y1-y0);
    int dx=(x1-x0);
    if(abs(dx)>=abs(dy))
        len=dx;
    else
        len=dy;
    wy=(w-1)/2*sqrt((dx*dx+dy*dy))/abs(dx);
    float xinc=float(dx)/len;
    float yinc=float(dy)/len;
    float x=x0;
    float y=y0;
    int i;
    for(i=0;i<abs(len);i++)
    {
        x+=xinc;
        y+=yinc;
        yp=int(y-wy);
        while(yp<(y+wy))
        {
        if((count%5==0&&c==1)||((count/10)%2==0&&c==2)||(((count/10)%2==0||count%5==0)&&c==3))
        I.setPixel(int(x),int(yp),qRgb(255,255,255));
        yp++;
        }
        count++;
    }
}

void MainWindow::on_radioButton_2_clicked()
{
    QImage I(500,500,QImage::Format_RGB888);
    int x1=ui->textEdit_3->toPlainText().toUInt();
    int y1=ui->textEdit_4->toPlainText().toUInt();
    int x0=ui->textEdit_5->toPlainText().toUInt();
    int y0=ui->textEdit_6->toPlainText().toUInt();
    dda(I,x1,y1,x0,y0,1);
    ui->label->setPixmap(QPixmap::fromImage(I));

}

void MainWindow::on_radioButton_3_clicked()
{
    QImage I(500,500,QImage::Format_RGB888);
    int x1=ui->textEdit_3->toPlainText().toUInt();
    int y1=ui->textEdit_4->toPlainText().toUInt();
    int x0=ui->textEdit_5->toPlainText().toUInt();
    int y0=ui->textEdit_6->toPlainText().toUInt();
    dda(I,x1,y1,x0,y0,2);
    ui->label->setPixmap(QPixmap::fromImage(I));
}

void MainWindow::on_radioButton_4_clicked()
{
    QImage I(500,500,QImage::Format_RGB888);
    int x1=ui->textEdit_3->toPlainText().toUInt();
    int y1=ui->textEdit_4->toPlainText().toUInt();
    int x0=ui->textEdit_5->toPlainText().toUInt();
    int y0=ui->textEdit_6->toPlainText().toUInt();
    dda(I,x1,y1,x0,y0,3);
    ui->label->setPixmap(QPixmap::fromImage(I));
}
