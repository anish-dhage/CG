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
    void mousePressEvent(QMouseEvent*);
    void DrawXY();
    void Matmul();
    void DDA(int,int,int,int);
    void on_pushButton_clicked();
    void resetTr();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

signals:
    void clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
