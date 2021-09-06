#ifndef SMARTSECONDSETTING_H
#define SMARTSECONDSETTING_H

#include <QWidget>

namespace Ui {
class SmartSecondSetting;
}

class SmartSecondSetting : public QWidget
{
    Q_OBJECT

public:
    explicit SmartSecondSetting(QWidget *parent = nullptr);
    ~SmartSecondSetting();



private slots:
    void on_tableWidget_itemSelectionChanged();


    void on_EmptypushButton_clicked();

    void on_RevokepushButton_clicked();

    void on_ClearpushButton_clicked();

    void on_FinishpushButton_clicked();

    void on_ExportpushButton_clicked();

private:
    int Col = 0;
    int Row = 0;
    int Index = 1;
    int Colindex = 1;

private:
    void InitForm();













private:
    Ui::SmartSecondSetting *ui;
};

#endif // SMARTSECONDSETTING_H
