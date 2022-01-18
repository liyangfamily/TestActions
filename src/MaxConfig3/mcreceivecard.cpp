#include "mcreceivecard.h"
#include "ui_mcreceivecard.h"
#include <QMessageBox>
#include <QScrollArea>
#include "app.h"
#include "CustomWidget/mccusfileupgradewidget.h"
#include "CustomWidget/mcprogressdialog.h"
#include "ConnectionControl/connectionView.h"
#include "ConnectionControl/connectionScene.h"
#include "mcgammatable.h"

#include "Core/icore.h"
using namespace Internal::CustomWidget;

MCReceiveCard::MCReceiveCard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MCReceiveCard)
{
    ui->setupUi(this);
    gDispatcher->registerDispatcherPackage(LBLPackageInteCtrl_ReadSCFPGARegister(), this);

    QRegExp regx("[A-Fa-f0-9]{8}");
    ui->lineEditRegAddr->setValidator(new QRegExpValidator(regx, ui->lineEditRegAddr));
    ui->btnRegBroadCast->setChecked(true);
    ui->spinBoxRegLength->setRange(1,0xFFFF);
    ui->spinBoxRegPort->setRange(0,0xFF);
    ui->spinBoxRegModule->setRange(0,0xFF);

    initRCStatusInfo();

    m_monitor = new MCMonitor(this);
}

MCReceiveCard::~MCReceiveCard()
{
    gDispatcher->unregisterDispatcherPackage(LBLPackageInteCtrl_ReadSCFPGARegister(), this);
    delete ui;
}

bool MCReceiveCard::event(QEvent * e)
{
    if (e->type() == LBLPackageEvent::s_disPatcherPackage_eventType)
    {
        LBLPackageEvent *tempE = static_cast<LBLPackageEvent*>(e);
        switch (tempE->cmdNum() - 1)
        {
        case LBLInteCtrlPackage::ECommand::EC_Read_RCFPGARegister:
        {
            //onParseReadRCFPGARegister(tempE->package().data());
        }
        break;
        default:
            break;
        }
    }
    return QWidget::event(e);
}

void MCReceiveCard::cleanReceiveCardWidget()
{
    ui->tableWidgetSRCInfo->clearContents();
	ui->tableWidgetSRCInfo->setRowCount(0);
    ui->textBrowserReg->clear();
}

void MCReceiveCard::updateReceiveCard()
{
	LAPI::ReadConnection();
}

void MCReceiveCard::initRCStatusInfo()
{
	//ui->tableWidgetSRCInfo->setShowGrid(false);
	ui->tableWidgetSRCInfo->setMouseTracking(true);
	ui->tableWidgetSRCInfo->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui->tableWidgetSRCInfo->setEditTriggers(QAbstractItemView::NoEditTriggers);

	QStringList header;
    header << tr("PortIndex") << tr("ModuleIndex") << tr("HardWareVer") << tr("SoftwareVer") << tr("MCUVer") \
           << tr("ProtocolVer") << tr("PackageLoseRate") << tr("BitErrorRate") << tr("Upgrade");
	ui->tableWidgetSRCInfo->setColumnCount(header.size()); //设置列数
	ui->tableWidgetSRCInfo->setHorizontalHeaderLabels(header);
	ui->tableWidgetSRCInfo->horizontalHeader()->setStretchLastSection(true); //设置充满表宽度
    ui->tableWidgetSRCInfo->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    //ui->tableWidgetSRCInfo->horizontalHeader()->setSectionResizeMode(ECol_Upgrade, QHeaderView::Stretch);
    //ui->tableWidgetSRCInfo->horizontalHeader()->setFixedHeight(23); //设置表头的高度
	ui->tableWidgetSRCInfo->horizontalHeader()->setDefaultSectionSize(150); 
	ui->tableWidgetSRCInfo->verticalHeader()->setVisible(false);
}

