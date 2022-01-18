#ifndef MCCORRECT_H
#define MCCORRECT_H

#include <QWidget>
#include <Utils/testscreenhelper.h>
QT_BEGIN_NAMESPACE
class QButtonGroup;
QT_END_NAMESPACE
namespace Ui {
class MCCorrect;
}

class ConnectionFrame;
class ConnectionDiagramScene;
class MCCorrect : public QWidget
{
    Q_OBJECT

public:
    explicit MCCorrect(QWidget *parent = nullptr);
    ~MCCorrect();

private:
    Ui::MCCorrect *ui;
    ConnectionFrame *m_view;
    ConnectionDiagramScene *m_scene;
    QButtonGroup* m_portBtnGroup = nullptr;

private:
    void initViewAndScene();
    void loadCorrectFilePath(QString path);

protected:
    void resizeEvent(QResizeEvent *event) override;
public slots:
    void slot_ConnectItem();
    void slot_EnterNavigatPage();
    void on_btnConnectionRead_clicked();
    void slot_updateConnectionSetting();

private slots:
    void slot_paintStartPosChanged();
    void on_btnErase_clicked();
    void on_btnReload_clicked();
    void on_btnSend_clicked();
    void on_btnSave_clicked();
    void on_radioBtnSixPic_clicked();
    void on_radioBtnEightPic_clicked();
    void on_radioBtnLowGray_clicked();
    void on_toolBtnFullScreenData_clicked();

    void on_radioBtn10Pic_clicked();

private:
    TestScreenHelper m_testScrrenHelper;
};
#endif // MCCORRECT_H
