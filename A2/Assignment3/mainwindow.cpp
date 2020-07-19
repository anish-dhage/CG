#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<cmath>
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

void MainWindow::on_pushButton_clicked()
{
    int r=ui->textEdit->toPlainText().toUInt();
    int x0=ui->textEdit_2->toPlainText().toUInt();
    int y0=ui->textEdit_3->toPlainText().toUInt();

    QImage I(500,500,QImage::Format_RGB888);
    circle_dda(I,x0,y0,int(r/2));
    midpt(I,x0,y0,r);
    int r3=(int)((sqrt(3)/2)*r);
    dda(I,x0-r3,x0,y0+int(r/2),y0-r);
    dda(I,x0+r3,x0,y0+int(r/2),y0-r);
    dda(I,x0+r3,x0-r3,y0+int(r/2),y0+int(r/2));
    ui->label->setPixmap(QPixmap::fromImage(I));
}

    int MainWindow::sign(float a)
    {
        if(a>0)
        {
            return 1;
        }
        else if(a<0)
        {
            return -1;
        }
        else
        {
            return 0;
        }
    }

    void MainWindow::dda(QImage &I,int x2,int x1,int y2,int y1)
    {
        float length;
        if(abs(x2-x1)>abs(y2-y1))
        {
            length = abs(x2-x1);
        }
        else
        {
            length = abs(y2-y1);
        }

        float dx,dy;
        dx = (float)((x2 - x1)/length);
        dy = (float)((y2 - y1)/length);

        float x,y;
        x = x1 + (0.5 * sign(dx));
        y = y1 + (0.5 * sign(dy));

        int i = 0;
        while(i < length){
            I.setPixel(floor(x),floor(y),qRgb(255,255,255));
            x = x + dx;
            y = y + dy;
            i++;
        }

    }
    void MainWindow::drawcircle(QImage &I,int x,int y,int x0,int y0)
    {
        int val=qRgb(255,255,255);
        I.setPixel(x+x0,y+y0,val);
        I.setPixel(x0-x,y0+y,val);
        I.setPixel(x+x0,y0-y,val);
        I.setPixel(x0-x,y0-y,val);
        I.setPixel(x0+y,x+y0,val);
        I.setPixel(y+x0,y0-x,val);
        I.setPixel(x0-y,y0-x,val);
        I.setPixel(x0-y,y0+x,val);
    }
    void MainWindow::circle_dda(QImage &I,int x0,int y0,int R)
    {
        int i,val=0;
        float x1=R;
        float y1=0;
        float x2;
        float y2;
        float e;
        float stx=x1,sty=y1;
        for(i=0;val<R;i++)
        {
            val=pow(2,i);
        }
        e=1/pow(2,i-1);
        do
        {
            x2=x1+y1*e;
            y2=y1-x2*e;
            I.setPixel(x0+int(x2),y0+int(y2),qRgb(255,255,255));
            x1=x2;
            y1=y2;

        }while((y1-sty)<e||(stx-x1)>e);
    }

    void MainWindow::midpt(QImage &I,int x0,int y0,int R)
    {
        int x=0;
        int y=R;
        int h=1-R;
        drawcircle(I,x,y,x0,y0);
        while(y>x)
        {
            if(h>=0)
            {
                h=h+2-2*y;
                y--;
            }
            x++;
            h=h+2*x+3;
            drawcircle(I,x,y,x0,y0);
        }
    }

