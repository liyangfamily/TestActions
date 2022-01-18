/****************************************************************************
**
** This Interface file is part of the SenderCardItem module of the LBusinessLib.
** 这个是LBusinessLib中AbstractSenderCardItem派生子类发送卡，该模块不对外开放
**
** 该接口文件为LED系统中2nd发送卡对象，用于管理2nd发送卡的业务和数据
**
****************************************************************************/
#ifndef CVTE_H_LBL_SENDERCARDITEM_2ND
#define CVTE_H_LBL_SENDERCARDITEM_2ND
#pragma once

#include "LBL_SenderCardItem/LBLAbstractSCItem.h"

namespace LBL
{
    namespace SCItem
    {
        template<class AbstractSenderCardItem_t, class ConSenderCardItem_t>
        class SenderCardItemFactory; //前置声明，告诉编译器工厂为模板

        class SenderCardItem_2ndPrivate;
        class LBL_SENDERCARDITEM_EXPORT SenderCardItem_2nd : public LBLAbstractSCItem
        {
            Q_DECLARE_PRIVATE(SenderCardItem_2nd)
        public:
            ~SenderCardItem_2nd();
            //发送卡属性
            virtual QString senderCardTag() const override;
            //发送卡相关
            quint16 writeBrightness(int value, bool sync, int msec) override;
            quint16 readBrightness(bool sync, int msec) override;
            int  getBrightness() override;

            //视频处理相关
            virtual quint16 writeHDMIByPassStatus(const quint8 value, bool sync, int msec) override;
            virtual quint16 readHDMIByPassStatus(bool sync, int msec) override;
            virtual quint16 getHDMIByPassStatus() override;

            virtual quint16 writeHDMIImageRatio(const quint8 value, bool sync, int msec) override;
            virtual quint16 readHDMIImageRatio(bool sync, int msec) override;
            virtual quint8  getHDMIImageRatio() override;

            virtual quint16 writeHDMIInputSource(const quint8 value, bool sync, int msec) override;
            virtual quint16 readHDMIInputSource(bool sync, int msec) override;
            virtual quint8  getHDMIInputSource() override;

            virtual quint16 writeHDMIImageContrast(const quint8 value, bool sync, int msec) override;
            virtual quint16 readHDMIImageContrast(bool sync, int msec) override;
            virtual quint8  getHDMIImageContrast() override;

            virtual quint16 writeHDMIImageColorTtemperature(const quint8 value, bool sync, int msec) override;
            virtual quint16 readHDMIImageColorTtemperature(bool sync, int msec) override;
            virtual quint8  getHDMIImageColorTtemperature() override;

            virtual quint16 writeHDMIImageBrightness(const quint8 value, bool sync, int msec) override;
            virtual quint16 readHDMIImageBrightness(bool sync, int msec) override;
            virtual quint8  getHDMIImageBrightness() override;

            virtual quint16 writeHDMIRGBGain(const int rValue, const int gValue, const int bValue, bool sync, int msec) override;
            virtual quint16 readHDMIRGBGain(bool sync, int msec) override;
            virtual QList<quint8> getHDMIRGBGain() override;

            virtual QByteArray GetEDIDData() override;
            virtual quint16 writeHDMIEDID(int dataGroupIndex, quint8* pDataBuff,int dataLen) override;

        protected:
            SenderCardItem_2nd(QObject* parent = 0); //禁用外部创建
            SenderCardItem_2nd(SenderCardItem_2ndPrivate& dd, QObject* parent = 0); // 允许子类通过它们自己的私有结构体来初始化
            bool registerControl() override;
            bool dispatcherPackage(const LBLEnginePackage& pack) override;
            friend class SenderCardItemFactory<LBLAbstractSCItem, SenderCardItem_2nd>; //声明为一对一的好友关系，让工厂可以访问protected构造函数
        };

    }
}
#endif
