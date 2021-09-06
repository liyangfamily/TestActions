#ifndef DATAGROUP_H
#define DATAGROUP_H

#include <QWidget>

namespace Ui {
class DataGroup;
}

class DataGroup : public QWidget
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
