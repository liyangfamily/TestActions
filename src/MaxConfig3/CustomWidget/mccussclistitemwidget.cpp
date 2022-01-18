#include "mccussclistitemwidget.h"
#include "ui_mccussclistitemwidget.h"
#include <QStyle>
#include <QRegExp>
#include <QMessageBox>
#include <LAPIControl>
#include <Core/icore.h>

MCCusSCListItemWidget::MCCusSCListItemWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MCCusSCListItemWidget)
{
    ui->setupUi(this);
    ui->toolBtnUpgrade->hide();
    ui->toolBtnDetails->hide();
    ui->DeviceName->hide();
//    ui->labelDeviceStatus->hide();
//    ui->labelDeviceType->hide();
//    ui->labelLinkInfo->hide();
    this->setMouseTracking(true);
    ui->toolBtnModifyName->setVisible(false);
    QRegExp regx("^\\w{5,40}$");
    QValidator *validator = new QRegExpValidator(regx, ui->lineEditDeviceName );
    ui->lineEditDeviceName->setValidator(validator);
    ui->lineEditDeviceName->setReadOnly(true);
    connect(ui->lineEditDeviceName,&QLineEdit::editingFinished,this,&MCCusSCListItemWidget::slot_toolBtnModifyName_editingFinished);
    connect(ui->lineEditDeviceName,&QLineEdit::returnPressed,this,&MCCusSCListItemWidget::slot_toolBtnModifyName_returnPressed);
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
        ui->lineEditDeviceName->setText(m_item->getDeviceName());
        ui->lineEditDeviceName->setToolTip(m_item->getDeviceName());
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

        ui->LinkInfo->setText(m_item->hostName().split(":").front());
        ui->DeviceType->setText(m_item->senderCardTag());
        ui->btnConnect->setText(m_item->isUsing()?tr("DisConnect"):tr("Connect"));
        ui->btnConnect->setChecked(m_item->isUsing());
    }
	else {
        ui->DeviceStatus->setText(tr("Offline"));
        ui->DeviceStatus->setProperty("SCOnlineStatus", "Offline");
        ui->btnConnect->setChecked(false);
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

void MCCusSCListItemWidget::enterEvent(QEvent *event)
{
    if(m_item&&m_item->hasAndroid()&&m_item->isUsing()){
        ui->toolBtnModifyName->setVisible(true);
    }
    QWidget::enterEvent(event);
}

void MCCusSCListItemWidget::leaveEvent(QEvent *event)
{
    ui->toolBtnModifyName->setVisible(false);
    QWidget::leaveEvent(event);
}

void MCCusSCListItemWidget::on_btnConnect_clicked()
{
    if(nullptr==m_item){
        return;
    }
    if(ui->btnConnect->text()==tr("Connect")){
        if(LAPI::ER_Fail== LAPI::ConnectItemByInternalUuid(m_item->internalUuid())){
            //return;
        }
    }
    else{
        if(LAPI::ER_Fail== LAPI::DisconnectItemByInternalUuid(m_item->internalUuid())){
            //return;
        }
    }
    ui->toolBtnModifyName->setVisible(m_item->isUsing());
    updateItemWidget();
}

void MCCusSCListItemWidget::on_toolBtnModifyName_clicked()
{
    ui->lineEditDeviceName->setReadOnly(false);
    ui->lineEditDeviceName->selectAll();
    ui->lineEditDeviceName->setFocus();
}

void MCCusSCListItemWidget::slot_toolBtnModifyName_editingFinished()
{
    ui->lineEditDeviceName->setReadOnly(true);
    QString tempName = ui->lineEditDeviceName->text();
    if(tempName.isEmpty()||tempName == ui->DeviceName->text()){
        ui->lineEditDeviceName->setText(ui->DeviceName->text());
        return;
    }
    int opt = QMessageBox::question(NULL, tr("Question"),
                                    tr("Change the send card name: \"%1\", confirm?").arg(tempName),
                                    QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    if (opt == QMessageBox::Yes)
    {
        LAPI::EResult ret =LAPI::WriteDeviceName(tempName,true);
        if(LAPI::EResult::ER_Success == ret){
            ui->DeviceName->setText(tempName);
            qDebug() << QString("Change the send card name: \"%1\".").arg(ui->lineEditDeviceName->text());
        }
        else{
            ui->lineEditDeviceName->setText(ui->DeviceName->text());
        }
        Core::ICore::showMessageLAPIResult(ret);
        return;
    }
}

void MCCusSCListItemWidget::slot_toolBtnModifyName_returnPressed()
{
    ui->lineEditDeviceName->setReadOnly(true);
    ui->lineEditDeviceName->clearFocus();
}
