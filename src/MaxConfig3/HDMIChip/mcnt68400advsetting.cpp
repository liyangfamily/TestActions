#include "mcnt68400advsetting.h"
#include "ui_mcnt68400advsetting.h"
#include <LAPI_Control/LAPIControl>
#include "Core/icore.h"
#include "ConnectionControl/mcsplitwindowitem.h"

#include <QMessageBox>
#include <QButtonGroup>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QTimer>

MCNT68400AdvSetting::MCNT68400AdvSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MCNT68400AdvSetting)
{
    ui->setupUi(this);
    setWindowFlag(Qt::WindowContextHelpButtonHint,false);
    setWindowFlag(Qt::WindowMinMaxButtonsHint,true);
    this->resize(650,670);
    initUI();
}

MCNT68400AdvSetting::~MCNT68400AdvSetting()
{
    delete ui;
}

void MCNT68400AdvSetting::resizeEvent(QResizeEvent *event)
{
    ui->SplitScreengraphicsView->fitInView(m_windowScene->sceneRect(),Qt::KeepAspectRatio);
}

void MCNT68400AdvSetting::initUI()
{
    initGraphicsView();
    connect(ui->hSliderContrast, SIGNAL(valueChanged(int)), ui->spinBoxContrast, SLOT(setValue(int)));
    connect(ui->spinBoxContrast, QOverload<int>::of(&QSpinBox::valueChanged), [=](int d){
        ui->hSliderContrast->setValue(d);
        LAPI::WriteHDMIImageContrast(d);
    });

    connect(ui->hSliderSharpness, SIGNAL(valueChanged(int)), ui->spinBoxSharpness, SLOT(setValue(int)));
    connect(ui->spinBoxSharpness, QOverload<int>::of(&QSpinBox::valueChanged), [=](int d){
        ui->hSliderSharpness->setValue(d);
        LAPI::WriteHDIMISharpness(d,LAPI::UI::EHDMIChannel::EHC_All,false);
    });


    connect(ui->hSliderVolume, SIGNAL(valueChanged(int)), ui->spinBoxVolume, SLOT(setValue(int)));
    connect(ui->spinBoxVolume, QOverload<int>::of(&QSpinBox::valueChanged), [=](int d){
        ui->hSliderVolume->setValue(d);
        LAPI::WriteHDIMIAudioVolume(d,LAPI::UI::EHDMIChannel::EHC_All,false);
    });
    connect(ui->checkBoxScreen1,&QCheckBox::stateChanged,this,&MCNT68400AdvSetting::slot_screenCheckBoxStatusChanged);
    connect(ui->checkBoxScreen2,&QCheckBox::stateChanged,this,&MCNT68400AdvSetting::slot_screenCheckBoxStatusChanged);
    connect(ui->checkBoxScreen3,&QCheckBox::stateChanged,this,&MCNT68400AdvSetting::slot_screenCheckBoxStatusChanged);
    connect(ui->checkBoxScreen4,&QCheckBox::stateChanged,this,&MCNT68400AdvSetting::slot_screenCheckBoxStatusChanged);
    connect(ui->comboBoxScreen1, SIGNAL(activated(const QString&)), this, SLOT(slot_comboBoxScreen1IndexChanged(const QString&)));
    connect(ui->comboBoxScreen2, SIGNAL(activated(const QString&)), this, SLOT(slot_comboBoxScreen2IndexChanged(const QString&)));
    connect(ui->comboBoxScreen3, SIGNAL(activated(const QString&)), this, SLOT(slot_comboBoxScreen3IndexChanged(const QString&)));
    connect(ui->comboBoxScreen4, SIGNAL(activated(const QString&)), this, SLOT(slot_comboBoxScreen4IndexChanged(const QString&)));

    connect(ui->comboBoxAudioSource,QOverload<int>::of(&QComboBox::currentIndexChanged), \
            this, &MCNT68400AdvSetting::slot_audioSourceChanged);

    m_zoomModeBtnGroup=new QButtonGroup(this);
    m_zoomModeBtnGroup->addButton(ui->radioBtnZoom4_3);
    m_zoomModeBtnGroup->addButton(ui->radioBtnZoom16_9);
    m_zoomModeBtnGroup->addButton(ui->radioBtnZoomFull);
    m_zoomModeBtnGroup->setExclusive(true);

    ui->radioBtnCustomResolution->setChecked(true);
    on_radioBtnCustomResolution_clicked();
    ui->radioBtnBoxSeries->setEnabled(false);

    ui->comboBoxPresetResolutuion->addItem("3840*2160",QSize(3840,2160));
    ui->comboBoxPresetResolutuion->addItem("2560*1440",QSize(2560,1440));
    ui->comboBoxPresetResolutuion->addItem("1920*1080",QSize(1920,1080));
    ui->comboBoxPresetResolutuion->addItem("1600*900",QSize(1600,900));
    ui->comboBoxPresetResolutuion->addItem("1280*720",QSize(1280,720));

    ui->spinBoxWidth->setRange(1,0xFFFF);
    ui->spinBoxHeight->setRange(1,0xFFFF);

    ui->spinBoxCusWindowX->setRange(0,0xFFFF);
    connect(ui->spinBoxCusWindowX, QOverload<int>::of(&QSpinBox::valueChanged),this,&MCNT68400AdvSetting::slot_CustomWindowInfoChanged);
    ui->spinBoxCusWindowY->setRange(0,0xFFFF);
    connect(ui->spinBoxCusWindowY, QOverload<int>::of(&QSpinBox::valueChanged),this,&MCNT68400AdvSetting::slot_CustomWindowInfoChanged);
    ui->spinBoxCusWindowWidth->setRange(0,0xFFFF);
    connect(ui->spinBoxCusWindowWidth, QOverload<int>::of(&QSpinBox::valueChanged),this,&MCNT68400AdvSetting::slot_CustomWindowInfoChanged);
    ui->spinBoxCusWindowHeight->setRange(0,0xFFFF);
    connect(ui->spinBoxCusWindowHeight, QOverload<int>::of(&QSpinBox::valueChanged),this,&MCNT68400AdvSetting::slot_CustomWindowInfoChanged);

    ui->comboBoxOutputHDMI1->addItem("HDMI 1",LAPI::UI::EOutputSource::EOS_HDMI1);
    ui->comboBoxOutputHDMI1->addItem("HDMI 2",LAPI::UI::EOutputSource::EOS_HDMI2);
    ui->comboBoxOutputHDMI1->addItem("HDMI 3",LAPI::UI::EOutputSource::EOS_HDMI3);
    ui->comboBoxOutputHDMI1->addItem("Same Screen",LAPI::UI::EOutputSource::EOS_SameScreen);
    connect(ui->comboBoxOutputHDMI1, QOverload<int>::of(&QComboBox::currentIndexChanged), \
            this, &MCNT68400AdvSetting::slot_OutputSourceChanged);

    ui->comboBoxOutputHDMI2->addItem("HDMI 1",LAPI::UI::EOutputSource::EOS_HDMI1);
    ui->comboBoxOutputHDMI2->addItem("HDMI 2",LAPI::UI::EOutputSource::EOS_HDMI2);
    ui->comboBoxOutputHDMI2->addItem("HDMI 3",LAPI::UI::EOutputSource::EOS_HDMI3);
    ui->comboBoxOutputHDMI2->addItem("Same Screen",LAPI::UI::EOutputSource::EOS_SameScreen);
    connect(ui->comboBoxOutputHDMI2, QOverload<int>::of(&QComboBox::currentIndexChanged), \
            this, &MCNT68400AdvSetting::slot_OutputSourceChanged);

    ui->comboBoxOutputDP->addItem("HDMI 1",LAPI::UI::EOutputSource::EOS_HDMI1);
    ui->comboBoxOutputDP->addItem("HDMI 2",LAPI::UI::EOutputSource::EOS_HDMI2);
    ui->comboBoxOutputDP->addItem("HDMI 3",LAPI::UI::EOutputSource::EOS_HDMI3);
    ui->comboBoxOutputDP->addItem("Android",LAPI::UI::EOutputSource::EOS_Android);
    ui->comboBoxOutputDP->addItem("DP",LAPI::UI::EOutputSource::EOS_DP);
    ui->comboBoxOutputDP->addItem("Same Screen",LAPI::UI::EOutputSource::EOS_SameScreen);
    connect(ui->comboBoxOutputDP, QOverload<int>::of(&QComboBox::currentIndexChanged), \
            this, &MCNT68400AdvSetting::slot_OutputSourceChanged);

    QTimer::singleShot(10,[=](){
         on_btnRefresh_clicked();
    });
}

