#ifndef MCCUSSCLISTITEMWIDGET_H
#define MCCUSSCLISTITEMWIDGET_H

#include <QWidget>
#include <QEvent>
#include <LBLAbstractSCItem>

namespace Ui {
class MCCusSCListItemWidget;
}

class MCCusSCListItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MCCusSCListItemWidget(QWidget *parent = nullptr);
    ~MCCusSCListItemWidget();

private:
    Ui::MCCusSCListItemWidget *ui;

public:
    void setSCItem(LBL::SCItem::LBLAbstractSCItem* item);
    void updateItemWidget();

	bool isOnline();

protected:
    void enterEvent(QEvent* event);
    void leaveEvent(QEvent* event);
private:

private slots:
    void on_btnConnect_clicked();
    void on_toolBtnModifyName_clicked();
    void slot_toolBtnModifyName_editingFinished();
    void slot_toolBtnModifyName_returnPressed();
private:
    LBL::SCItem::LBLAbstractSCItem* m_item;
};

#endif // MCCUSSCLISTITEMWIDGET_H
