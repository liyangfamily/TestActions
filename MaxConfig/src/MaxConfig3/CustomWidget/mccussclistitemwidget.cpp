#include "mccussclistitemwidget.h"
#include "ui_mccussclistitemwidget.h"
#include <QStyle>
#include <LAPIControl>

MCCusSCListItemWidget::MCCusSCListItemWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MCCusSCListItemWidget)
{
    ui->setupUi(this);
    ui->toolBtnUpgrade->hide();
}

MCCusSCListItemWidget::~MCCusSCListItemWidget()
{
    delete ui;
}

void MCCusSCListItemWidget::setSCItem(LBL::SCItem::LBLAbstractSCItem *item)
{
    Q_ASSERT(item);
    if(item){
        m_item=item;
        updateItemWidget();
    }
}

void MCCusSCListItemWidget::updateItemWidget()
{
    if(m_item){
        ui->DeviceName->setText(m_item->getDeviceName());
        //状态
        switch(m_item->senderCardStatus())
        {
        case ESenderCardStatus::ESS_Online:
        {
            ui->DeviceStatus->setText(tr("Online"));
            ui->DeviceStatus->setProperty("SCOnlineStatus","Online");
        }
        break;
        case ESenderCardStatus::ESS_OffLine:
        {
            ui->DeviceStatus->setText(tr("Offline"));
            ui->DeviceStatus->setProperty("SCOnlineStatus","Offline");
        }
        break;
        case ESenderCardStatus::ESS_StandBy:
        {
            ui->DeviceStatus->setText(tr("StandBy"));
            ui->DeviceStatus->setProperty("SCOnlineStatus","Offline");
        }
        break;
        case ESenderCardStatus::ESS_OnlyAndroidOnline:
        {
            ui->DeviceStatus->setText(tr("Android Online"));
            ui->DeviceStatus->setProperty("SCOnlineStatus","Offline");
        }
        break;
        }

        ui->DeviceStatus->style()->unpolish(ui->DeviceStatus);
        ui->DeviceStatus->style()->polish(ui->DeviceStatus);
        ui->DeviceStatus->update();

        ui->LinkInfo->setText(m_item->hostName());
        ui->DeviceType->setText(m_item->senderCardTag());
        ui->btnConnect->setText(m_item->isUsing()?tr("DisConnect"):tr("Connect"));
    }
	else {
        ui->DeviceStatus->setText(tr("Offline"));
        ui->DeviceStatus->setProperty("SCOnlineStatus", "Offline");
        ui->DeviceStatus->style()->unpolish(ui->DeviceStatus);
        ui->DeviceStatus->style()->polish(ui->DeviceStatus);
        ui->DeviceStatus->update();
	}
}

bool MCCusSCListItemWidget::isOnline()
{
	if (m_item) {
		//状态
		if (m_item->senderCardStatus() == ESenderCardStatus::ESS_Online) {
			return true;
		}
	}
	return false;
}

void MCCusSCListItemWidget::on_btnConnect_clicked()
{
    if(nullptr==m_item){
        return;
    }
    if(ui->btnConnect->text()==tr("Connect")){
        if(LAPI::ER_Fail== LAPI::ConnectItemByInternalUuid(m_item->internalUuid())){
            return;
        }
    }
    else{
        if(LAPI::ER_Fail== LAPI::DisconnectItemByInternalUuid(m_item->internalUuid())){
            return;
        }
    }
    updateItemWidget();
}
