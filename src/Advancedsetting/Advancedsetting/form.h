#ifndef FORM_H
#define FORM_H

#include <QWidget>

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr);
    ~Form();

    void paintEvent (QPaintEvent * event);
    void ChangRGB(QColor rgb,int xendp);


public:
    int Xend;
private:
    QImage Image;
    QColor RGB;

private:
    Ui::Form *ui;
};

#endif // FORM_H
