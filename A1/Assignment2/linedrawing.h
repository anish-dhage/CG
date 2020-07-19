#ifndef LINEDRAWING_H
#define LINEDRAWING_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>

class linedrawing
{
public:
    linedrawing();
    int sign(float a);
    void dda_linedraw(int x1,int y1,int x2,int y2);
    void bresenems(int x1,int y1,int x2,int y2);
    QImage retImage();

signals:

public slots:


};

#endif // LINEDRAWING_H