#include "Utils/graphicstheme.h"
using namespace Utils::GraphicsTheme;

void MCNT68400AdvSetting::initGraphicsView()
{
    m_windowScene=new QGraphicsScene(this);
    m_windowScene->setSceneRect(QRectF(0,0,3840,2160));
    //m_windowScene->setBackgroundBrush(QBrush(Qt::yellow));
    ui->SplitScreengraphicsView->setRenderHint(QPainter::Antialiasing, true);
    ui->SplitScreengraphicsView->setDragMode(QGraphicsView::RubberBandDrag);
    ui->SplitScreengraphicsView->setOptimizationFlags(QGraphicsView::DontSavePainterState);
    ui->SplitScreengraphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    ui->SplitScreengraphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

    ui->SplitScreengraphicsView->setSceneRect(0, 0, 3840, 2160);
    ui->SplitScreengraphicsView->centerOn(0, 0);
    ui->SplitScreengraphicsView->setScene(m_windowScene);

    m_windowBgItem= m_windowScene->addRect(QRectF(0,0,3840,2160),QPen(Qt::red),QBrush(Qt::gray));

    QTimer::singleShot(1,[=](){
        ui->SplitScreengraphicsView->fitInView(QRectF(0,0,3840,2160),Qt::KeepAspectRatio);
    });
}

void MCNT68400AdvSetting::updateUISettings()
{
    blockingControlSignals(true);
    updateCustomWindowStatus();
    updateMultiScreenSettings(LAPI::GetHDMIMultiScreenMode());
    updateMultiScreenInputSource(LAPI::GetHDMIMultiScreenInputSource());

    updateZoomMode(LAPI::GetHDMIImageRatio());
    updateOtherSettings();
    updateGraphicsView(LAPI::GetHDMIMultiScreenMode());
    blockingControlSignals(false);
}

