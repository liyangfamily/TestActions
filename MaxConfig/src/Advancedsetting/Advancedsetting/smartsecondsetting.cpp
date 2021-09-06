#include "smartsecondsetting.h"
#include "ui_smartsecondsetting.h"
#include <QDebug>
#include "advancedsetting.h"

SmartSecondSetting::SmartSecondSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SmartSecondSetting)
{
    ui->setupUi(this);

    InitForm();
}

SmartSecondSetting::~SmartSecondSetting()
{
    delete ui;
}

void SmartSecondSetting::InitForm()
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
}




void SmartSecondSetting::on_tableWidget_itemSelectionChanged()
{
    int column = ui->tableWidget->currentColumn();
    int row = ui->tableWidget->currentRow();

    if (row == 0)
    {
        bool result =  ui->tableWidget->item(row,column) == NULL || (ui->tableWidget->item(row,column) && ui->tableWidget->item(row,column)->text() == tr(""));
        if (result != NULL)
        {
            ui->tableWidget->setItem(row,column,new QTableWidgetItem(QString::number(Index)));
            ui->tableWidget->item(row,column)->setBackgroundColor(QColor(255,250,205));
            Index++;
        }
    }
    if (column == 0)
    {
        bool result =  ui->tableWidget->item(row,column) == NULL || (ui->tableWidget->item(row,column) && ui->tableWidget->item(row,column)->text() == tr(""));
        if (result != NULL)
        {
            Colindex++;
            ui->tableWidget->setItem(row,column,new QTableWidgetItem(QString::number(Colindex)));
            ui->tableWidget->item(row,column)->setBackgroundColor(QColor(255,50,50));
        }
    }

}







void SmartSecondSetting::on_EmptypushButton_clicked()
{
    Index++;
}

void SmartSecondSetting::on_RevokepushButton_clicked()
{
    if (Index == 0)
    {
        return;
    }
    bool ok ;
    bool Found = false;
    int i = 0;
    int j = 0;
    if (Colindex > 1)
    {
        for (i=0;i<Row;i++)
        {
            bool result =  ui->tableWidget->item(i,0) == NULL || (ui->tableWidget->item(i,0) && ui->tableWidget->item(i,0)->text() == tr(""));
            if (result == NULL)
            {
                unsigned char Number = QString(ui->tableWidget->item(i,0)->text()).toInt(&ok,10);
                if (Number == Colindex)
                {
                    ui->tableWidget->item(i,0)->setText(NULL);
                    ui->tableWidget->item(i,0)->setBackgroundColor(QColor(255,255,255));
                    Colindex--;
                    Found = true;
                    break;
                }
            }
        }
    }
    if (Colindex > 1)
    {
        return;
    }

    for (j=0;j<Row;j++)
    {
        if (Found) break;
        for (i=0;i<Col;i++)
        {
            bool result =  ui->tableWidget->item(j,i) == NULL || (ui->tableWidget->item(j,i) && ui->tableWidget->item(j,i)->text() == tr(""));
            if (result == NULL)
            {
                unsigned char Number = QString(ui->tableWidget->item(j,i)->text()).toInt(&ok,10);
                if (Number == (Index - 1))
                {
                    ui->tableWidget->item(j,i)->setText(NULL);
                    ui->tableWidget->item(j,i)->setBackgroundColor(QColor(255,255,255));
                    Index--;
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

void SmartSecondSetting::on_ClearpushButton_clicked()
{
    ui->tableWidget->clear();
    Index = 0;
    Colindex = 0;
}

void SmartSecondSetting::on_FinishpushButton_clicked()
{
    int Mode = 0;
    bool ok;
    int i=0;
    QByteArray GZPara = NULL;
    GZPara.resize(1024 * 2);
    switch (ModulePara[0x15]) {
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
            unsigned char Number = QString(ui->tableWidget->item(0,i)->text()).toInt(&ok,10);
            GZPara[i] = Number;
        }
    }
    for (int j=0;j<4;j++)
    {
        for (i=0;i<256;i++)
        {
            GZPara[j * 256 + i] = GZPara[i];
        }
    }
    for (i=0;i<Row;i++)
    {
        bool result =  ui->tableWidget->item(i,0) == NULL || (ui->tableWidget->item(i,0) && ui->tableWidget->item(i,0)->text() == tr(""));
        if (result == NULL)
        {
            unsigned char Number = QString(ui->tableWidget->item(i,0)->text()).toInt(&ok,10);
            GZPara[i + 1024] = Number;
        }
    }
    UniversalInterface::Writebin(LBLUIHelper::appParamDataLocation() + "//GZPara.bin",GZPara);
}

void SmartSecondSetting::on_ExportpushButton_clicked()
{

}
