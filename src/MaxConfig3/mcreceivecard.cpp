#include "mcreceivecard.h"
#include "ui_mcreceivecard.h"
#include <QMessageBox>
#include <QScrollArea>
#include "app.h"
#include "CustomWidget/mccusfileupgradewidget.h"

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
	header << tr("PortIndex") << tr("ModuleIndex") << tr("HardWareVer") << tr("SoftwareVer") << tr("FPGAVer") << tr("PackageLoseRate") << tr("BitErrorRate") << tr("Upgrade");
	ui->tableWidgetSRCInfo->setColumnCount(header.size()); //设置列数
	ui->tableWidgetSRCInfo->setHorizontalHeaderLabels(header);
	ui->tableWidgetSRCInfo->horizontalHeader()->setStretchLastSection(true); //设置充满表宽度
    ui->tableWidgetSRCInfo->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
	ui->tableWidgetSRCInfo->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Stretch);
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

		ui->tableWidgetSRCInfo->setItem(i, ECol_HardWareVer, new QTableWidgetItem(tempInfo.GetHardwareVendor()));
		ui->tableWidgetSRCInfo->item(i, ECol_HardWareVer)->setTextAlignment(Qt::AlignCenter);

		ui->tableWidgetSRCInfo->setItem(i, ECol_SoftWareVer, new QTableWidgetItem(tempInfo.GetSoftwareVendor()));
		ui->tableWidgetSRCInfo->item(i, ECol_SoftWareVer)->setTextAlignment(Qt::AlignCenter);

		ui->tableWidgetSRCInfo->setItem(i, ECol_FPGAVer, new QTableWidgetItem(tempInfo.GetFPGAVersion()));
		ui->tableWidgetSRCInfo->item(i, ECol_FPGAVer)->setTextAlignment(Qt::AlignCenter);

		ui->tableWidgetSRCInfo->setItem(i, ECol_PackLoseRate, new QTableWidgetItem(QString("%1%2")\
			.arg(QString::number(tempInfo.GetPackageLoseRate(), 'f', 2))\
		.arg("PPM")));
		ui->tableWidgetSRCInfo->item(i, ECol_PackLoseRate)->setTextAlignment(Qt::AlignCenter);

		ui->tableWidgetSRCInfo->setItem(i, ECol_BitErrorRate, new QTableWidgetItem(QString("%1%2")\
			.arg(QString::number(tempInfo.GetBitErrorRate(), 'f', 2))\
			.arg("PPM")));
		ui->tableWidgetSRCInfo->item(i, ECol_BitErrorRate)->setTextAlignment(Qt::AlignCenter);

		ui->tableWidgetSRCInfo->setItem(i, ECol_Upgrade, new QTableWidgetItem());
		ui->tableWidgetSRCInfo->item(i, ECol_Upgrade)->setFlags(ui->tableWidgetSRCInfo->item(i, ECol_Upgrade)->flags()&~Qt::ItemIsSelectable&~Qt::ItemIsEditable);
		MCCusFileUpgradeWidget *pBtn = new MCCusFileUpgradeWidget(LBLFileTransferPackage::EFT_ReciverFPGA, ui->tableWidgetSRCInfo);
		pBtn->setPortIndex(tempInfo.GetPortIndex());
		pBtn->setModuleIndex(tempInfo.GetModuleIndex());
		pBtn->startRefresh();
		ui->tableWidgetSRCInfo->setCellWidget(i, ECol_Upgrade, pBtn);
	}

	QTimer::singleShot(5, [=]() {
		ui->tableWidgetSRCInfo->resizeColumnToContents(ECol_Upgrade);
		ui->tableWidgetSRCInfo->repaint();
	});
	
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
    updateReceiveCard();
}

