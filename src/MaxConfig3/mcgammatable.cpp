#include "mcgammatable.h"
#include "ui_mcgammatable.h"
#include "app.h"
#include "Utils/utilsfilefilter.h"
#include "CustomWidget/mcdelegateclass.h"
#include "Core/icore.h"
#include "LAPIControl"

#include <QFileDialog>
#include <QMessageBox>

using namespace Utils::Gamma;

MCGammaTable::MCGammaTable(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MCGammaTable)
{
    ui->setupUi(this);
    setWindowFlag(Qt::WindowContextHelpButtonHint,false);
    initGammaTable();
    buildGammaData();
    updateGammaToTable();
}

MCGammaTable::~MCGammaTable()
{
    delete ui;
}

void MCGammaTable::initGammaTable()
{
    //ui->tableWidgetSRCInfo->setShowGrid(false);
    ui->tableWidget->setMouseTracking(true);
    //ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setEditTriggers(QAbstractItemView::DoubleClicked);

    QStringList header;
    header <<tr("Node")<< tr("R_Int") <<tr("R_Dec")<< tr("G_Int")<<tr("G_Dec") << tr("B_Int")<<tr("B_Dec");
    ui->tableWidget->setColumnCount(header.size()); //设置列数
    ui->tableWidget->setHorizontalHeaderLabels(header);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true); //设置充满表宽度
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //ui->tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    //ui->tableWidgetSRCInfo->horizontalHeader()->setFixedHeight(23); //设置表头的高度
    ui->tableWidget->horizontalHeader()->setDefaultSectionSize(150);
    ui->tableWidget->verticalHeader()->setVisible(false);

    m_intEditDelegate = new SpinBoxDelegate(this);
    ui->tableWidget->setItemDelegateForColumn(1, m_intEditDelegate);
    ui->tableWidget->setItemDelegateForColumn(3, m_intEditDelegate);
    ui->tableWidget->setItemDelegateForColumn(5, m_intEditDelegate);

    m_decEditDelegate = new SpinBoxDelegate(this);
    m_decEditDelegate->setMinimum(0);
    m_decEditDelegate->setMaximum(0xFF);
    ui->tableWidget->setItemDelegateForColumn(2, m_decEditDelegate);
    ui->tableWidget->setItemDelegateForColumn(4, m_decEditDelegate);
    ui->tableWidget->setItemDelegateForColumn(6, m_decEditDelegate);

    initGammaTableData();
}

void MCGammaTable::initGammaTableData()
{
    ui->dpinBoxGamma->setMinimum(1.0);
    ui->dpinBoxGamma->setMaximum(4.0);
    connect(ui->dpinBoxGamma,QOverload<double>::of(&QDoubleSpinBox::valueChanged),[=](double d){
        m_gammaHelper.setGammaValue(d);
        buildGammaData();
        updateGammaToTable();
    });

    ui->dSpinBoxSlopeValue->setMinimum(0);
    ui->dSpinBoxSlopeValue->setMaximum(30);
    connect(ui->dSpinBoxSlopeValue,QOverload<double>::of(&QDoubleSpinBox::valueChanged),[=](double d){
        m_gammaHelper.setGrayScaleSlope(d);
        buildGammaData();
        updateGammaToTable();
    });

    for(int i=10;i<=16;++i){
        ui->comboBoxGrayScaleLv->addItem(QString("%1bit").arg(i),i);
    }
    connect(ui->comboBoxGrayScaleLv,QOverload<int>::of(&QComboBox::currentIndexChanged),[=](int d){
        slot_comboBoxGrayScaleLv_IndexChanged(d);
    });

    ui->spinBoxMinGrayScale->setMinimum(0);
    ui->spinBoxMinGrayScale->setMaximum(0xFFFF);
    connect(ui->spinBoxMinGrayScale,QOverload<int>::of(&QSpinBox::valueChanged),[=](int d){
        m_gammaHelper.setGrayScaleMin(d);
        m_intEditDelegate->setMinimum(d);
        buildGammaData();
        updateGammaToTable();
    });

    ui->spinBoxMaxGrayScale->setMinimum(0);
    ui->spinBoxMaxGrayScale->setMaximum(0xFFFF);
    connect(ui->spinBoxMaxGrayScale,QOverload<int>::of(&QSpinBox::valueChanged),[=](int d){
        ui->spinBoxMinGrayScale->setMaximum(d);
        m_gammaHelper.setGrayScaleMax(d);
        m_intEditDelegate->setMaximum(d);
        buildGammaData();
        updateGammaToTable();
    });

    on_btnReset_clicked();
}

void MCGammaTable::buildGammaData()
{
    if(!m_gammaHelper.isVaild()){
        return;
    }

    QVector<GammaNode>& gammaTable=m_gammaHelper.buildGammaTable();
    if(m_gammaHelper.gammaNodeCount()!=(quint32)gammaTable.size()){
        return;
    }
}

