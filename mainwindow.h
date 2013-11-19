#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked(); //обработчик нажатия на кнопку "НANDLE"      

private:
    Ui::MainWindow *ui;
    void setupEnvironment();
};

#endif // MAINWINDOW_H
