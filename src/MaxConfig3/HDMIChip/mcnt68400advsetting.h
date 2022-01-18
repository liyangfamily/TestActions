#ifndef MCNT68400ADVSETTING_H
#define MCNT68400ADVSETTING_H

#include <QWidget>
#include "LBL_Core/LAPIDefUI.h"

namespace Ui {
class MCNT68400AdvSetting;
}

class QButtonGroup;
class QGraphicsScene;
class QGraphicsRectItem;
class MCSplitWindowItem;
class MCNT68400AdvSetting : public QWidget
{
    Q_OBJECT

public:
    explicit MCNT68400AdvSetting(QWidget *parent = nullptr);
    ~MCNT68400AdvSetting();

private:
    Ui::MCNT68400AdvSetting *ui;
    QButtonGroup* m_zoomModeBtnGroup=nullptr;
    QGraphicsScene* m_windowScene=nullptr;
    QGraphicsRectItem* m_windowBgItem=nullptr;
    QList<MCSplitWindowItem*> m_allWindowItemList;
    MCSplitWindowItem* m_curOptWindowItem=nullptr;
protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    void initUI();
    void initGraphicsView();
    void updateUISettings();
    void updateMultiScreenSettings(LAPI::UI::EMultiScreenMode mode);
    void updateMultiScreenInputSource(const  QList<quint8>& list);
    void updateZoomMode(LAPI::UI::EImageRatio mode);
    void updateCustomWindowStatus();
    void updateOtherSettings();
    void updateGraphicsView(LAPI::UI::EMultiScreenMode mode);

    LAPI::UI::EInputSource translateInputSource(const QString& strSource);

    void blockingControlSignals(bool b);

    void addWindowItem(LAPI::UI::EHDMIChannel channel, QString source,QRectF rt,bool interact=true);
    void setWindowItemSouceText(LAPI::UI::EHDMIChannel channel,const QString& str);
private slots:
    void on_btnFullScreen_clicked();
    void on_btnDoubleScreen_clicked();
    void on_btnTripleScreen_clicked();
    void on_btnQuardrupleScreen_clicked();
    void on_btnCustomizeScreen_clicked();

    void slot_comboBoxScreen1IndexChanged(const QString& strSource);
    void slot_comboBoxScreen2IndexChanged(const QString& strSource);
    void slot_comboBoxScreen3IndexChanged(const QString& strSource);
    void slot_comboBoxScreen4IndexChanged(const QString& strSource);
    void slot_audioSourceChanged();

    void slot_WindowRectChanged(QRectF rt);
    void slot_CustomWindowInfoChanged();

    void slot_screenCheckBoxStatusChanged();

    void on_radioBtnZoom4_3_clicked();
    void on_radioBtnZoom16_9_clicked();
    void on_radioBtnZoomFull_clicked();

    void slot_OutputSourceChanged();

    void on_radioBtnPresetResolution_clicked();
    void on_radioBtnBoxSeries_clicked();
    void on_radioBtnCustomResolution_clicked();
    void on_btnResolutionSave_clicked();

    void on_btnReset_clicked();
    void on_btnRefresh_clicked();
    void on_btnSetEDID_clicked();
};

#endif // MCNT68400ADVSETTING_H
