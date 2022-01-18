#ifndef MCDELEGATECLASS_H
#define MCDELEGATECLASS_H


#include <QStyledItemDelegate>

//! [0]
class SpinBoxDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    SpinBoxDelegate(QObject *parent = 0);

    void setMinimum(int v){
        minimum=v;
    }
    void setMaximum(int v){
        maximum=v;
    }

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override;

    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const override;

    void updateEditorGeometry(QWidget *editor,
        const QStyleOptionViewItem &option, const QModelIndex &index) const override;

private:
    int minimum=0;
    int maximum=100;
};
//! [0]

#endif // MCDELEGATECLASS_H