void MCReceiveCard::on_btnParamImport_clicked()
{
	QString selectFilter;
	QString fileName = QFileDialog::getOpenFileName(this,
		tr("Select File"),
		App::lastOpenPath,
		QString("%1;;%2;;%3").arg(Utils::FileFilter::MODULEPARAM_FILTER).arg(Utils::FileFilter::DRIVEICPARAM_FILTER).arg(Utils::FileFilter::DECODINGICPARAM_FILTER),
		&selectFilter);
	if (fileName.isEmpty()) {
		return;
	}
	QFileInfo file(fileName);
	App::lastOpenPath = file.absolutePath();
	App::writeConfig();

	if (file.size() != 1024) { 
		return;
	}
	if (selectFilter == Utils::FileFilter::MODULEPARAM_FILTER) {
		ui->labelRCModuleFileName->setText(file.fileName());
		ui->labelRCModuleFileName->setToolTip(file.filePath());
	}
	else if (selectFilter == Utils::FileFilter::DRIVEICPARAM_FILTER) {
		ui->labelRCDriveICFileName->setText(file.fileName());
		ui->labelRCDriveICFileName->setToolTip(file.filePath());
	}
	else {
		ui->labelRCDecodingICFileName->setText(file.fileName());
		ui->labelRCDecodingICFileName->setToolTip(file.filePath());
	}
	return;
}

void MCReceiveCard::on_btnModuleExport_clicked()
{
	QByteArray data = LAPI::ReadModuleParam(0, 0);
	if (data.isEmpty()) {
		QMessageBox::information(NULL, tr("提示"), \
			tr("读取失败."), QMessageBox::Yes, QMessageBox::Yes);
		return;
	}
	QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), \
		App::lastOpenPath, \
		QString("%1").arg(Utils::FileFilter::MODULEPARAM_FILTER));
	if (fileName.isEmpty()) {
		return;
	}
	QFile file(fileName);
	if (!file.open(QIODevice::WriteOnly)) {
		QMessageBox::information(NULL, tr("提示"), \
			tr("文件打开失败."), QMessageBox::Yes, QMessageBox::Yes);
	}
	file.write(data);
	file.close();
}

void MCReceiveCard::on_btnModuleSend_clicked()
{
	QFile file(ui->labelRCModuleFileName->toolTip());
	if (!file.open(QIODevice::ReadOnly)) {
		return;
	}
	QByteArray data = file.readAll();
    file.close();
	LAPI::EResult ret = LAPI::WriteModuleParam(0xFF, 0xFF, data);
	Core::ICore::showMessageLAPIResult(ret);
	/*if (LAPI::EResult::ER_Success != ret) {
		QMessageBox::information(NULL, tr("提示"), \
			tr("发送失败."), QMessageBox::Yes, QMessageBox::Yes);
	}*/
}

void MCReceiveCard::on_btnDriveICExport_clicked()
{
	QByteArray data = LAPI::ReadDriveICParam(0, 0);
	if (data.isEmpty()) {
		QMessageBox::information(NULL, tr("提示"), \
			tr("读取失败."), QMessageBox::Yes, QMessageBox::Yes);
		return;
	}
	QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), \
		App::lastOpenPath, \
		QString("%1").arg(Utils::FileFilter::DRIVEICPARAM_FILTER));
	if (fileName.isEmpty()) {
		return;
	}
	QFile file(fileName);
	if (!file.open(QIODevice::WriteOnly)) {
		QMessageBox::information(NULL, tr("提示"), \
			tr("文件打开失败."), QMessageBox::Yes, QMessageBox::Yes);
	}
	file.write(data);
	file.close();
}

void MCReceiveCard::on_btnDriveICSend_clicked()
{
	QFile file(ui->labelRCDriveICFileName->toolTip());
	if (!file.open(QIODevice::ReadOnly)) {
		return;
	}
	QByteArray data = file.readAll();
    file.close();
	LAPI::EResult ret = LAPI::WriteDriveICParam(0xFF, 0xFF, data);
	Core::ICore::showMessageLAPIResult(ret);
	/*if (LAPI::EResult::ER_Success != ret) {
		QMessageBox::information(NULL, tr("提示"), \
			tr("发送失败."), QMessageBox::Yes, QMessageBox::Yes);
	}*/
}