void MCNT68400AdvSetting::updateMultiScreenSettings(LAPI::UI::EMultiScreenMode mode)
{
    ui->checkBoxScreen1->setVisible(false);
    ui->checkBoxScreen2->setVisible(false);
    ui->checkBoxScreen3->setVisible(false);
    ui->checkBoxScreen4->setVisible(false);

    ui->frame_2->setVisible(false);

    ui->radioBtnZoom4_3->setEnabled(false);
    ui->radioBtnZoom16_9->setEnabled(false);
    ui->radioBtnZoomFull->setEnabled(false);
    QStringList strAudioSrc;
    bool bScreen1=false,bScreen2=false,bScreen3=false,bScreen4=false;
    switch (mode)
    {
    case LAPI::UI::EMSM_None:
    {
        bScreen1=true;
        strAudioSrc << tr("Screen 1");
        ui->btnFullScreen->setChecked(bScreen1);

        ui->radioBtnZoom4_3->setEnabled(true);
        ui->radioBtnZoom16_9->setEnabled(true);
        ui->radioBtnZoomFull->setEnabled(true);
    }
        break;
    case LAPI::UI::EMSM_1Window:
        break;
    case LAPI::UI::EMSM_2Window:
        break;
    case LAPI::UI::EMSM_SideBySide:
    {
        bScreen1=true;
        bScreen2=true;
        strAudioSrc << tr("Screen 1") << tr("Screen 2");
        ui->btnDoubleScreen->setChecked(bScreen2);
    }
        break;
    case LAPI::UI::EMSM_3Divison1:
    {
        bScreen1=true;
        bScreen2=true;
        bScreen3=true;
        strAudioSrc << tr("Screen 1") << tr("Screen 2") << tr("Screen 3");
        ui->btnTripleScreen->setChecked(bScreen3);
    }
        break;
    case LAPI::UI::EMSM_3Division2:
        break;
    case LAPI::UI::EMSM_4Window:
    {
        bScreen1=true;
        bScreen2=true;
        bScreen3=true;
        bScreen4=true;
        strAudioSrc << tr("Screen 1") << tr("Screen 2") << tr("Screen 3") << tr("Screen 4");
        ui->btnQuardrupleScreen->setChecked(bScreen4);
    }
        break;
    case LAPI::UI::EMSM_UserMode:
    {
        bScreen1=true;
        bScreen2=true;
        bScreen3=true;
        bScreen4=true;
        ui->checkBoxScreen1->setVisible(bScreen1);
        ui->checkBoxScreen2->setVisible(bScreen1);
        ui->checkBoxScreen3->setVisible(bScreen1);
        ui->checkBoxScreen4->setVisible(bScreen1);
        ui->frame_2->setVisible(bScreen1);
        ui->btnCustomizeScreen->setChecked(bScreen1);
        if(ui->checkBoxScreen1->isChecked()){
            strAudioSrc.append(tr("Screen 1"));
        }
        if(ui->checkBoxScreen2->isChecked()){
            strAudioSrc.append(tr("Screen 2"));
        }
        if(ui->checkBoxScreen3->isChecked()){
            strAudioSrc.append(tr("Screen 3"));
        }
        if(ui->checkBoxScreen1->isChecked()){
            strAudioSrc.append(tr("Screen 4"));
        }
    }
        break;
    default:
        break;
    }
    ui->labelScreen1->setVisible(bScreen1);
    ui->comboBoxScreen1->setVisible(bScreen1);
    ui->labelScreen2->setVisible(bScreen2);
    ui->comboBoxScreen2->setVisible(bScreen2);
    ui->labelScreen3->setVisible(bScreen3);
    ui->comboBoxScreen3->setVisible(bScreen3);
    ui->labelScreen4->setVisible(bScreen4);
    ui->comboBoxScreen4->setVisible(bScreen4);

    ui->comboBoxAudioSource->clear();
    ui->comboBoxAudioSource->addItems(strAudioSrc);
}

void MCNT68400AdvSetting::updateMultiScreenInputSource(const QList<quint8> &list)
{
    const QList<quint8>& tempL=list;
    QStringList strScreenInputSources;

    ui->comboBoxScreen1->clear();
    ui->comboBoxScreen2->clear();
    ui->comboBoxScreen3->clear();
    ui->comboBoxScreen4->clear();

    strScreenInputSources.append("Android");
    strScreenInputSources.append("PC");
    strScreenInputSources.append("HDMI1");
    strScreenInputSources.append("HDMI2");
    strScreenInputSources.append("HDMI3");
    strScreenInputSources.append("DP");

    if(tempL.size()==4){
        ui->comboBoxScreen1->addItems(strScreenInputSources);
        ui->comboBoxScreen1->setCurrentIndex(tempL.at(0));
        ui->comboBoxScreen2->addItems(strScreenInputSources);
        ui->comboBoxScreen2->setCurrentIndex(tempL.at(1));
        ui->comboBoxScreen3->addItems(strScreenInputSources);
        ui->comboBoxScreen3->setCurrentIndex(tempL.at(2));
        ui->comboBoxScreen4->addItems(strScreenInputSources);
        ui->comboBoxScreen4->setCurrentIndex(tempL.at(3));
    }
}