void MCReceiveCard::updateRCStatusInfo(QList<LBL::RC::SRCStatusInfo>&rcStatusInfoList)
{
	ui->tableWidgetSRCInfo->clearContents();
    ui->tableWidgetSRCInfo->setRowCount(rcStatusInfoList.size());//总行数
	for (int i = 0; i < rcStatusInfoList.size(); ++i) {

		ui->tableWidgetSRCInfo->setRowHeight(i, 40);

		const LBL::RC::SRCStatusInfo& tempInfo = rcStatusInfoList.at(i);

		ui->tableWidgetSRCInfo->setItem(i, ECol_PortIndex, new QTableWidgetItem(QString::number(tempInfo.GetPortIndex() + 1)));
		ui->tableWidgetSRCInfo->item(i, ECol_PortIndex)->setTextAlignment(Qt::AlignCenter);

		ui->tableWidgetSRCInfo->setItem(i, ECol_ModuleIndex, new QTableWidgetItem(QString::number(tempInfo.GetModuleIndex() + 1)));
		ui->tableWidgetSRCInfo->item(i, ECol_ModuleIndex)->setTextAlignment(Qt::AlignCenter);

        ui->tableWidgetSRCInfo->setItem(i, ECol_HardWareVer, new QTableWidgetItem(tempInfo.GetPCBCategory()));
		ui->tableWidgetSRCInfo->item(i, ECol_HardWareVer)->setTextAlignment(Qt::AlignCenter);
        ui->tableWidgetSRCInfo->item(i, ECol_HardWareVer)->setToolTip(tempInfo.GetHardwareVendor());

        QString softwareVer = tempInfo.GetSoftwareVersion();
        ui->tableWidgetSRCInfo->setItem(i, ECol_SoftWareVer, new QTableWidgetItem(softwareVer));
        ui->tableWidgetSRCInfo->item(i, ECol_SoftWareVer)->setTextAlignment(Qt::AlignCenter);
        if(softwareVer.contains("G")){
            ui->tableWidgetSRCInfo->item(i, ECol_SoftWareVer)->setBackgroundColor(QColor("#3D242F"));
            ui->tableWidgetSRCInfo->item(i, ECol_SoftWareVer)->setTextColor(QColor("#F44A4A"));
        }
        ui->tableWidgetSRCInfo->setItem(i, ECol_MCUVer, new QTableWidgetItem(tempInfo.GetMCUVersion()));
        ui->tableWidgetSRCInfo->item(i, ECol_MCUVer)->setTextAlignment(Qt::AlignCenter);

        ui->tableWidgetSRCInfo->setItem(i, ECol_ProtocolType, new QTableWidgetItem(tempInfo.GetPotocolType()));
        ui->tableWidgetSRCInfo->item(i, ECol_ProtocolType)->setTextAlignment(Qt::AlignCenter);

		ui->tableWidgetSRCInfo->setItem(i, ECol_PackLoseRate, new QTableWidgetItem(QString("%1%2")\
			.arg(QString::number(tempInfo.GetPackageLoseRate(), 'f', 2))\
		.arg("PPM")));
        ui->tableWidgetSRCInfo->item(i, ECol_PackLoseRate)->setTextAlignment(Qt::AlignCenter);
        ui->tableWidgetSRCInfo->item(i, ECol_PackLoseRate)->setToolTip(tr("Receive Packages:%1\n"\
                                                                          "Total Packages:%2")\
                                                                       .arg(tempInfo.recivedPackages)\
                                                                       .arg(tempInfo.totalPackages));

		ui->tableWidgetSRCInfo->setItem(i, ECol_BitErrorRate, new QTableWidgetItem(QString("%1%2")\
			.arg(QString::number(tempInfo.GetBitErrorRate(), 'f', 2))\
			.arg("PPM")));
		ui->tableWidgetSRCInfo->item(i, ECol_BitErrorRate)->setTextAlignment(Qt::AlignCenter);
        ui->tableWidgetSRCInfo->item(i, ECol_BitErrorRate)->setToolTip(tr("Correct Packages:%1\n"\
                                                                          "Total Packages:%2")\
                                                                       .arg(tempInfo.correctPackages)\
                                                                       .arg(tempInfo.totalPackages));

		ui->tableWidgetSRCInfo->setItem(i, ECol_Upgrade, new QTableWidgetItem());
		ui->tableWidgetSRCInfo->item(i, ECol_Upgrade)->setFlags(ui->tableWidgetSRCInfo->item(i, ECol_Upgrade)->flags()&~Qt::ItemIsSelectable&~Qt::ItemIsEditable);
        MCCusFileUpgradeWidget *pBtn = new MCCusFileUpgradeWidget(LBLFileTransferPackage::EFT_ReciverFPGA, ui->tableWidgetSRCInfo);
		pBtn->setPortIndex(tempInfo.GetPortIndex());
		pBtn->setModuleIndex(tempInfo.GetModuleIndex());
        pBtn->startRefresh();
        ui->tableWidgetSRCInfo->setCellWidget(i, ECol_Upgrade, pBtn);
	}

    //ui->tableWidgetSRCInfo->resizeColumnsToContents();
    ui->tableWidgetSRCInfo->resizeColumnToContents(ECol_Upgrade);
}

quint16 MCReceiveCard::onParseReadRCFPGARegister(const QByteArray &data)
{
    LBLPackageInteCtrl_ReadSCFPGARegister pack(data);
    QByteArray packData = pack.getReplyData();
    return 0;
}

