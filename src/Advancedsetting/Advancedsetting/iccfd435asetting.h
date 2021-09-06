#ifndef ICCFD435ASETTING_H
#define ICCFD435ASETTING_H

#include <QWidget>

namespace Ui {
class ICCFD435ASetting;
}

class ICCFD435ASetting : public QWidget
{
    Q_OBJECT

public:
    explicit ICCFD435ASetting(QWidget *parent = nullptr);
    ~ICCFD435ASetting();

private slots:
    void on_SettingpushButton_clicked();

    void on_CurrentGrayRcomboBox_currentIndexChanged(int index);

    void on_CurrentGrayGcomboBox_currentIndexChanged(int index);

    void on_CurrentGrayBcomboBox_currentIndexChanged(int index);

    void on_AdvancedSettingpushButton_clicked();

private:
    void InitForm();
    void LoadForm();
    void SetRegValue(int Num, int RGB, int hl, unsigned char value1, unsigned char value2);

    int GetLowGrayscale(unsigned char value);
    int GetColBlankAdj(unsigned char value);
    bool GetColBlankEnhance(unsigned char value);
    int GetColumnBlankTime(unsigned char value);
    int GetCouplingStrengthAdj(unsigned char value);
    int GetCouplingRangeAdj(unsigned char value);
    bool GetCouplingOptimization(unsigned char value);
    bool GetPreDriveEnablement(unsigned char value);
    int GetPreDriveMode(unsigned char value);
    int GetPreDriveTime(unsigned char value);
    int GetLowGrayStrength(unsigned char valuelow,unsigned char valuehigh);
    int GetLowGrayTime(unsigned char value);
    bool GetDynamicEnergySaving(unsigned char value);
    int GetWakeupSetting(unsigned char value);
    int GetOpenCircuitDetectionThreshold(unsigned char value);
    int GetOpenTestPointAdj(unsigned char value);
    bool GetOpenCircuitProtcetEnable(unsigned char value);
    bool GetOpenCircuitDynamicDetec(unsigned char value);
    int GetScanMode(unsigned char value);
    bool GetGclkDoubleAlong(unsigned char value);
    int GetConstantCurrentPoint(unsigned char value);
    int GetOutputResponse(unsigned char value);
    int GetPWMGraySetting(unsigned char value);
    bool GetLowGrayDisplayOptimization(unsigned char value);
    int GetLowGrayOptimizationMode(unsigned char value);
    int GetCurrentGear(unsigned char value);
    int GetCurrentGray(unsigned char value);
    int GetCurrentGraySetting(unsigned char value);



    void SetLowGrayscale(int index, int RGB);
    void SetColBlankAdj(int index, int RGB);
    void SetColBlankEnhance(bool check,int RGB);
    void SetColumnBlankTime(int index, int RGB);
    void SetCouplingStrengthAdj(int index, int RGB);
    void SetCouplingRangeAdj(int index, int RGB);
    void SetCouplingOptimization(bool check, int RGB);
    void SetPreDriveEnablement(bool check, int RGB);
    void SetPreDriveMode(int index, int RGB);
    void SetPreDriveTime(int index, int RGB);
    void SetLowGrayStrength(int index, int RGB);
    void SetLowGrayTime(int index, int RGB);
    void SetDynamicEnergySaving(bool check, int RGB);
    void SetWakeupSetting(int index, int RGB);
    void SetOpenCircuitDetectionThreshold(int index, int RGB);
    void SetOpenTestPointAdj(int index, int RGB);
    void SetOpenCircuitProtcetEnable(bool check, int RGB);
    void SetOpenCircuitDynamicDetec(bool check, int RGB);
    void SetScanMode(int index, int RGB);
    void SetGclkDoubleAlong(bool check, int RGB);
    void SetConstantCurrentPoint(int index, int RGB);
    void SetOutputResponse(int index, int RGB);
    void SetPWMGraySetting(int index, int RGB);
    void SetLowGrayDisplayOptimization(bool check, int RGB);
    void SetLowGrayOptimizationMode(int index, int RGB);
    void SetCurrentGear(int index, int RGB);
    void SetCurrentGray(int index, int RGB);
    void SetCurrentGraySetting(int index, int RGB);







private:
    Ui::ICCFD435ASetting *ui;
};

#endif // ICCFD435ASETTING_H
