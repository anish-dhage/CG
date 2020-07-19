#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<cmath>
int level;
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
void MainWindow::DDA(QImage &I,int x1,int y1,int x0,int y0)
{
    int len;
    int dy=(y1-y0);
    int dx=(x1-x0);
    if(abs(dx)>=abs(dy))
        len=abs(dx);
    else
        len=abs(dy);
    float xinc=float(dx)/len;
    float yinc=float(dy)/len;
    float x=x0;
    float y=y0;
    int i;
    for(i=0;i<abs(len);i++)
    {
        x+=xinc;
        y+=yinc;
        I.setPixel(int(x),int(y),qRgb(50,100,100));
    }
}

void MainWindow::hilbert(QImage &I,float P[4][2],float End[2][2],int dir,int n)
{
    float side;
    float PP[4][4][2];
    float M[4][2][2];
    int a,b,c,d;

    a=dir;
    b=(dir+1)%4;
    c=(dir+2)%4;
    d=(dir+3)%4;

    if(n==level)
    {
        DDA(I,P[a][0],P[a][1],P[b][0],P[b][1]);
        DDA(I,P[b][0],P[b][1],P[c][0],P[c][1]);
        DDA(I,P[c][0],P[c][1],P[d][0],P[d][1]);

        End[0][0]=P[a][0];
        End[0][1]=P[a][1];
        End[1][0]=P[d][0];
        End[1][1]=P[d][1];
    }

    else
    {
        side=sqrt(pow((P[0][0]-P[1][0]),2)+pow((P[0][1]-P[1][1]),2))/4;

        for(int i=0;i<4;i++)
        {
            PP[i][0][0]=P[i][0]-side;
            PP[i][0][1]=P[i][1]+side;
            PP[i][1][0]=P[i][0]-side;
            PP[i][1][1]=P[i][1]-side;
            PP[i][2][0]=P[i][0]+side;
            PP[i][2][1]=P[i][1]-side;
            PP[i][3][0]=P[i][0]+side;
            PP[i][3][1]=P[i][1]+side;
        }

        hilbert(I,PP[a],M[a],b,n+1);
        hilbert(I,PP[b],M[b],a,n+1);
        hilbert(I,PP[c],M[c],a,n+1);
        hilbert(I,PP[d],M[d],d,n+1);

        DDA(I,M[a][0][0],M[a][0][1],M[b][0][0],M[b][0][1]);
        DDA(I,M[b][1][0],M[b][1][1],M[c][0][0],M[c][0][1]);
        DDA(I,M[c][1][0],M[c][1][1],M[d][1][0],M[d][1][1]);

        End[0][0]=M[a][1][0];
        End[0][1]=M[a][1][1];
        End[1][0]=M[d][0][0];
        End[1][1]=M[d][0][1];
    }
}

void MainWindow::on_pushButton_clicked()
{
    QImage I(500, 500, QImage::Format_RGB888);
    level=ui->textEdit->toPlainText().toUInt();

    float P[4][2];
    P[0][0]=200;
    P[0][1]=300;
    P[1][0]=200;
    P[1][1]=200;
    P[2][0]=300;
    P[2][1]=200;
    P[3][0]=300;
    P[3][1]=300;

    float M[2][2];

    hilbert(I,P,M,0,0);

    ui->label->setPixmap(QPixmap::fromImage(I));
}