void MCReceiveCard::slot_ConnectItem()
{
    cleanReceiveCardWidget();
    updateReceiveCard();
}

void MCReceiveCard::slot_EnterNavigatPage()
{
    ConnectionFrame::instance()->setCurrentMode(ConnectionDiagramScene::Mode::ModuleParam);
    updateReceiveCard();
}

void MCReceiveCard::on_btnParamImport_clicked()
{
	QString selectFilter;
	QString fileName = QFileDialog::getOpenFileName(this,
		tr("Select File"),
		App::lastOpenPath,
        QString("%1;;%2;;%3").arg(Utils::FileFilter::MODULEPARAM_FILTER)
                             .arg(Utils::FileFilter::DRIVEICPARAM_FILTER)
                             .arg(Utils::FileFilter::DECODINGICPARAM_FILTER),
		&selectFilter);
	if (fileName.isEmpty()) {
		return;
    }
    App::lastOpenPath = fileName;
	App::writeConfig();

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        return;
    }
    QByteArray data = file.readAll();
    file.close();

    if (selectFilter == Utils::FileFilter::MODULEPARAM_FILTER) {
        if (file.size() != 1024) {
            return;
        }
        LAPI::EResult ret = LAPI::WriteModuleParam(0xFF, 0xFF, data);
        Core::ICore::showMessageLAPIResult(ret);
	}
    else if (selectFilter == Utils::FileFilter::DRIVEICPARAM_FILTER) {
        if (file.size() != 1024) {
            return;
        }
        LAPI::EResult ret = LAPI::WriteDriveICParam(0xFF, 0xFF, data);
        Core::ICore::showMessageLAPIResult(ret);
	}
    else if(selectFilter==Utils::FileFilter::DECODINGICPARAM_FILTER){
        LAPI::EResult ret = LAPI::WriteDecodingICParam(0xFF, 0xFF, data);
        Core::ICore::showMessageLAPIResult(ret);
    }
    else if(selectFilter==Utils::FileFilter::ALLPARAM_FILTER){
        if (file.size() != 9216) {
            return;
        }
        LAPI::EResult ret = LAPI::WriteRCFPGARegister(0xFF, 0xFF,0, data);
        Core::ICore::showMessageLAPIResult(ret);
    }
	return;
}

void MCReceiveCard::on_btnParamExport_clicked()
{
    QString selectFilter;
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), \
        App::lastOpenPath,
        QString("%1;;%2;;%3").arg(Utils::FileFilter::MODULEPARAM_FILTER)
                             .arg(Utils::FileFilter::DRIVEICPARAM_FILTER)
                             .arg(Utils::FileFilter::DECODINGICPARAM_FILTER),
        &selectFilter);
    if (fileName.isEmpty()) {
        return;
    }
    App::lastOpenPath = fileName;
    App::writeConfig();

    QByteArray data;
    if (selectFilter == Utils::FileFilter::MODULEPARAM_FILTER) {
        data = LAPI::ReadModuleParam(0, 0);
    }
    else if (selectFilter == Utils::FileFilter::DRIVEICPARAM_FILTER) {
        data = LAPI::ReadDriveICParam(0, 0);
    }
    else if(selectFilter == Utils::FileFilter::DECODINGICPARAM_FILTER){
        data = LAPI::ReadDecodingICParam(0, 0);
    }
    else if(selectFilter==Utils::FileFilter::ALLPARAM_FILTER){
        data = LAPI::ReadRCFPGARegister(0, 0,0,9216);
    }

    if (data.isEmpty()) {
        QMessageBox::information(NULL, tr("Tip"), \
            tr("Read failed."), QMessageBox::Yes, QMessageBox::Yes);
        return;
    }

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::information(NULL, tr("Tip"), \
            tr("File open failed."), QMessageBox::Yes, QMessageBox::Yes);
    }
    file.write(data);
    file.close();
}

void MCReceiveCard::on_btnParamSave_clicked()
{
	LAPI::EResult ret = LAPI::WriteSaveRCParam(0xFF, 0xFF, true);
    Core::ICore::showMessageLAPIResult(ret);
}

void MCReceiveCard::on_btnGamma_clicked()
{
    if(!m_gamma){
        m_gamma = new MCGammaTable(this);
    }
    m_gamma->raise();
    m_gamma->show();
}

void MCReceiveCard::on_btnRCUpgradeAll_clicked()
{
    m_monitor->raise();
    m_monitor->show();
}

