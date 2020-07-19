#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    bool start;
    int k;
    int a[10],b[10];

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void dda_linedraw(int x1,int y1,int x2,int y2);
    int sign(float a);
    void mousePressEvent(QMouseEvent *ev);
    void mouseDoubleClickEvent(QMouseEvent *ev);
    void seedfill(int px ,int py);

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
