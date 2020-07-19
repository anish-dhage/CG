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
    void DDA(QImage &I,int x1,int y1,int x0,int y0);

    void hilbert(QImage &I,float P[4][2],float End[2][2],int dir,int n);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
