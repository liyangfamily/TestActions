#ifndef ICXM11202GSETTING_H
#define ICXM11202GSETTING_H

#include <QDialog>

namespace Ui {
class ICXM11202GSetting;
}

class ICXM11202GSetting : public QDialog
{
    Q_OBJECT

public:
    explicit ICXM11202GSetting(QWidget *parent = nullptr);
    ~ICXM11202GSetting();

public:
    enum ELY11202RGB
    {
        ELC_R = 0,	//红
        ELC_G,		//绿
        ELC_B,		//蓝
    };
    //各分组序号
    enum ELY11202GroupIndex
    {
        ELI_RefreshRate = 4,	//刷新倍率
        ELI_Chip_Column = 5,	//max(40)
        ELI_Chip_Row = 6,		//max(36)

        ELI_Current_Adjust1 = 14,		//电流调节1  [7:6]
        ELI_Current_Adjust2 = 0xF0,		//电流调节2  --该值仅做为识别值，位置值同电流调节1. bit[5-0]

        ELI_Current_Gain = 17,			//电流增益
        ELI_Disapparate_Level = 20,		//消影等级
        ELI_LowGray_Compen1 = 23,		//低灰偏色补偿1
        ELI_LowGray_Compen2 = 26,		//低灰偏色补偿2
        ELI_LowGray_Even = 31,			//低灰均匀性
        ELI_DefectDetect_Level = 41,	//去坏点侦测等级

        ELI_GradualTransition_Optimize = 29,	//渐变过度优化
    };

public:
    //数据处理
    int GetDataToShow(ELY11202GroupIndex index, ELY11202RGB rgb);
    bool SetShowToData(ELY11202GroupIndex index, ELY11202RGB rgb, int value);

    void SetRegValue(int Num, int value);
    unsigned char GetRegValue(int Num);

    void ParamToShow();
    void ShowToParam();

    void SetToDefault();

    bool ShowInfo = false;

public:

    QByteArray ReadFile(QString filepath);
    bool WriteFile(QString filepath,QByteArray array);
    void Writebin(QString path, QByteArray bytes);
    QByteArray Readbin(QString path);
    QByteArray ReadGamdat(QString filepath);
    //void MessageBoxShow(QString title,QString str);
    QString filename;
    void SetGlobalReg();
    void GetGlobalReg();

public:
    QByteArray regpara;


private slots:
    void on_SettingBtn_clicked();

    void on_PresetApushButton_clicked();

    void on_PresetBpushButton_clicked();

    void on_PresetCpushButton_clicked();

    void on_PresetDpushButton_clicked();
    void on_DefectDetectionpushButton_clicked();
   // void on_ReadpushButton_clicked();

    void on_CurrentRegulation1RspinBox_valueChanged(int arg1);

    void on_CurrentRegulation2RspinBox_valueChanged(int arg1);

    void on_CurrentGainRspinBox_valueChanged(int arg1);

    void on_CurrentRegulation1GspinBox_valueChanged(int arg1);

    void on_CurrentRegulation2GspinBox_valueChanged(int arg1);

    void on_CurrentGainGspinBox_valueChanged(int arg1);

    void on_CurrentRegulation1BspinBox_valueChanged(int arg1);

    void on_CurrentRegulation2BspinBox_valueChanged(int arg1);

    void on_CurrentGainBspinBox_valueChanged(int arg1);

    void on_RefreshRatelspinBox_valueChanged(int arg1);

    void on_SaveFilepushButton_clicked();

    void on_LoadFilepushButton_clicked();

    void on_AdvancedSettingpushButton_clicked();

    void on_pushButton_Readback_clicked();

    void on_pushButton_ClearDeadPoint_clicked();

    void on_pushButton_Default_clicked();

    void on_UseDefectDetectioncheckBox_stateChanged(int arg1);

private:
    Ui::ICXM11202GSetting *ui;
};

#endif // ICXM11202GSETTING_H