void MCNT68400AdvSetting::updateZoomMode(LAPI::UI::EImageRatio mode)
{
    switch(mode)
    {
    case LAPI::UI::EIR_4_3:
        ui->radioBtnZoom4_3->setChecked(true);
        break;
    case LAPI::UI::EIR_16_9:
        ui->radioBtnZoom16_9->setChecked(true);
        break;
    case LAPI::UI::EIR_Full:
        ui->radioBtnZoomFull->setChecked(true);
        break;
    default:
        break;
    }
}

void MCNT68400AdvSetting::updateCustomWindowStatus()
{
    //if(ui->btnCustomizeScreen->isChecked()){
        LAPI::ReadHDIMIWindowShowStatus(LAPI::UI::EHDMIChannel::EHC_All);
        quint8 value=LAPI::GetHDIMIWindowShowStatus();
        ui->checkBoxScreen1->setChecked(value&0x01);
        ui->checkBoxScreen2->setChecked(value&0x02);
        ui->checkBoxScreen3->setChecked(value&0x04);
        ui->checkBoxScreen4->setChecked(value&0x08);
   //}
}

void MCNT68400AdvSetting::updateOtherSettings()
{
    quint8 audioSrc=LAPI::GetHDIMIAudioSrc();
    if(audioSrc<ui->comboBoxAudioSource->count()){
        ui->comboBoxAudioSource->setCurrentIndex(audioSrc);
    }

    QList<quint8> templist=LAPI::GetHDMIOutputSource();
    if(templist.size()==3){
        ui->comboBoxOutputHDMI2->setCurrentIndex(ui->comboBoxOutputHDMI2->findData(templist.at(0)));
        ui->comboBoxOutputHDMI1->setCurrentIndex(ui->comboBoxOutputHDMI1->findData(templist.at(1)));
        ui->comboBoxOutputDP->setCurrentIndex(ui->comboBoxOutputDP->findData(templist.at(2)));
    }

    ui->hSliderContrast->setValue(LAPI::GetHDMIImageContrast());
    ui->spinBoxContrast->setValue(LAPI::GetHDMIImageContrast());
    ui->hSliderSharpness->setValue(LAPI::GetHDIMISharpness());
    ui->spinBoxSharpness->setValue(LAPI::GetHDIMISharpness());
    ui->hSliderVolume->setValue(LAPI::GetHDIMIAudioVolume());
    ui->spinBoxVolume->setValue(LAPI::GetHDIMIAudioVolume());

    ui->radioBtnCustomResolution->setChecked(true);
    on_radioBtnCustomResolution_clicked();
    QSize displayArea=LAPI::GetHDIMIDisplayArea();
    ui->spinBoxWidth->setValue(displayArea.width());
    ui->spinBoxHeight->setValue(displayArea.height());
}

