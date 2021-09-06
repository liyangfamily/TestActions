#include "mainwindow_new.h"
#include "ui_mainwindow_new.h"
#include "CustomWidget/mcelevatedclass.h"
#include "CustomWidget/mcsclistitemwidget.h"

MainWindow_New::MainWindow_New(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow_New)
{
    ui->setupUi(this);

    NavigateBarFirstBtn* testBtn=new NavigateBarFirstBtn("111",this);
    //testBtn->setProperty("sizePolicy",QVariant(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding)));
    ui->frameNavigatFirst->layout()->addWidget(testBtn);

    for(int i=0;i<10;++i){
        QListWidgetItem* pListWidgetItem = new QListWidgetItem(ui->listSenderCard);
        MCSCListItemWidget* item=new MCSCListItemWidget(ui->listSenderCard);
        ui->listSenderCard->setItemWidget(pListWidgetItem, item);
    }
    ui->comboBox->setView(new QListView());
    ui->progressBar_3->setFormat(QString::fromLocal8Bit("升级失败"));
}

MainWindow_New::~MainWindow_New()
{
    delete ui;
}

void MainWindow_New::on_pushButton_3_clicked()
{
    ui->progressBar_3->setHasError(!ui->progressBar_3->hasError());
}
