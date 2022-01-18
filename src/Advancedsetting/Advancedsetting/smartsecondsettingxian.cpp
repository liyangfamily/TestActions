#include "smartsecondsettingxian.h"
#include "ui_smartsecondsettingxian.h"
#include <QDebug>
#include "advancedsetting.h"
#include <qfiledialog.h>
#include "form.h"
#include <QTimer>
#include <LAPIControl>
#include <QCloseEvent>

SmartSecondSettingXian::SmartSecondSettingXian(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SmartSecondSettingXian)
{
    ui->setupUi(this);

    Qt::WindowFlags windowFlag  = Qt::Dialog;
    windowFlag                  |= Qt::WindowMinimizeButtonHint;
    windowFlag                  |= Qt::WindowMaximizeButtonHint;
    windowFlag                  |= Qt::WindowCloseButtonHint;
    setWindowFlags(windowFlag);

    InitForm();
    XAPara.resize(1024*2);

    ScreenX=0;
    ScreenY=0;
    ScreenWidth=480;
    ScreenHeight=270;

    wf.setGeometry(ScreenX,ScreenY,ScreenWidth,ScreenHeight);
    wf.ChangRGB(QColor(255,255,255),0);
    wf.update();
    wf.show();
    wf.setGeometry(ScreenX,ScreenY,ScreenWidth,ScreenHeight);
    wf.ChangRGB(QColor(255,255,255),0);
    wf.update();
    wf.show();

    QObject::connect(this, SIGNAL(SendSignal1()),this,SLOT(TimerSetPicture1()));
    QObject::connect(this, SIGNAL(SendSignal2()),this,SLOT(TimerSetPicture2()));

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(100);

    ui->radioButtonXA->setChecked(true);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
}
#ifdef Q_CC_MSVC
#pragma execution_character_set("utf-8")
#endif



SmartSecondSettingXian::~SmartSecondSettingXian()
{
    delete ui;
}
void SmartSecondSettingXian::InitForm()
{
    int LightWidth = (unsigned char)ModulePara[0x02] + (unsigned char)ModulePara[0x03] * 256;
    int LightHeight = (unsigned char)ModulePara[0x04] + (unsigned char)ModulePara[0x05] * 256;

    Col = LightWidth;
    Row = LightHeight;

    ui->tableWidget->setColumnCount(LightWidth);
    ui->tableWidget->setRowCount(LightHeight);


    ui->tableWidget->setShowGrid(true);
    ui->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background:rgb(240,240,240);color: black;}");//设置表头背景和字体颜色
    ui->tableWidget->verticalHeader()->setStyleSheet("QHeaderView::section{background:rgb(240,240,240);color: black;}");//设置表头背景和字体颜色

    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->verticalHeader()->setStretchLastSection(true);
    //ui->tableWidget->verticalHeader()->setVisible(false);
    //均分各列
    //ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->tableWidget->clearSelection();
    //ui->tableWidget->setStyleSheet("selection-background-color: rgb(255,250,205)");

    for (int i=0;i<ui->tableWidget->columnCount();i++)
    {
        ui->tableWidget->setColumnWidth(i,30);
    }
    for (int j=0;j<ui->tableWidget->rowCount();j++)
    {
        ui->tableWidget->setRowHeight(j,30);
    }

    scannum = (uchar)ModulePara[0x25];
}

