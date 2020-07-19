#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<math.h>
#include<QDebug>
static QImage image(700,700,QImage::Format_RGB888);
int sign(float a)
{
    if(a<0)
    {
        return(-1);
    }
    else if(a>0)
    {
        return(1);
    }
    else
    {
        return 0;
    }
}
void bresenhams(float x1,float y1,float x2,float y2)
{
    QRgb value;
    value=qRgb(255,255,255);
    float x=x1;
    float y=y1;
    float dx=abs(x2-x1);
    float dy=abs(y2-y1);
    int s1=sign(x2-x1);
    int s2=sign(y2-y1);
    int interchange;
    if(dy>dx)
    {
        float temp=dx;
        dx=dy;
        dy=temp;
        interchange=1;
    }
    else
    {
        interchange=0;
    }
    float e=2*dy-dx;
    for(int i=0;i<=dx;i++)
    {
        image.setPixel(x,y,value);
        while(e>=0)
        {
            if(interchange==1)
            {
                x=x+s1;
            }
            else
            {
                y=y+s2;
            }
            e=e-2*dx;
        }
        if(interchange==1)
        {
            y=y+s2;
        }
        else
        {
            x=x+s1;
        }
        e=e+2*dy;
    }
}
void seedfill(int x,int y,QRgb old,QRgb col)
{
    if(x<=0||x>=700||y>=700||y<=0)
    {
        return;
    }
    QRgb curr=image.pixel(x,y);
    if(curr==old)
    {
        image.setPixel(x,y,col);


        seedfill(x,y+1,old,col);


        seedfill(x-1,y,old,col);


        seedfill(x,y-1,old,col);
        seedfill(x+1,y,old,col);
    }
}

int* rotate(int a,int b)
{
    float angle=3.14/4;
   int*c = new int[2];
        int x=a-350;
        int y=350-b;
        int newx=x*cos(angle)-y*sin(angle);

        int newy=x*sin(angle)+y*cos(angle);
        c[0]=newx+350;
        c[1]=-newy+350;
    return(c);

}


void draw()
{
    //rotate
int*rpoint=new int[2];
int*rpoint1=new int[2];
rpoint=rotate(350,350);
rpoint1=rotate(550,350);
bresenhams(rpoint[0],rpoint[1],rpoint1[0],rpoint1[1]);

//rpoint=rotate(350,350);
rpoint1=rotate(350,150);
bresenhams(rpoint[0],rpoint[1],rpoint1[0],rpoint1[1]);

rpoint=rotate(350,150);
rpoint1=rotate(550,150);
bresenhams(rpoint[0],rpoint[1],rpoint1[0],rpoint1[1]);

rpoint=rotate(550,150);
rpoint1=rotate(550,350);
bresenhams(rpoint[0],rpoint[1],rpoint1[0],rpoint1[1]);


    int i=0;
    while(i<200)
    {
        rpoint=rotate((350+i),350);
        rpoint1=rotate((350+i),150);
        bresenhams(rpoint[0],rpoint[1],rpoint1[0],rpoint1[1]);
        i=i+50;
    }
    i=0;
    while(i<200)
    {
        rpoint=rotate(350,350-i);
        rpoint1=rotate(550,350-i);
        bresenhams(rpoint[0],rpoint[1],rpoint1[0],rpoint1[1]);

        //bresenhams(350,350-i,550,350-i);
        i=i+50;
    }


        QRgb col=qRgb(255,255,255);
        QRgb old=qRgb(0,0,0);

    int x[4],y[4];     //seedfill coordinates
    for(int k=0;k<4;k++)
    {
        x[k]=375+k*50;
        y[k]=325-k*50;
     }


    int a=rotate(375+100,325)[0];
    int b=rotate(375+100,325)[1];
    seedfill(a,b,old,col);


     a=rotate(375,325)[0];
     b=rotate(375,325)[1];
    seedfill(a,b,old,col);


    a=rotate(375+50,325-50)[0];
    b=rotate(375+50,325-50)[1];
   seedfill(a,b,old,col);


   a=rotate(375,325-100)[0];
   b=rotate(375,325-100)[1];
  seedfill(a,b,old,col);


  a=rotate(375+100,325-100)[0];
  b=rotate(375+100,325-100)[1];
 seedfill(a,b,old,col);


 a=rotate(375+150,325-50)[0];
 b=rotate(375+150,325-50)[1];
seedfill(a,b,old,col);



a=rotate(375+50,325-150)[0];
b=rotate(375+50,325-150)[1];
seedfill(a,b,old,col);


a=rotate(375+150,325-150)[0];
b=rotate(375+150,325-150)[1];
seedfill(a,b,old,col);


}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    draw();
    ui->label->setPixmap(QPixmap::fromImage(image));
    qDebug()<<"oafhaofiha";

}

MainWindow::~MainWindow()
{
    delete ui;
}



