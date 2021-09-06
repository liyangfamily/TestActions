#include "mcsclistitemwidget.h"
#include "ui_mcsclistitemwidget.h"

MCSCListItemWidget::MCSCListItemWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MCSCListItemWidget)
{
    ui->setupUi(this);
}

MCSCListItemWidget::~MCSCListItemWidget()
{
    delete ui;
}