void MCReceiveCard::on_btnRCInfoRefresh_clicked()
{
    //ui->btnRCInfoRefresh->setEnabled(false);
    MCProgressDialog bar(this);
    bar.setLabelText(tr("Refreshing..."));
    bar.show();
	QList<LBL::RC::SRCStatusInfo> tempList= LAPI::ReadRCStatusInfo(true);
	if (tempList.isEmpty()) {
		tempList = LAPI::GetRCStatusInfo();
	}
    updateRCStatusInfo(tempList);
    bar.delayReset();
    //ui->btnRCInfoRefresh->setEnabled(true);
    Core::ICore::showMessage(tr("Receive card info refresh completion."),1000);
}

void MCReceiveCard::on_checkBoxRegBroadCast_clicked()
{

}

void MCReceiveCard::on_btnRegRead_clicked()
{
    ui->textBrowserReg->clear();
    quint8 port=ui->spinBoxRegPort->value();
    quint8 module=ui->spinBoxRegModule->value();
    quint32 addr=ui->lineEditRegAddr->text().toUInt(nullptr,16);
    quint16 length=ui->spinBoxRegLength->value();
    QByteArray reData= LAPI::ReadRCFPGARegister(port,module,addr,length);
    QString buffer;
    buffer = LBLUIHelper::byteArrayToHexStr(reData);
    ui->textBrowserReg->append(buffer); 
	Core::ICore::showMessageLAPIResult(reData.isEmpty() ? LAPI::EResult::ER_Fail : LAPI::EResult::ER_Success);
}

void MCReceiveCard::on_btnRegWrite_clicked()
{
	quint8 port = ui->btnRegBroadCast->isChecked() ? 0xFF : ui->spinBoxRegPort->value();
	quint8 module = ui->btnRegBroadCast->isChecked() ? 0xFF : ui->spinBoxRegModule->value();
	quint32 addr = ui->lineEditRegAddr->text().toUInt(nullptr, 16);
	quint16 length = ui->spinBoxRegLength->value();
    QByteArray buffer;
    buffer.fill(0, length);
    QByteArray text = LBLUIHelper::hexStrToByteArray(ui->textBrowserReg->toPlainText().simplified());
    buffer.replace(0, length > text.size() ? text.size() : length, text);
    LAPI::EResult ret = LAPI::WriteRCFPGARegister(port, module, addr, buffer);
	Core::ICore::showMessageLAPIResult(ret);
}

void MCReceiveCard::on_btnRegImport_clicked()
{
	QString selectFilter;
	QString fileName = QFileDialog::getOpenFileName(this,
		tr("Select File"),
		App::lastOpenPath,
        QString("%1").arg(tr(Utils::FileFilter::BINPARAM_FILTER)),
		&selectFilter);
	if (fileName.isEmpty()) {
		return;
	}
	QFileInfo fileinfo(fileName);
	App::lastOpenPath = fileinfo.absolutePath();
	App::writeConfig();

	QFile file(fileName);
	if (!file.open(QIODevice::ReadOnly)) {
		return;
	}
    QByteArray data = file.readAll();
    file.close();

	ui->textBrowserReg->clear();
	QString buffer;
	buffer = LBLUIHelper::byteArrayToHexStr(data);
	ui->textBrowserReg->append(buffer);
    ui->textBrowserReg->moveCursor(QTextCursor::Start);
    ui->spinBoxRegLength->setValue(data.size());
}

void MCReceiveCard::on_btnRegExport_clicked()
{
	QByteArray data = LBLUIHelper::hexStrToByteArray(ui->textBrowserReg->toPlainText());
	if (data.isEmpty()) {
		return;
	}
	QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), \
		App::lastOpenPath, \
        QString("%1").arg(tr(Utils::FileFilter::BINPARAM_FILTER)));
	if (fileName.isEmpty()) {
		return;
	}
	QFile file(fileName);
	if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::information(NULL, tr("Tip"), \
            tr("File open failed."), QMessageBox::Yes, QMessageBox::Yes);
	}
	file.write(data);
	file.close();
}

void MCReceiveCard::slot_rcTableWidgetUpgrade_clicked()
{
	QPushButton *senderObj = qobject_cast<QPushButton*>(sender());
	if (!senderObj){
		return;
	}
	QModelIndex idx = ui->tableWidgetSRCInfo->indexAt(QPoint(senderObj->frameGeometry().x(), senderObj->frameGeometry().y()));
	QTableWidgetItem* item = ui->tableWidgetSRCInfo->item(idx.row(), 0);
	if (!item) {
		return;
	}
	QHBoxLayout* layout = qobject_cast<QHBoxLayout*>(ui->tableWidgetSRCInfo->cellWidget(idx.row(), ECol_Upgrade));
	if (!layout) {
		return;
	}
	QString port = ui->tableWidgetSRCInfo->item(idx.row(), ECol_Upgrade)->text();
    QString module = ui->tableWidgetSRCInfo->item(idx.row(), 1)->text();
}
