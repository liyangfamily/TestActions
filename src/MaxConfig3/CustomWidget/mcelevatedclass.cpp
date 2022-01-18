#include "mcelevatedclass.h"

#include <QStyleOption>
#include <QPainter>
#include <QComboBox>

RoundedMenu::RoundedMenu(QWidget *parent):
    QMenu(parent)
{
    this->setWindowFlag(Qt::FramelessWindowHint);        //重要
    this->setWindowFlag(Qt::NoDropShadowWindowHint);     //重要
    this->setAttribute(Qt::WA_TranslucentBackground);    //重要
    this->setFont(QFont("Microsoft YaHei", 12));
}

void QComboBox::wheelEvent(QWheelEvent* e) {}
void QAbstractSpinBox::wheelEvent(QWheelEvent *e){}

BindingSliderAndSpinBox::BindingSliderAndSpinBox(QSlider *slider, QSpinBox *spinbox, QWidget *parent):
    QObject(parent)
{
    if(slider&&spinbox){
        connect(slider, QOverload<int>::of(&QSlider::valueChanged), [=](int d)
                {
            spinbox->blockSignals(true);
            spinbox->setValue(d);
            spinbox->blockSignals(false);
            if(slider->isSliderDown()){
                //鼠标按下在拖动滑块
                emit sig_valueChanged(d);
            }
            else{
                //鼠标在点击滑槽
                emit sig_singleShotValueChange(d);
            }
        });

        connect(spinbox, QOverload<int>::of(&QSpinBox::valueChanged), [=](int d)
        {
            slider->setValue(d);
        });

        connect(slider, &QSlider::sliderReleased, [=]()
                { sig_singleShotValueChange(slider->value()); });
    }
}
