#ifndef ADVANCEDOTHERPARA_H
#define ADVANCEDOTHERPARA_H

#include <QWidget>

namespace Ui {
class AdvancedOtherPara;
}

class AdvancedOtherPara : public QWidget
{
    Q_OBJECT

public:
    explicit AdvancedOtherPara(QWidget *parent = nullptr);
    ~AdvancedOtherPara();

private slots:
    void on_pushButton_clicked();

private:
    void InitForm();
    void LoadForm();







private:
    Ui::AdvancedOtherPara *ui;
};

#endif // ADVANCEDOTHERPARA_H
