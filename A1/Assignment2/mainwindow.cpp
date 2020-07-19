#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "linedrawing.h"

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

linedrawing l;

void MainWindow::on_pushButton_clicked()
{
    int x1 = 50;
    int y1 = 150;
    int x2 = 50;
    int y2 = 150;
    int side;
    side = ui->textEdit->toPlainText().toInt();

    l.bresenems(x1,y1,x2 + side,y2);
    l.bresenems(x1 + side ,y1, x2 + side,y2 + side);
    l.bresenems(x1 + side,y1 + side,x2 ,y2 + side);
    l.bresenems(x1,y1,x2,y2 + side);

    l.dda_linedraw(x1,(y1+(side/2)),(x2+(side/2)),y2+side);
    l.dda_linedraw((x1+(side/2)),y1+side,x2+side,y2+(side/2));
    l.dda_linedraw(x1+side,y1+(side/2),x2+(side/2),y2);
    l.dda_linedraw(x1+(side/2),y1,x2,(y2+(side/2)));

    l.bresenems(x1+(side/4),y1+((3*side)/4),x2+((3*side)/4),y2+((3*side)/4));
    l.bresenems(x1+((3*side)/4),y1+((3*side)/4), x2+((3*side)/4),y2+(side/4));
    l.bresenems(x1+((3*side)/4),y1+(side/4),x2+(side/4) ,y2 + (side/4));
    l.bresenems(x1+(side/4) ,y1 + (side/4),x2+(side/4),y2+((3*side)/4));

    QImage i = l.retImage();
    ui->label->setPixmap(QPixmap::fromImage(i));
    ui->pushButton->setEnabled(true);
}

