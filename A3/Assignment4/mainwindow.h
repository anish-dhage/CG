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
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();
    void on_pushButton_clicked();
    void resetTr();
    void Matmul();

    void mousePressEvent(QMouseEvent *eve);

    int sign(float a);
    void DDA(int x1,int y1,int x2,int y2);


signals:
    void clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