void SmartSecondSettingXian::on_tableWidget_itemSelectionChanged()
{
    int column = ui->tableWidget->currentColumn();
    int row = ui->tableWidget->currentRow();

    //qDebug() <<"xend:"<<xend;
    //西安协议
    if (ui->radioButtonXA->isChecked())
    {
        if (Index <= ((uchar)ModulePara[0x1E] * 16))
        {
            bool result =  ui->tableWidget->item(row,column) == NULL || (ui->tableWidget->item(row,column) && ui->tableWidget->item(row,column)->text() == tr(""));
            if (result != NULL)
            {
                ui->tableWidget->setItem(row,column,new QTableWidgetItem(QString::number(Index)));
                ui->tableWidget->item(row,column)->setBackgroundColor(QColor(255,250,205));
                Index++;
                xend++;
            }
        }

        if (Index > ((uchar)ModulePara[0x1E] * 16))
        {
            timer->stop();
            wf.close();
            UniversalInterface::MessageBoxShow("",tr("描点完成"));
            return;
        }

    }
    //广州协议
    else
    {
        if (Index <= ((uchar)ModulePara[0x1E] * 16))
        {
            bool result =  ui->tableWidget->item(row,column) == NULL || (ui->tableWidget->item(row,column) && ui->tableWidget->item(row,column)->text() == tr(""));
            if (result != NULL)
            {
                ui->tableWidget->setItem(row,column,new QTableWidgetItem(QString::number(Index)));
                ui->tableWidget->item(row,column)->setBackgroundColor(QColor(255,250,205));
                Index++;
                xend++;
            }
        }
        else if (Index <= ((uchar)ModulePara[0x1E] * 16 + scannum - 1))
        {
            bool result =  ui->tableWidget->item(row,column) == NULL || (ui->tableWidget->item(row,column) && ui->tableWidget->item(row,column)->text() == tr(""));
            if (result != NULL)
            {
                ui->tableWidget->setItem(row,column,new QTableWidgetItem(QString::number(Index - (uchar)ModulePara[0x1E] * 16 + 1)));
                ui->tableWidget->item(row,column)->setBackgroundColor(QColor(255,0,0));
                Index++;
                xend++;
            }
        }
        if (Index > ((uchar)ModulePara[0x1E] * 16 + scannum - 1))
        {
            timer->stop();
            wf.close();
            UniversalInterface::MessageBoxShow("",tr("描点完成"));
            return;
        }
    }


}

void SmartSecondSettingXian::TimerSetPicture1()
{
    wf.ChangRGB(QColor(255,255,255),xend);
    wf.update();
    wf.show();
}

void SmartSecondSettingXian::TimerSetPicture2()
{
    wf.ChangRGB(QColor(255,255,255),xend+1);
    wf.update();
    wf.show();
}
void SmartSecondSettingXian::update()
{
    if (Sign)
    {
        emit SendSignal1();
        Sign = false;
    }
    else
    {
        emit SendSignal2();
        Sign = true;
    }
    wf.repaint();
}


void SmartSecondSettingXian::on_EmptypushButton_clicked()
{
    Index++;
    //西安协议
    if (ui->radioButtonXA->isChecked())
    {
        if (Index > ((uchar)ModulePara[0x1E] * 16))
        {
            timer->stop();
            wf.close();
            UniversalInterface::MessageBoxShow("",tr("描点完成"));
            return;
        }
    }
    else //广州协议
    {
        if (Index > ((uchar)ModulePara[0x1E] * 16 + scannum - 1))
        {
            timer->stop();
            wf.close();
            UniversalInterface::MessageBoxShow("",tr("描点完成"));
            return;
        }
    }
    ui->tableWidget->setFocus();
}

void SmartSecondSettingXian::on_RevokepushButton_clicked()
{
    if (Index == 0)
    {
        return;
    }
    bool ok ;
    bool Found = false;
    int i = 0;
    int j = 0;

    for (j=0;j<Row;j++)
    {
        if (Found) break;
        for (i=0;i<Col;i++)
        {
            bool result =  ui->tableWidget->item(j,i) == NULL || (ui->tableWidget->item(j,i) && ui->tableWidget->item(j,i)->text() == tr(""));
            if (result == NULL)
            {
                int Number = QString(ui->tableWidget->item(j,i)->text()).toInt(&ok,10);
                if (Number == (Index - 1))
                {
                    ui->tableWidget->item(j,i)->setText(NULL);
                    ui->tableWidget->item(j,i)->setBackgroundColor(QColor(20,32,47));
                    Index--;
                    xend--;
                    Found = true;
                    break;
                }
            }
        }
    }
    if ((!Found) && (Index > 1))
    {
        Index--;
    }
    ui->tableWidget->setFocus();
}

void SmartSecondSettingXian::on_ClearpushButton_clicked()
{
    Index = 1;
    xend = 0;
    ui->tableWidget->clear();
}

