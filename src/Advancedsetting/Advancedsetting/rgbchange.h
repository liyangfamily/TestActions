#ifndef RGBCHANGE_H
#define RGBCHANGE_H

#include <QDialog>

namespace Ui {
class RGBchange;
}

class RGBchange : public QDialog
{
    Q_OBJECT

public:
    explicit RGBchange(QWidget *parent = nullptr);
    ~RGBchange();




private slots:
    void on_pushButton_clicked();

private:
    void InitForm();
    void LoadForm();


private:
    Ui::RGBchange *ui;
};

#endif // RGBCHANGE_H
