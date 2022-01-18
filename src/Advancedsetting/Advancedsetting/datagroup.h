#ifndef DATAGROUP_H
#define DATAGROUP_H

#include <QDialog>

namespace Ui {
class DataGroup;
}

class DataGroup : public QDialog
{
    Q_OBJECT

public:
    explicit DataGroup(QWidget *parent = nullptr);
    ~DataGroup();

private slots:
    void on_pushButton_clicked();

    void on_spinBox_valueChanged(int arg1);

private:
    Ui::DataGroup *ui;

private:
    void InitForm();
    void LoadForm();









};

#endif // DATAGROUP_H
