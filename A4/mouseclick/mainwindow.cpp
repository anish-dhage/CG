#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMouseEvent>
#include <QColorDialog>
#include <math.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    start = true;
    k = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

QImage image(500, 500, QImage::Format_RGB888);
QColor C;

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

void MainWindow::dda_linedraw(int x1,int y1,int x2,int y2)
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
        image.setPixel(floor(x),floor(y),C.rgb());
        x = x + dx;
        y = y + dy;
        i++;
    }

    ui->label->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::mousePressEvent(QMouseEvent *ev){
    if(start == true){
        int p,q;
        p = ev->pos().x();
        q = ev->pos().y();
        a[k] = p;
        b[k] = q;

        if(ev->button() == Qt::RightButton){
            dda_linedraw(a[k-1],b[k-1],a[0],b[0]);
            start = false;
        }
        else{
            if(k>0){
                dda_linedraw(a[k],b[k],a[k-1],b[k-1]);
            }
        }
        k++;
    }
}

void MainWindow::on_pushButton_clicked()
{
    C = QColorDialog::getColor();
}

void MainWindow::seedfill(int px ,int py){
    QRgb curr = image.pixel(px,py);
    if(curr != C.rgb()){
        image.setPixel(px,py,C.rgb());
        seedfill(px+1,py);
        seedfill(px-1,py);
        seedfill(px,py+1);
        seedfill(px,py-1);
    }
    ui->label->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::mouseDoubleClickEvent(QMouseEvent *ev){
    int px,py;
    px = ev->pos().x();
    py = ev->pos().y();
    seedfill(px,py);
}
