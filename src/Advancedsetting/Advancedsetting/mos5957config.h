#ifndef MOS5957CONFIG_H
#define MOS5957CONFIG_H

#include <QDialog>

namespace Ui {
class MOS5957config;
}

class MOS5957config : public QDialog
{
    Q_OBJECT

public:
    explicit MOS5957config(QWidget *parent = nullptr);
    ~MOS5957config();

private slots:
    void on_pushButton_clicked();

private:
    void LoadForm();

private:
    Ui::MOS5957config *ui;
};

#endif // MOS5957CONFIG_H