void MCGammaTable::on_btnReset_clicked()
{
    ui->dpinBoxGamma->setValue(2.8);
    ui->dSpinBoxSlopeValue->setValue(0.5);

    ui->btnHDR->setChecked(false);
    on_btnHDR_clicked();

    ui->btnColorDepthBroaden->setChecked(false);
    on_btnColorDepthBroaden_clicked();

    ui->comboBoxGrayScaleLv->setCurrentIndex(3);
    slot_comboBoxGrayScaleLv_IndexChanged(3);

    ui->spinBoxMinGrayScale->setValue(0);
    ui->spinBoxMaxGrayScale->setValue(0xFFFF);

    buildGammaData();
    updateGammaToTable();
}

void MCGammaTable::on_btnImport_clicked()
{
    QString selectFilter;
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Select File"),
        App::lastOpenPath,
        QString("%1;;%2;;%3").arg(Utils::FileFilter::GAMMAPARAM_FILTER)
                                                    .arg(Utils::FileFilter::OLDGAMMAPARAM_FILTER)
                                                    .arg(Utils::FileFilter::GAMDATGAMMAPARAM_FILTER),
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

    bool bImport = false;
    if (selectFilter == Utils::FileFilter::GAMMAPARAM_FILTER) {
        bImport = m_gammaHelper.setRawGammaData(data);
    }
    else if (selectFilter == Utils::FileFilter::OLDGAMMAPARAM_FILTER) {
        bImport = m_gammaHelper.setRawGammaDataFromOld(data);
    }
    else if (selectFilter == Utils::FileFilter::GAMDATGAMMAPARAM_FILTER) {
        bImport = m_gammaHelper.setRawGammaDataFromGamdat(data);
    }
    if(bImport){
        if(m_gammaHelper.colorDepthBit()==GammaTableHelper::ECD_8bit){
             ui->btnHDR->setChecked(false);
        }
        if(m_gammaHelper.colorDepthBit()==GammaTableHelper::ECD_10bit){
             ui->btnHDR->setChecked(true);
        }
        if(m_gammaHelper.colorDepthBroadenBit()==GammaTableHelper::ECDB_16bit){
            ui->btnColorDepthBroaden->setChecked(false);
        }
        if(m_gammaHelper.colorDepthBroadenBit()==GammaTableHelper::ECDB_24bit){
            ui->btnColorDepthBroaden->setChecked(true);
        }
        updateGammaToTable();
    }
    if(!bImport){
        QMessageBox::information(NULL, tr("Tip"), \
                                 tr("Import failure."), QMessageBox::Yes, QMessageBox::Yes);
    }
    return;
}

void MCGammaTable::on_btnExport_clicked()
{
    updateGammaToHelper();

    QString selectFilter;
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), \
        App::lastOpenPath,
        QString("%1").arg(Utils::FileFilter::GAMMAPARAM_FILTER),
        &selectFilter);
    if (fileName.isEmpty()) {
        return;
    }
    App::lastOpenPath = fileName;
    App::writeConfig();

    QByteArray data;
    if (selectFilter == Utils::FileFilter::GAMMAPARAM_FILTER) {
        data = m_gammaHelper.rawGammaData();
    }

    if (data.isEmpty()) {
        QMessageBox::information(NULL, tr("Tip"), \
            tr("Generate failure."), QMessageBox::Yes, QMessageBox::Yes);
        return;
    }

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::information(NULL, tr("Tip"), \
            tr("File open failed."), QMessageBox::Yes, QMessageBox::Yes);
    }
    file.write(data);
    file.close();
    QMessageBox::information(NULL, tr("Tip"), \
        tr("Export success."), QMessageBox::Yes, QMessageBox::Yes);
}

#include <CustomWidget/mcprogressdialog.h>
void MCGammaTable::on_btnSend_clicked()
{
    ui->btnSend->setEnabled(false);
    MCProgressDialog bar(this);
    bar.setLabelText(tr("Sending Gamma..."));
    bar.show();
    updateGammaToHelper();
    QByteArray data=m_gammaHelper.rawGammaData();
    if(ui->btnHDR->isChecked()){
        LAPI::WriteSC10BitSource(ui->btnHDR->isChecked());
        quint16 fileType= LBLFileTransferPackage::EFileType::EFT_GammaFile_10Bit_24Bit;
        LAPI::EResult ret = LAPI::UpgradeFile(fileType,data,true,30000);
        if(ret==LAPI::EResult::ER_Success){
            bar.delayReset();
            LAPI::WriteSC24BitGammaSwitch(ui->btnColorDepthBroaden->isChecked());
            QMessageBox::information(this, tr("Tip"), \
                                     tr("Successful operation."), QMessageBox::Yes, QMessageBox::Yes);
        }
        Core::ICore::showMessageLAPIResult(ret,1000);
    }
    else
    {
        LAPI::WriteSC10BitSource(ui->btnHDR->isChecked());
        quint16 fileType= ui->btnColorDepthBroaden->isChecked()?\
                    LBLFileTransferPackage::EFileType::EFT_GammaFile_24Bit:LBLFileTransferPackage::EFileType::EFT_GammaFile_16Bit;
        LAPI::EResult ret = LAPI::UpgradeFile(fileType,data,true,30000);
        if(ret==LAPI::EResult::ER_Success){
            bar.delayReset();
            LAPI::WriteSC24BitGammaSwitch(ui->btnColorDepthBroaden->isChecked());
            QMessageBox::information(this, tr("Tip"), \
                                     tr("Successful operation."), QMessageBox::Yes, QMessageBox::Yes);
        }
        Core::ICore::showMessageLAPIResult(ret,1000);
    }
    bar.delayReset();
    ui->btnSend->setEnabled(true);
}

