#ifndef MCSCLISTITEMWIDGET_H
#define MCSCLISTITEMWIDGET_H

#include <QWidget>

namespace Ui {
class MCSCListItemWidget;
}

class MCSCListItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MCSCListItemWidget(QWidget *parent = nullptr);
    ~MCSCListItemWidget();

private:
    Ui::MCSCListItemWidget *ui;
};

#endif // MCSCLISTITEMWIDGET_H