void MCNT68400AdvSetting::updateGraphicsView(LAPI::UI::EMultiScreenMode mode)
{
    QSize displayArea=LAPI::GetHDIMIDisplayArea();
    if(displayArea.isNull()||displayArea.isEmpty()){
        displayArea=QSize(3840,2560);
    }

    QRectF displayRt=QRectF(QPointF(0,0),displayArea);

    m_windowScene->setSceneRect(displayRt);
    ui->SplitScreengraphicsView->setSceneRect(displayRt);
    if(m_windowBgItem){
        m_windowBgItem->setRect(displayRt);
    }

    QList<QGraphicsItem *> itemList = m_windowScene->items();
    for (auto i = 0; i < itemList.size(); ++i) {
        if(itemList.at(i)->type()==MCSplitWindowItem::Type){
            m_windowScene->removeItem(itemList[i]);
            delete itemList[i];
        }
    }
    m_allWindowItemList.clear();
    switch (mode)
    {
    case LAPI::UI::EMSM_None:
    {
        addWindowItem(LAPI::UI::EHDMIChannel::EHC_1, ui->comboBoxScreen1->currentText(),displayRt,false);
    }
        break;
    case LAPI::UI::EMSM_1Window:
        break;
    case LAPI::UI::EMSM_2Window:
        break;
    case LAPI::UI::EMSM_SideBySide:
    {
        QRectF rt1=displayRt.adjusted(0,0,-displayArea.width()/2,0);
        QRectF rt2=displayRt.adjusted(displayArea.width()/2,0,0,0);
        addWindowItem(LAPI::UI::EHDMIChannel::EHC_1, ui->comboBoxScreen1->currentText(),rt1,false);
        addWindowItem(LAPI::UI::EHDMIChannel::EHC_2, ui->comboBoxScreen2->currentText(),rt2,false);
    }
        break;
    case LAPI::UI::EMSM_3Divison1:
    {
        QRectF rt1=displayRt.adjusted(0,0,-displayArea.width()/2,0);
        QRectF rt2=displayRt.adjusted(displayArea.width()/2,0,0,-displayArea.height()/2);
        QRectF rt3=displayRt.adjusted(displayArea.width()/2,displayArea.height()/2,0,0);
        addWindowItem(LAPI::UI::EHDMIChannel::EHC_1, ui->comboBoxScreen1->currentText(),rt1,false);
        addWindowItem(LAPI::UI::EHDMIChannel::EHC_2, ui->comboBoxScreen2->currentText(),rt2,false);
        addWindowItem(LAPI::UI::EHDMIChannel::EHC_3, ui->comboBoxScreen3->currentText(),rt3,false);
    }
        break;
    case LAPI::UI::EMSM_3Division2:
        break;
    case LAPI::UI::EMSM_4Window:
    {
        QRectF rt1=displayRt.adjusted(0,0,-displayArea.width()/2,-displayArea.height()/2);
        QRectF rt2=displayRt.adjusted(displayArea.width()/2,0,0,-displayArea.height()/2);
        QRectF rt3=displayRt.adjusted(0,displayArea.height()/2,-displayArea.width()/2,0);
        QRectF rt4=displayRt.adjusted(displayArea.width()/2,displayArea.height()/2,0,0);
        addWindowItem(LAPI::UI::EHDMIChannel::EHC_1, ui->comboBoxScreen1->currentText(),rt1,false);
        addWindowItem(LAPI::UI::EHDMIChannel::EHC_2, ui->comboBoxScreen2->currentText(),rt2,false);
        addWindowItem(LAPI::UI::EHDMIChannel::EHC_3, ui->comboBoxScreen3->currentText(),rt3,false);
        addWindowItem(LAPI::UI::EHDMIChannel::EHC_4, ui->comboBoxScreen4->currentText(),rt4,false);
    }
        break;
    case LAPI::UI::EMSM_UserMode:
    {
        QList<QRect> rtList;
        for(int i=LAPI::UI::EHDMIChannel::EHC_1;i<=LAPI::UI::EHDMIChannel::EHC_4;++i){
            LAPI::ReadAllHDMIAdvanceData_PIP(0,(LAPI::UI::EHDMIChannel)i);
            //LAPI::ReadHDIMIWindowPos((LAPI::UI::EHDMIChannel)i);
            QPoint pt=LAPI::GetHDIMIWindowPos();
            //LAPI::ReadHDIMIWindowSize((LAPI::UI::EHDMIChannel)i);
            QSize size=LAPI::GetHDIMIWindowSize();
            rtList.append(QRect(pt,size));
        }
        if(rtList.size()>0){
            addWindowItem(LAPI::UI::EHDMIChannel::EHC_1, ui->comboBoxScreen1->currentText(),rtList.at(0));
        }
        if(rtList.size()>1){
            addWindowItem(LAPI::UI::EHDMIChannel::EHC_2, ui->comboBoxScreen2->currentText(),rtList.at(1));
        }
        if(rtList.size()>2){
            addWindowItem(LAPI::UI::EHDMIChannel::EHC_3, ui->comboBoxScreen3->currentText(),rtList.at(2));
        }
        if(rtList.size()>3){
            addWindowItem(LAPI::UI::EHDMIChannel::EHC_4, ui->comboBoxScreen4->currentText(),rtList.at(3));
        }
    }
        break;
    default:
        break;
    }
    QTimer::singleShot(10,[=](){
        ui->SplitScreengraphicsView->fitInView(displayRt,Qt::KeepAspectRatio);
    });
}

LAPI::UI::EInputSource MCNT68400AdvSetting::translateInputSource(const QString &strSource)
{
    if (strSource == "Android")
    {
        return LAPI::UI::EIS_Android;
    }
    else if (strSource == "HDMI1")
    {
        return LAPI::UI::EIS_HDMI1;
    }
    else if (strSource == "HDMI2")
    {
        return LAPI::UI::EIS_HDMI2;
    }
    else if (strSource == "HDMI3")
    {
        return LAPI::UI::EIS_HDMI3;
    }
    else if (strSource == "DP")
    {
        return LAPI::UI::EIS_DP;
    }
    else if (strSource == "PC")
    {
        return LAPI::UI::EIS_PC;
    }
    return LAPI::UI::EIS_HDMI1;
}

