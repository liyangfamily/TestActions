#ifndef MAINWINDOW_NEW_H
#define MAINWINDOW_NEW_H

#include <QMainWindow>

namespace Ui {
class MainWindow_New;
}

class MainWindow_New : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow_New(QWidget *parent = nullptr);
    ~MainWindow_New();

private:
    Ui::MainWindow_New *ui;

private slots:
    void on_pushButton_3_clicked();
};

#endif // MAINWINDOW_NEW_H
