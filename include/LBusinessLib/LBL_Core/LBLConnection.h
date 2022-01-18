/*********************************************************************************************************
** This file is part of the LBL_Core module of the LBL Toolkit.
*********************************************************************************************************/
#ifndef CVTE_H_LBLCONNECTION
#define CVTE_H_LBLCONNECTION
#pragma once

#include <LBL_Core/LBLCoreGlobal>
#include <LBL_Core/LAPIDef>
#include <LBL_Core/LBLJsonConnection.h>
#include <QObject>
#include <QMap>
#include <QRectF>
#include <QUuid>

class LBLConnectionPrivate;
class LBL_CORE_EXPORT LBLConnection : public LBLJsonConnection
{
    Q_DECLARE_PRIVATE(LBLConnection)
public:
    LBLConnection();
    ~LBLConnection();
    LBLConnection(const LBLConnection& ct);
    LBLConnection& operator=(const LBLConnection& ct);

public:
    void setRow(int value);
    int row() const;
    void setCol(int value);
    int col() const;
    void setModuleWidth(qint16 value);
    qint16 moduleWidth() const;
    void setModuleHeight(qint16 value);
    qint16 moduleHeight() const;

    //解析Json需要调用
    void calculateBaseInfo();

    //检查网口区域是否有效，对于Json一般不会有错，主要针对回读；解析连线关系都需要调用
    quint16 checkPortLoadArea(const QList<LBLSPort> &data);

    //解析回读连线关系
    quint16 parseConnectionData(const QByteArray &data);
    //构建下发连线关系
    QByteArray buildConnectionDataV1();
    QByteArray buildConnectionDataV2();
    QByteArray buildConnectionDataXA();
    QByteArray buildConnectionDataV0();

protected:
    //在checkPortLoadArea中调用，用于计算读取到的连线关系有几行几列
    void calculateRowAndCol();

protected:
    quint16 parseConnectionDataV1(const QByteArray &data);
    quint16 parseConnectionDataV2(const QByteArray &data);
    quint16 parseConnectionDataXA(const QByteArray &data);
    quint16 parseConnectionDataV0(const QByteArray &data);

private:
    void cloneConnection(const LBLConnection& ct);
private:
    QScopedPointer<LBLConnectionPrivate> d_ptr;
};

class LBL_CORE_EXPORT LBLConnectionCluster : public LBLJsonConnectionCluster
{
public:
    LBLConnectionCluster(){};
};

#endif
