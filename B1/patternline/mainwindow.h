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

    void on_radioButton_2_clicked();
    void dda(QImage &I, int x1, int y1, int x0, int y0, int c);
    void on_radioButton_3_clicked();

    void on_radioButton_4_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