void SmartSecondSettingXian::on_FinishpushButton_clicked()
{
    //修改描点完成时的参数
    //箱体宽度，箱体高度，一组数据芯片级联数，扫描数
    int pw = (uchar)ModulePara[0x06] + (uchar)ModulePara[0x07] * 256;
    int ph = (uchar)ModulePara[0x08] + (uchar)ModulePara[0x09] * 256;
    int cn = (uchar)ModulePara[0x1E];
    int sn = (uchar)ModulePara[0x25];
    int mw = (uchar)ModulePara[0x02] + (uchar)ModulePara[0x03] * 256;
    int mh = (uchar)ModulePara[0x04] + (uchar)ModulePara[0x05] * 256;
    //IC组数
    ModulePara[0x1F] = (pw * ph) / (sn * cn * 16);



    //每个接口数据组
    ModulePara[0x26] = (mw * mh) / (sn * cn * 16);
    //有效接口个数
    ModulePara[0x27] = (pw * ph) / (mw * mh);

    //发送描点完成时修改的参数
    LAPI::EResult ret1 = LAPI::WriteModuleParam(0xFF,0xFF,ModulePara);
    if (ret1 == LAPI::EResult::ER_INTECTRL_Success)
    {
        UniversalInterface::Writebin(LBLUIHelper::appParamDataLocation() + "//ModulePara.bin",ModulePara);
    }
    else
    {
        UniversalInterface::MessageBoxShow(tr("描点"),tr("设置失败！"));
        return;
    }

    LAPI::EResult ret2;
    if (ui->radioButtonXA->isChecked())
    {
        GetTableXA();
        //发送描点表
        ret2 = LAPI::writeLinearTableFile(0xFF,0xFF,XAPara);
    }
    else if (ui->radioButtonGZ->isChecked())
    {
        GetTableGZ();
        //发送描点表
        ret2 = LAPI::writeLinearTableFile(0xFF,0xFF,GZPara);
    }
    else
        ret2 = LAPI::EResult::ER_INTECTRL_NULL;

    if (ret2 == LAPI::EResult::ER_INTECTRL_Success)
    {

        UniversalInterface::MessageBoxShow(tr("描点"),tr("设置成功！"));
    }
    else
    {
        UniversalInterface::MessageBoxShow(tr("描点"),tr("设置失败！"));
    }
}

void SmartSecondSettingXian::on_ExportpushButton_clicked()
{
    QString fileName;
    fileName = QFileDialog::getSaveFileName(this,tr("Open File"), "", tr("bin Files (*.bin)"));

    if (!fileName.isEmpty())
    {
        //fileName即是选择的文件名
        if (ui->radioButtonXA->isChecked())
        {
             GetTableXA();
             UniversalInterface::Writebin(fileName,XAPara);
        }
        if (ui->radioButtonGZ->isChecked())
        {
            GetTableGZ();
            UniversalInterface::Writebin(fileName,GZPara);
        }

        UniversalInterface::MessageBoxShow(tr("导出文件"),tr("文件导出成功"));
    }
    else
    {
        return;
    }
}