void MCReceiveCard::on_btnDecodingICExport_clicked()
{
	QByteArray data = LAPI::ReadDecodingICParam(0, 0);
	if (data.isEmpty()) {
		QMessageBox::information(NULL, tr("提示"), \
			tr("读取失败."), QMessageBox::Yes, QMessageBox::Yes);
		return;
	}
	QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), \
		App::lastOpenPath, \
		QString("%1").arg(Utils::FileFilter::DECODINGICPARAM_FILTER));
	if (fileName.isEmpty()) {
		return;
	}
	QFile file(fileName);
	if (!file.open(QIODevice::WriteOnly)) {
		QMessageBox::information(NULL, tr("提示"), \
			tr("文件打开失败."), QMessageBox::Yes, QMessageBox::Yes);
	}
	file.write(data);
	file.close();
}

void MCReceiveCard::on_btnDecodingICSend_clicked()
{
	QFile file(ui->labelRCDecodingICFileName->toolTip());
	if (!file.open(QIODevice::ReadOnly)) {
		return;
	}
	QByteArray data = file.readAll();
    file.close();
	LAPI::EResult ret = LAPI::WriteDecodingICParam(0xFF, 0xFF, data);
	Core::ICore::showMessageLAPIResult(ret);
	/*if (LAPI::EResult::ER_Success != ret) {
		QMessageBox::information(NULL, tr("提示"), \
			tr("发送失败."), QMessageBox::Yes, QMessageBox::Yes);
	}*/
}

void MCReceiveCard::on_btnParamSave_clicked()
{
	LAPI::EResult ret = LAPI::WriteSaveRCParam(0xFF, 0xFF, true);
	Core::ICore::showMessageLAPIResult(ret);
}

void MCReceiveCard::on_btnRCUpgradeAll_clicked()
{
	m_monitor.show();
	m_monitor.raise();
}

void MCReceiveCard::on_btnRCInfoRefresh_clicked()
{
	//QList<LBL::RC::SRCMonitorInfo> tempMonitorList = LAPI::ReadRCMonitorInfo(0xFF, true);

	QList<LBL::RC::SRCStatusInfo> tempList= LAPI::ReadRCStatusInfo(true);
	if (tempList.isEmpty()) {
		tempList = LAPI::GetRCStatusInfo();
	}
	updateRCStatusInfo(tempList);
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
	QByteArray text = LBLUIHelper::hexStrToByteArray(ui->textBrowserReg->toPlainText());
	buffer.replace(0, length > text.size() ? text.size() : length, text);
	LAPI::EResult ret = LAPI::WriteRCFPGARegister(port, module, addr, buffer);
	/*if (LAPI::EResult::ER_Success != LAPI::WriteRCFPGARegister(port, module, addr, buffer)) {
		QMessageBox::information(NULL, tr("提示"), \
			tr("寄存器写入失败."), QMessageBox::Yes, QMessageBox::Yes);
	}*/
	Core::ICore::showMessageLAPIResult(ret);
}

void MCReceiveCard::on_btnRegImport_clicked()
{
	QString selectFilter;
	QString fileName = QFileDialog::getOpenFileName(this,
		tr("Select File"),
		App::lastOpenPath,
		QString("%1").arg(Utils::FileFilter::BINPARAM_FILTER),
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
		QString("%1").arg(Utils::FileFilter::BINPARAM_FILTER));
	if (fileName.isEmpty()) {
		return;
	}
	QFile file(fileName);
	if (!file.open(QIODevice::WriteOnly)) {
		QMessageBox::information(NULL, tr("提示"), \
			tr("文件打开失败."), QMessageBox::Yes, QMessageBox::Yes);
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
