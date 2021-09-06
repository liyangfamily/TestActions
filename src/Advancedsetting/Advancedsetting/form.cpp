#include "form.h"
#include "ui_form.h"
//#include "QMouseEvent"
//#include "QPaintEvent"
#include "QPainter"


Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);

    setWindowFlags(Qt::WindowStaysOnTopHint);
}

Form::~Form()
{
    delete ui;
}
void Form::ChangRGB(QColor rgb,int xendp)
{
    RGB = rgb;
    Xend = xendp;
}
void Form::paintEvent(QPaintEvent *)
{
    int ScreenX = 0;
    int ScreenHeight = this->height();
    int ScreenY =0;
    int ScreenWidth = this->width();
    int i = 0;
    int j = 0;

    QPainter painter;
    painter.begin(this);
    //定义画笔
    QPen pen;

    //先初始化成黑色
    pen.setColor(QColor(0,0,0));
    painter.setPen(pen);
    for ( i = ScreenX; i < ScreenHeight; i++)
    {
        for (j = ScreenY; j < ScreenWidth; j++)
        {
            painter.drawPoint(j,i);
        }
    }
    pen.setColor(RGB);
    painter.setPen(pen);
    for (i = ScreenX; i < Xend; i++)
    {
        painter.drawPoint(i,0);
    }
    painter.end();

}