void SmartSecondSettingXian::GetTableXA()
{
    bool ok ;
    int i = 0;
    int j = 0;
    int index = 0;

    for (i=0;i<XAPara.length();i++)
    {
        XAPara[i] = 0;
    }

    //判断为行扫
    if (((ModulePara[0x23] >> 2) & 0x01) == 0x00)
    {
        //找出列最宽的列
        int ColMaxNumber = 0;
        for (j=0;j<Row;j++)
        {
            for (i=0;i<Col;i++ )
            {
                bool result =  ui->tableWidget->item(j,i) == NULL || (ui->tableWidget->item(j,i) && ui->tableWidget->item(j,i)->text() == tr(""));
                if (result == NULL)
                {
                    if (i > ColMaxNumber)
                    {
                        ColMaxNumber = i;
                    }
                }
            }
        }
        //qDebug() << "ColMaxNumber:" << ColMaxNumber;
        int RowIndex = 0;
        for (j=0;j<Row;j++)
        {
            bool NewRow = true;
            index = 0;
            for (i=0;i<Col;i++ )
            {
                bool result =  ui->tableWidget->item(j,i) == NULL || (ui->tableWidget->item(j,i) && ui->tableWidget->item(j,i)->text() == tr(""));
                if (result == NULL)
                {
                    if (NewRow)
                    {
                        RowIndex++;
                    }
                    int Number = QString(ui->tableWidget->item(j,i)->text()).toInt(&ok,10);
                    XAPara[((RowIndex - 1) * (ColMaxNumber + 1) + index) * 2 + 0] = ((Number - 1) / 16);
                    XAPara[((RowIndex - 1) * (ColMaxNumber + 1) + index) * 2 + 1] = ((Number - 1) % 16);
                    index++;

                    NewRow = false;
                }
            }
        }
    }
    else if (((ModulePara[0x23] >> 2) & 0x01) == 0x01)      //判断为列扫
    {
        //找出行最高的行
        int RowMaxNumber = 0;
        for (j=0;j<Col;j++)
        {
            for (i=0;i<Row;i++)
            {
                bool result =  ui->tableWidget->item(i,j) == NULL || (ui->tableWidget->item(i,j) && ui->tableWidget->item(i,j)->text() == tr(""));
                if (result == NULL)
                {
                    if (i > RowMaxNumber)
                    {
                        RowMaxNumber = i;
                    }
                }
            }
        }
        //qDebug() << "RowMaxNumber:"<<RowMaxNumber;
        int ColIndex = 0;
        for (j=0;j<Col;j++)
        {
            bool NewCol = true;
            index = 0;
            for (i=0;i<Row;i++ )
            {
                bool result =  ui->tableWidget->item(i,j) == NULL || (ui->tableWidget->item(i,j) && ui->tableWidget->item(i,j)->text() == tr(""));
                if (result == NULL)
                {
                    if (NewCol)
                    {
                        ColIndex++;
                    }
                    int Number = QString(ui->tableWidget->item(i,j)->text()).toInt(&ok,10);
                    XAPara[((ColIndex - 1) * (RowMaxNumber + 1) + index) * 2 + 0] = ((Number - 1) / 16);
                    XAPara[((ColIndex - 1) * (RowMaxNumber + 1) + index) * 2 + 1] = ((Number - 1) % 16);
                    index++;
                    NewCol = false;
                }
            }
        }
    }
    UniversalInterface::Writebin(LBLUIHelper::appParamDataLocation() + "//XAPara.bin",XAPara);
}

void SmartSecondSettingXian::GetTableGZ()
{
    int Mode = 0;
    bool ok;
    int i=0;
    //QByteArray GZPara = NULL;
    GZPara.resize(1024 * 2);
    qDebug() << "0x15:" <<(uchar)ModulePara[0x15];
    switch ((uchar)ModulePara[0x15]) {
    case 0:
        Mode=2;
        break;
    case 1:
        Mode=4;
        break;
    default:
        Mode=2;
        break;
    }

    for (i=0;i<GZPara.length();i++)
    {
        GZPara[i] = 0;
    }
    for (i=0;i<Col;i++)
    {
        bool result =  ui->tableWidget->item(0,i) == NULL || (ui->tableWidget->item(0,i) && ui->tableWidget->item(0,i)->text() == tr(""));
        if (result == NULL)
        {
            int Number = QString(ui->tableWidget->item(0,i)->text()).toInt(&ok,10);
            GZPara[i] = Number;
        }
    }
    for (int j=0;j<Mode;j++)
    {
        for (i=0;i<256;i++)
        {
            GZPara[j * 256 + i] = GZPara[i] + j * 256;
        }
    }
    for (i=0;i<Row;i++)
    {
        bool result =  ui->tableWidget->item(i,0) == NULL || (ui->tableWidget->item(i,0) && ui->tableWidget->item(i,0)->text() == tr(""));
        if (result == NULL)
        {
            int Number = QString(ui->tableWidget->item(i,0)->text()).toInt(&ok,10);
            GZPara[i + 1024] = Number;
        }
    }
    for (int j=0;j<32/Mode;j++)
    {
        for (i=0;i<64;i++)
        {
            GZPara[j * 64 + i + 1024] = GZPara[i + 1024] + j * 64;
        }
    }
    UniversalInterface::Writebin(LBLUIHelper::appParamDataLocation() + "//GZPara.bin",GZPara);
}



void SmartSecondSettingXian::closeEvent(QCloseEvent * e)
{
    Q_UNUSED(e);
    if (timer->isActive())
    {
        timer->stop();
        wf.close();
    }
}