void MCNT68400AdvSetting::blockingControlSignals(bool b)
{
    ui->btnFullScreen->blockSignals(b);
    ui->btnDoubleScreen->blockSignals(b);
    ui->btnTripleScreen->blockSignals(b);
    ui->btnQuardrupleScreen->blockSignals(b);
    ui->btnCustomizeScreen->blockSignals(b);

    ui->checkBoxScreen1->blockSignals(b);
    ui->checkBoxScreen2->blockSignals(b);
    ui->checkBoxScreen3->blockSignals(b);
    ui->checkBoxScreen4->blockSignals(b);

    ui->comboBoxScreen1->blockSignals(b);
    ui->comboBoxScreen2->blockSignals(b);
    ui->comboBoxScreen3->blockSignals(b);
    ui->comboBoxScreen4->blockSignals(b);

    ui->comboBoxAudioSource->blockSignals(b);

    ui->radioBtnZoom4_3->blockSignals(b);
    ui->radioBtnZoom16_9->blockSignals(b);
    ui->radioBtnZoomFull->blockSignals(b);

    ui->comboBoxOutputHDMI1->blockSignals(b);
    ui->comboBoxOutputHDMI2->blockSignals(b);
    ui->comboBoxOutputDP->blockSignals(b);

    ui->hSliderContrast->blockSignals(b);
    ui->hSliderSharpness->blockSignals(b);
    ui->hSliderVolume->blockSignals(b);
    ui->spinBoxContrast->blockSignals(b);
    ui->spinBoxSharpness->blockSignals(b);
    ui->spinBoxVolume->blockSignals(b);

    ui->radioBtnPresetResolution->blockSignals(b);
    ui->radioBtnBoxSeries->blockSignals(b);
    ui->radioBtnCustomResolution->blockSignals(b);

    ui->comboBoxPresetResolutuion->blockSignals(b);
    ui->comboBoxBoxSeries->blockSignals(b);
    ui->spinBoxRow->blockSignals(b);
    ui->spinBoxColumn->blockSignals(b);
    ui->spinBoxWidth->blockSignals(b);
    ui->spinBoxHeight->blockSignals(b);

    ui->spinBoxCusWindowX->blockSignals(b);
    ui->spinBoxCusWindowY->blockSignals(b);
    ui->spinBoxCusWindowWidth->blockSignals(b);
    ui->spinBoxCusWindowHeight->blockSignals(b);
}

void MCNT68400AdvSetting::addWindowItem(LAPI::UI::EHDMIChannel channel, QString source, QRectF rt,bool interact/*=true*/)
{
    MCSplitWindowItem* item=new MCSplitWindowItem(source,g_ModuleTheme.portColor(ModultItemTheme::PortColor(m_allWindowItemList.size())));
    connect(item,&MCSplitWindowItem::sig_WindowRectChanged,this,&MCNT68400AdvSetting::slot_WindowRectChanged);
    item->setPos(rt.topLeft());
    item->setRect(QRectF(QPointF(0,0),rt.size()));
    item->setZValue(10);
    item->setChannel(channel);
    if(!interact){
         item->setFlag(QGraphicsItem::ItemIsSelectable,false);
    }
    m_windowScene->addItem(item);
    m_allWindowItemList.append(item);
}

void MCNT68400AdvSetting::setWindowItemSouceText(LAPI::UI::EHDMIChannel channel, const QString &str)
{
    if(!m_windowScene){
        return;
    }
    QList<QGraphicsItem *> list1 = m_windowScene->items();
    for(auto item:list1){
        if(item->type()==MCSplitWindowItem::Type){
            MCSplitWindowItem* windowItem=qgraphicsitem_cast<MCSplitWindowItem*>(item);
            if(windowItem->channel()==channel){
                windowItem->setSourceName(str);
            }
        }
    }
}

void MCNT68400AdvSetting::on_btnFullScreen_clicked()
{
    LAPI::EResult ret = LAPI::WriteHDMIMultiScreenMode(LAPI::UI::EMSM_None);
    updateMultiScreenSettings(LAPI::UI::EMSM_None);
    updateGraphicsView(LAPI::UI::EMSM_None);
    Core::ICore::showMessageLAPIResult(ret);
}

void MCNT68400AdvSetting::on_btnDoubleScreen_clicked()
{
    LAPI::EResult ret = LAPI::WriteHDMIMultiScreenMode(LAPI::UI::EMSM_SideBySide);
    updateMultiScreenSettings(LAPI::UI::EMSM_SideBySide);
    updateGraphicsView(LAPI::UI::EMSM_SideBySide);
    Core::ICore::showMessageLAPIResult(ret);
}

void MCNT68400AdvSetting::on_btnTripleScreen_clicked()
{
    LAPI::EResult ret = LAPI::WriteHDMIMultiScreenMode(LAPI::UI::EMSM_3Divison1);
    updateMultiScreenSettings(LAPI::UI::EMSM_3Divison1);
    updateGraphicsView(LAPI::UI::EMSM_3Divison1);
    Core::ICore::showMessageLAPIResult(ret);
}

void MCNT68400AdvSetting::on_btnQuardrupleScreen_clicked()
{
    LAPI::EResult ret = LAPI::WriteHDMIMultiScreenMode(LAPI::UI::EMSM_4Window);
    updateMultiScreenSettings(LAPI::UI::EMSM_4Window);
    updateGraphicsView(LAPI::UI::EMSM_4Window);
    Core::ICore::showMessageLAPIResult(ret);
}

void MCNT68400AdvSetting::on_btnCustomizeScreen_clicked()
{
    LAPI::EResult ret = LAPI::WriteHDMIMultiScreenMode(LAPI::UI::EMSM_UserMode);
    updateMultiScreenSettings(LAPI::UI::EMSM_UserMode);
    //updateCustomWindowStatus();
    updateGraphicsView(LAPI::UI::EMSM_UserMode);
    Core::ICore::showMessageLAPIResult(ret);
}

void MCNT68400AdvSetting::slot_comboBoxScreen1IndexChanged(const QString &strSource)
{
    LAPI::EResult ret =  LAPI::WriteHDMIMultiScreenInputSource(this->translateInputSource(strSource), LAPI::UI::EHC_1);
    setWindowItemSouceText(LAPI::UI::EHC_1,strSource);
    Core::ICore::showMessageLAPIResult(ret);
}

