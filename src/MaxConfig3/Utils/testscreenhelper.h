#pragma once

#include <QDialog>
#include <QTimer>
#include "correctdatahelper.h"

class TestScreenHelper : public QDialog
{
	Q_OBJECT

public:
	TestScreenHelper(QWidget *parent = Q_NULLPTR);
	~TestScreenHelper();
    void showImageList(QList<QPair<CorrectDataHelper*, QSharedPointer<QByteArray>>> imageData,
                       const CorrectDataHelper::CorrectDataType type);
    void showFullScreenImageList(QList<QPair<CorrectDataHelper*, QSharedPointer<QByteArray>>> imageData,
                       const CorrectDataHelper::CorrectDataType type);

    static void setPaintStartPos(const QPoint& pt);
    static QPoint paintStartPos();
protected slots:
	void showImageTimeOut();
protected:
	void paintEvent(QPaintEvent *event) override;

private:
	QTimer m_showTimer;
	int m_drawImageIndex = 0;
    int m_drawImageCount = 0;
    QList<QPair<CorrectDataHelper*, QSharedPointer<QByteArray>>> m_imageData;
	QList<QPair<CorrectDataHelper*, QList<QImage>>> m_imageList;

    static QPoint m_paintStartPos;
    bool m_bFullScreen=false;
};
