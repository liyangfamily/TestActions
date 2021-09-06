#ifndef MCCUSSCLISTITEMWIDGET_H
#define MCCUSSCLISTITEMWIDGET_H

#include <QWidget>
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
private:

private slots:
    void on_btnConnect_clicked();
private:
    LBL::SCItem::LBLAbstractSCItem* m_item;
};

#endif // MCCUSSCLISTITEMWIDGET_H