void MCNT68400AdvSetting::slot_comboBoxScreen2IndexChanged(const QString &strSource)
{
    LAPI::EResult ret = LAPI::WriteHDMIMultiScreenInputSource(this->translateInputSource(strSource), LAPI::UI::EHC_2);
    setWindowItemSouceText(LAPI::UI::EHC_2,strSource);
    Core::ICore::showMessageLAPIResult(ret);
}

void MCNT68400AdvSetting::slot_comboBoxScreen3IndexChanged(const QString &strSource)
{
    LAPI::EResult ret = LAPI::WriteHDMIMultiScreenInputSource(this->translateInputSource(strSource), LAPI::UI::EHC_3);
    setWindowItemSouceText(LAPI::UI::EHC_3,strSource);
    Core::ICore::showMessageLAPIResult(ret);
}

void MCNT68400AdvSetting::slot_comboBoxScreen4IndexChanged(const QString &strSource)
{
    LAPI::EResult ret = LAPI::WriteHDMIMultiScreenInputSource(this->translateInputSource(strSource), LAPI::UI::EHC_4);
    setWindowItemSouceText(LAPI::UI::EHC_4,strSource);
    Core::ICore::showMessageLAPIResult(ret);
}

void MCNT68400AdvSetting::slot_audioSourceChanged()
{
    LAPI::EResult ret = LAPI::WriteHDIMIAudioSrc(ui->comboBoxAudioSource->currentIndex(), LAPI::UI::EHDMIChannel::EHC_All);
    Core::ICore::showMessageLAPIResult(ret);
}

void MCNT68400AdvSetting::slot_WindowRectChanged(QRectF rt)
{
    if(rt.isEmpty()){
        return;
    }
    m_curOptWindowItem = qobject_cast<MCSplitWindowItem*>(sender());
    ui->spinBoxCusWindowX->blockSignals(true);
    ui->spinBoxCusWindowY->blockSignals(true);
    ui->spinBoxCusWindowWidth->blockSignals(true);
    ui->spinBoxCusWindowHeight->blockSignals(true);
    ui->spinBoxCusWindowX->setValue(rt.topLeft().toPoint().x());
    ui->spinBoxCusWindowY->setValue(rt.topLeft().toPoint().y());
    ui->spinBoxCusWindowWidth->setValue(rt.toRect().width());
    ui->spinBoxCusWindowHeight->setValue(rt.toRect().height());
    QString posStr=QString("(%1,%2),(%3,%4)").arg(rt.topLeft().toPoint().x())
            .arg(rt.topLeft().toPoint().y())
            .arg(rt.toRect().width())
            .arg(rt.toRect().height());
    ui->spinBoxCusWindowX->blockSignals(false);
    ui->spinBoxCusWindowY->blockSignals(false);
    ui->spinBoxCusWindowWidth->blockSignals(false);
    ui->spinBoxCusWindowHeight->blockSignals(false);
}

void MCNT68400AdvSetting::slot_CustomWindowInfoChanged()
{
    if(m_windowScene){
        MCSplitWindowItem* windowItem=qgraphicsitem_cast<MCSplitWindowItem*>(m_curOptWindowItem);
        if(windowItem){
            QRectF rt(ui->spinBoxCusWindowX->value(),ui->spinBoxCusWindowY->value(),\
                      ui->spinBoxCusWindowWidth->value(),ui->spinBoxCusWindowHeight->value());
            windowItem->setPos(rt.topLeft());
            windowItem->externalChangeSize(rt.size());
        }
    }
}

void MCNT68400AdvSetting::slot_screenCheckBoxStatusChanged()
{
    quint8 status=0;
    LBLUIHelper::bitSet(status,0,ui->checkBoxScreen1->isChecked());
    LBLUIHelper::bitSet(status,1,ui->checkBoxScreen2->isChecked());
    LBLUIHelper::bitSet(status,2,ui->checkBoxScreen3->isChecked());
    LBLUIHelper::bitSet(status,3,ui->checkBoxScreen4->isChecked());
    LAPI::EResult ret = LAPI::WriteHDIMIWindowShowStatus(status,LAPI::UI::EHDMIChannel::EHC_All);
    Core::ICore::showMessageLAPIResult(ret);
}

void MCNT68400AdvSetting::on_radioBtnZoom4_3_clicked()
{
    LAPI::EResult ret = LAPI::WriteHDMIImageRatio(LAPI::UI::EIR_4_3, true);
    Core::ICore::showMessageLAPIResult(ret);
}

void MCNT68400AdvSetting::on_radioBtnZoom16_9_clicked()
{
    LAPI::EResult ret = LAPI::WriteHDMIImageRatio(LAPI::UI::EIR_16_9, true);
    Core::ICore::showMessageLAPIResult(ret);
}

void MCNT68400AdvSetting::on_radioBtnZoomFull_clicked()
{
    LAPI::EResult ret = LAPI::WriteHDMIImageRatio(LAPI::UI::EIR_Full, true);
    Core::ICore::showMessageLAPIResult(ret);
}

