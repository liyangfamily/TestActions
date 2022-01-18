 #ifndef ADVANCEDSETTING_H
#define ADVANCEDSETTING_H

#include <QDialog>
#include "AdvancedSetting_global.h"
#include "smartsetting.h"
#include "universalinterface.h"
#include <QMenuBar>

extern QByteArray ModulePara;
extern QByteArray ICPara;
extern QByteArray DataPara;



enum ChipType{
    CONVENTSIONALCHIP,
    ICN_2038S,
    MBI_5038,
    SUM_2017T,
    MBI_5124,
    SUM_2017,
    DP_3246,
    SUM_2030 = 0x81,
    SUM_2030T,
    SUM_2032,
    SUM_2131,
    SUM_2033,
    MBI_5252,
    MBI_5041B,
    MBI_5041Q,
    MBI_5042_5041,
    MBI_5042B,
    MBI_5043,
    MBI_5151,
    MBI_5047,
    MBI_5152,
    MBI_5153,
    MBI_5155,
    SUM_2035,
    SM_16259,
    MBI_5353,
    SUM_6086,
    LS_9935,
    ICN_2055_2069,
    CFD_335A,
    SUM_2035NEW,
    ICN_2153,
    FM_6363,
    FM_6565,
    LS_9935B,
    CFD_435A,
    CFD_555A,
    CFD_455A,
    ICND_2138,
    XM11202G,
    XM10480G,
};

namespace Ui {
class AdvancedSetting;
}




class ADVANCEDSETTING_EXPORT AdvancedSetting : public QDialog
{
    Q_OBJECT

public:
    explicit AdvancedSetting(QWidget *parent = nullptr);
    ~AdvancedSetting();



private slots:
    void on_SmartSettingBtn_clicked();
    void on_pushButton_clicked();
    void on_TXDcomboBox_currentIndexChanged(int index);
    void Showic();
    void showMOS();
    void initList();
    int ShowWorkFrequency(int address);
    void on_comboBox_6_currentIndexChanged(int index);
    void on_comboBox_2_currentIndexChanged(const QString &arg1);
    void on_comboBox_3_currentIndexChanged(int index);
    void on_comboBox_5_currentIndexChanged(const QString &arg1);
    void on_comboBox_4_currentIndexChanged(int index);
    void on_spinBox_valueChanged(int arg1);
    void on_spinBox_2_valueChanged(int arg1);
    void on_spinBox_3_valueChanged(int arg1);
    void on_comboBox_7_currentIndexChanged(int index);
    void on_spinBox_5_valueChanged(int arg1);
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    int VisionRefresh();
    void on_checkBox_clicked(bool checked);
    void on_rgbChangeBtn_clicked();
    void on_dataGroupBtn_clicked();
    void on_checkBox_2_clicked(bool checked);
    void on_toolButton_clicked();
    void CreateAction();
    void on_spinBox_4_valueChanged(int arg1);
    void on_OtherpushButton_clicked();
//    void romoveAllItem (QComboBox *cb);

    void on_ReadpushButton_clicked();

    void on_pushButton_2_clicked();

    void on_SavepushButton_clicked();

    void on_ButtonColorGamdat_clicked();
    void WriteFrequencyDoubling(int Regnum, int ByteCount, int StartByte);

public slots:
    void ICconfigShow();
    void CurrentConfigShow();
    void MOSConfigShow();
    void FLASHConfig();
    void GrayFineProcessingShow();
    void ScanShow();

signals:
    void triggered();


public:
    QStringList DclkGclkList;
    bool ShowPara;
    bool InitCombobox;





public slots:
    void LoadingPara();





private:
    Ui::AdvancedSetting *ui;
};

#endif // ADVANCEDSETTING_H