void MCGammaTable::updateGammaToTable()
{
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);

    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(m_gammaHelper.gammaNodeCount());//总行数
    QVector<GammaNode>& gammaTable=m_gammaHelper.gammaTable();
    for (int i = 0; i < (int)gammaTable.size(); ++i) {
        const GammaNode& currentNodeF = gammaTable[i];
        ui->tableWidget->setRowHeight(i, 40);

        ui->tableWidget->setItem(i, 0,\
                                 new QTableWidgetItem(QString::number(i+1)));
        ui->tableWidget->item(i, 0)->setTextAlignment(Qt::AlignCenter);

        ui->tableWidget->setItem(i, 1,\
                                 new QTableWidgetItem(QString::number(currentNodeF.r_int)));
        ui->tableWidget->item(i, 1)->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(i, 2,\
                                 new QTableWidgetItem(QString::number(currentNodeF.r_dec)));
        ui->tableWidget->item(i, 2)->setTextAlignment(Qt::AlignCenter);

        ui->tableWidget->setItem(i, 3, \
                                 new QTableWidgetItem(QString::number(currentNodeF.g_int)));
        ui->tableWidget->item(i, 3)->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(i, 4,\
                                 new QTableWidgetItem(QString::number(currentNodeF.g_dec)));
        ui->tableWidget->item(i, 4)->setTextAlignment(Qt::AlignCenter);

        ui->tableWidget->setItem(i, 5, \
                                 new QTableWidgetItem(QString::number(currentNodeF.b_int)));
        ui->tableWidget->item(i, 5)->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(i, 6,\
                                 new QTableWidgetItem(QString::number(currentNodeF.b_dec)));
        ui->tableWidget->item(i, 6)->setTextAlignment(Qt::AlignCenter);
    }
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
}

void MCGammaTable::updateGammaToHelper()
{
    if(!m_gammaHelper.isVaild()){
        return;
    }
    QVector<GammaNode>& gammaTable=m_gammaHelper.gammaTable();
    if(ui->tableWidget->rowCount() !=(int)gammaTable.size()){
        return;
    }
    for (int i = 0; i < (int)m_gammaHelper.gammaNodeCount(); ++i) {
        GammaNode& currentNodeF = gammaTable[i];
        currentNodeF.r_int=ui->tableWidget->item(i,1)->text().toUInt();
        currentNodeF.r_dec=ui->tableWidget->item(i,2)->text().toUInt();
        currentNodeF.g_int=ui->tableWidget->item(i,3)->text().toUInt();
        currentNodeF.g_dec=ui->tableWidget->item(i,4)->text().toUInt();
        currentNodeF.b_int=ui->tableWidget->item(i,5)->text().toUInt();
        currentNodeF.b_dec=ui->tableWidget->item(i,6)->text().toUInt();
    }
}

void MCGammaTable::on_btnHDR_clicked()
{
    m_gammaHelper.setColorDepthBit(ui->btnHDR->isChecked()?GammaTableHelper::ECD_10bit:GammaTableHelper::ECD_8bit);
    buildGammaData();
    updateGammaToTable();
}

void MCGammaTable::on_btnColorDepthBroaden_clicked()
{
    m_gammaHelper.setColorDepthBroadenBit(ui->btnColorDepthBroaden->isChecked()?GammaTableHelper::ECDB_24bit:GammaTableHelper::ECDB_16bit);
    buildGammaData();
    updateGammaToTable();
}

void MCGammaTable::slot_comboBoxGrayScaleLv_IndexChanged(int d)
{
    m_gammaHelper.setGrayscaleLevel(GammaTableHelper::EGrayscaleLevel(ui->comboBoxGrayScaleLv->itemData(d).toUInt()));
    ui->spinBoxMinGrayScale->setRange(m_gammaHelper.grayScaleMin(),m_gammaHelper.grayScaleMax());
    ui->spinBoxMinGrayScale->setValue(m_gammaHelper.grayScaleMin());
    ui->spinBoxMaxGrayScale->setRange(m_gammaHelper.grayScaleMin(),m_gammaHelper.grayScaleMax());
    ui->spinBoxMaxGrayScale->setValue(m_gammaHelper.grayScaleMax());
    buildGammaData();
    updateGammaToTable();
}

