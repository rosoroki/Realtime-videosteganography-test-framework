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
    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
//private slots:
   // void load();
   // void save();
   // void search();
   // void graph();
    //void on_tabWidget_selected(const QString &arg1);
};

#endif // MAINWINDOW_H
