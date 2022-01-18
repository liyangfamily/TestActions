#ifndef MCMS9570ADVSETTING_H
#define MCMS9570ADVSETTING_H

#include <QDialog>
#include "LBL_Core/LAPIDefUI.h"

namespace Ui {
class MCMS9570AdvSetting;
}

class MCMS9570AdvSetting : public QDialog
{
    Q_OBJECT

public:
    explicit MCMS9570AdvSetting(QWidget *parent = nullptr);
    ~MCMS9570AdvSetting();

private:
    Ui::MCMS9570AdvSetting *ui;

private:
    void initUI();
    void updateUISettings();
    void updateOtherSettings();

    void blockingControlSignals(bool b);

private slots:
    void on_radioBtnPresetResolution_clicked();
    void on_radioBtnBoxSeries_clicked();
    void on_radioBtnCustomResolution_clicked();
    void on_btnResolutionSave_clicked();

    void on_btnReset_clicked();
    void on_btnRefresh_clicked();
    void on_btnSetEDID_clicked();
};

#endif // MCMS9570ADVSETTING_H
