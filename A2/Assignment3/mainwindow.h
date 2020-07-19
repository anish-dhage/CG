#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void midpt(QImage &I,int x0,int y0,int R);
    void drawcircle(QImage &I,int x,int y,int x0,int y0);
    void dda(QImage &I,int x1,int x0,int y1,int y0);
    void circle_dda(QImage &I,int x0,int y0,int R);
    int sign(float a);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