void MCNT68400AdvSetting::slot_OutputSourceChanged()
{
    LAPI::EResult ret = LAPI::WriteHDMIOutputSource(LAPI::UI::EOutputSource(ui->comboBoxOutputHDMI2->currentData().toInt()),\
                                LAPI::UI::EOutputSource(ui->comboBoxOutputHDMI1->currentData().toInt()),\
                                LAPI::UI::EOutputSource(ui->comboBoxOutputDP->currentData().toInt()),\
                                LAPI::UI::EHDMIChannel::EHC_All);
    Core::ICore::showMessageLAPIResult(ret);
}

void MCNT68400AdvSetting::on_radioBtnPresetResolution_clicked()
{
    ui->framePreSetResolution->setVisible(true);
    ui->frameBoxSeries->setVisible(false);
    ui->frameCustResolution->setVisible(false);
}

void MCNT68400AdvSetting::on_radioBtnBoxSeries_clicked()
{
    ui->framePreSetResolution->setVisible(false);
    ui->frameBoxSeries->setVisible(true);
    ui->frameCustResolution->setVisible(false);
}

void MCNT68400AdvSetting::on_radioBtnCustomResolution_clicked()
{
    ui->framePreSetResolution->setVisible(false);
    ui->frameBoxSeries->setVisible(false);
    ui->frameCustResolution->setVisible(true);
}

void MCNT68400AdvSetting::on_btnResolutionSave_clicked()
{
    if(ui->radioBtnPresetResolution->isChecked()){
        LAPI::EResult ret = LAPI::WriteHDIMIDisplayArea(ui->comboBoxPresetResolutuion->currentData().toSize(),LAPI::UI::EHDMIChannel::EHC_All,true);
        Core::ICore::showMessageLAPIResult(ret);
        return;
    }
    if(ui->radioBtnCustomResolution->isChecked()){
        LAPI::EResult ret = LAPI::WriteHDIMIDisplayArea(QSize(ui->spinBoxWidth->value(),ui->spinBoxHeight->value()),\
                                                        LAPI::UI::EHDMIChannel::EHC_All,true);
        Core::ICore::showMessageLAPIResult(ret);
        return;
    }
}

void MCNT68400AdvSetting::on_btnReset_clicked()
{
    int opt =QMessageBox::question(NULL, tr("Question"), \
                                      tr("Are you sure to reset?"), QMessageBox::Yes|QMessageBox::No, QMessageBox::Yes);
    if(opt==QMessageBox::Yes){
        LAPI::EResult ret = LAPI::ResetHDMISetting();
        Core::ICore::showMessageLAPIResult(ret);
    }
}

void MCNT68400AdvSetting::on_btnRefresh_clicked()
{
    ui->btnRefresh->setEnabled(false);
    //同步
    LAPI::ReadHDMIMultiScreenMode();
    LAPI::ReadHDMIMultiScreenInputSource();
    LAPI::ReadHDMIImageRatio(true);
    LAPI::ReadHDIMIAudioSrc(LAPI::UI::EHDMIChannel::EHC_All);

    LAPI::ReadHDMIOutputSource(LAPI::UI::EHDMIChannel::EHC_All);

    LAPI::ReadHDMIImageContrast(true);
    LAPI::ReadHDIMISharpness(LAPI::UI::EHDMIChannel::EHC_All);
    LAPI::ReadHDIMIAudioVolume(LAPI::UI::EHDMIChannel::EHC_All);

    LAPI::ReadHDIMIDisplayArea(LAPI::UI::EHDMIChannel::EHC_All);

    updateUISettings();
    ui->btnRefresh->setEnabled(true);
}

void MCNT68400AdvSetting::on_btnSetEDID_clicked()
{
    QByteArray EDIDData = LAPI::GetEDIDData();
    if(EDIDData.length() != 256)
    {
         Core::ICore::showMessageLAPIResult(LAPI::EResult::ER_INTECTRL_Fail_NoReason);
         return;
    }
    int Width = ui->spinBoxWidth->value();
    int Height = ui->spinBoxHeight->value();

    EDIDData[56] = Width & 0xFF;
    EDIDData[58] = EDIDData[58] | (Width << 4);

    EDIDData[59] = Height & 0xFF;
    EDIDData[61] = EDIDData[58] | (Height << 4);

    //checksum
    uchar checksum = 0;
    for (int i =0; i<127; ++i)
    {
        checksum += EDIDData[i];
    }
    EDIDData[127] = (uchar)(256 - checksum);

//    quint8* aaa = new quint8[256];
//    for (int i=0;i<256;i++)
//    {
//        aaa[i] = EDIDData[i];
//    }

    quint8 data[256]{0};
    memcpy(data,EDIDData,256);


    quint8 result = 0;
    for(int i = 0;i <16;i++)
    {
        result = LAPI::writeFacTest_UpdateEDID(i,data+(i+16),16,true,LBL_Defalut_SyncTimeout);
        if (LAPI::EResult::ER_Success != (quint16)result)
        {
            break;
        }
    }

    Core::ICore::showMessageLAPIResult((LAPI::EResult)result);


}
