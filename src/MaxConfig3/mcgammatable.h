#ifndef MCGAMMATABLE_H
#define MCGAMMATABLE_H

#include <QDialog>
#include "Utils/gammatablehelper.h"

namespace Ui {
class MCGammaTable;
}
class SpinBoxDelegate;
class MCGammaTable : public QDialog
{
    Q_OBJECT

public:
    explicit MCGammaTable(QWidget *parent = nullptr);
    ~MCGammaTable();
private:
    Utils::Gamma::GammaTableHelper m_gammaHelper;

private:
    Ui::MCGammaTable *ui;
    SpinBoxDelegate *m_intEditDelegate=nullptr;
    SpinBoxDelegate *m_decEditDelegate=nullptr;

private:
    void initGammaTable();
    void initGammaTableData();
    void buildGammaData();
    void updateGammaToTable();
    void updateGammaToHelper();

private slots:

    void on_btnHDR_clicked();
    void on_btnColorDepthBroaden_clicked();

    void on_btnReset_clicked();
    void on_btnImport_clicked();
    void on_btnExport_clicked();
    void on_btnSend_clicked();


    void slot_comboBoxGrayScaleLv_IndexChanged(int d);
};

#endif // MCGAMMATABLE_H
