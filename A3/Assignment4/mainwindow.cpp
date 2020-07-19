#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QtGui>
#include<cmath>
QImage I(400,400,QImage::Format_RGB888);
float Tr[3][3],A[3][25],B[3][25];
int cnt=0;
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

void MainWindow::DDA(int x1,int y1,int x2,int y2)
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
void MainWindow::mousePressEvent(QMouseEvent *eve)
{
   A[0][cnt]=QString::number(eve->x()).toUInt();
   A[1][cnt]=QString::number(eve->y()).toUInt();
   A[2][cnt]=1;
   int i,j;
   if(eve->button()==Qt::RightButton)
   {
       DDA(A[0][cnt-1],A[1][cnt-1],A[0][0],A[1][0]);
       for(i=0;i<2;i++)
           for(j=0;j<cnt;j++)
               A[i][j]-=200;
     }
   else
   {
   if(cnt)
       DDA(A[0][cnt],A[1][cnt],A[0][cnt-1],A[1][cnt-1]);
       cnt++;
   }
   ui->label->setPixmap(QPixmap::fromImage(I));
   emit(clicked());
}

void MainWindow::Matmul()
{
    int i,j,k;
    for(i=0;i<3;i++)
        for(j=0;j<cnt;j++)
        {
            B[i][j]=0;
            for(k=0;k<3;k++)
                B[i][j]=B[i][j]+Tr[i][k]*A[k][j];
        }
}
void MainWindow::resetTr()
{
    int i,j;
    for(i=0;i<3;i++)
        for(j=0;j<3;j++)
            Tr[i][j]=0;
}

void MainWindow::on_pushButton_clicked()
{
   int i,j;
   resetTr();
   int sx=ui->textEdit->toPlainText().toUInt();
   int sy=ui->textEdit_2->toPlainText().toUInt();

   Tr[0][0]=sx;
   Tr[2][2]=1;
   Tr[1][1]=sy;

   Matmul();
   for(i=0;i<2;i++){
       for(j=0;j<cnt;j++){
           B[i][j]+=200;
       }
   }
   for(i=1;i<cnt;i++){
       DDA(B[0][i],B[1][i],B[0][i-1],B[1][i-1]);
   }
    DDA(B[0][cnt-1],B[1][cnt-1],B[0][0],B[1][0]);
    ui->label->setPixmap(QPixmap::fromImage(I));
}


void MainWindow::on_pushButton_3_clicked()
{
    int i,j;
    resetTr();
    int tx=ui->textEdit_3->toPlainText().toUInt();
    int ty=ui->textEdit_4->toPlainText().toUInt();
    Tr[1][2]=ty;
    Tr[0][0]=Tr[1][1]=1;
    Tr[0][2]=tx;
    Tr[2][2]=1;
    Matmul();
    for(i=0;i<2;i++)
        for(j=0;j<cnt;j++)
            B[i][j]+=200;
    for(i=1;i<cnt;i++)
        DDA(B[0][i],B[1][i],B[0][i-1],B[1][i-1]);
     DDA(B[0][cnt-1],B[1][cnt-1],B[0][0],B[1][0]);
     ui->label->setPixmap(QPixmap::fromImage(I));
}

void MainWindow::on_pushButton_2_clicked()
{
    int i,j;
    float t=ui->textEdit_5->toPlainText().toFloat();
    resetTr();
    Tr[0][0]=cos(t);
    Tr[0][1]=sin(t);
    Tr[1][0]=-sin(t);
    Tr[1][1]=cos(t);
    Tr[2][2]=1;
    Matmul();
    for(i=0;i<2;i++)
        for(j=0;j<cnt;j++)
            B[i][j]+=200;
    for(i=1;i<cnt;i++)
        DDA(B[0][i],B[1][i],B[0][i-1],B[1][i-1]);
     DDA(B[0][cnt-1],B[1][cnt-1],B[0][0],B[1][0]);
     ui->label->setPixmap(QPixmap::fromImage(I));
}


