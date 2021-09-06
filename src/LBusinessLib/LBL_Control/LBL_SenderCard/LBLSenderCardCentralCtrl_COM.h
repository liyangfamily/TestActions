/****************************************************************************
**
** This Interface file is part of the SenderCard module of the LBL.
** 这个是LBL中的SenderCard模块中集控实现文件，该模块不对外开放
**
** 该接口文件包含LED系统中SenderCard集控相关操作,
** 抽取出发送卡集控中，部分对串口特殊处理的操作
**
****************************************************************************/
#ifndef CVTE_H_LBLSENDERCARDCENTRALCTRL_COM
#define CVTE_H_LBLSENDERCARDCENTRALCTRL_COM
#pragma once

#include "LBLSenderCardCentralCtrl.h"

namespace LBL
{
	namespace SC
	{
		template<class AbstractSenderCard_t, class ConSenderCard_t>
		class LBLSenderCardFactory; //前置声明，告诉编译器工厂为模板

		class LBL_SENDERCARD_EXPORT LBLSenderCardCentralCtrl_COM : public LBLSenderCardCentralCtrl
		{
			Q_DECLARE_PRIVATE(LBLSenderCardAbstract)

		public:
			~LBLSenderCardCentralCtrl_COM();

			/*********************************************************************************************************
			**其他
            *********************************************************************************************************/
			virtual quint16 writeBrightness(int value, bool sync, int msec) override;
			virtual quint16 readBrightness(bool sync, int msec) override;

		protected:
			void registerCallBack() override;
			quint16 onParseSCWriteBrightness(const QByteArray& data);
			quint16 onParseSCReadBrightness(const QByteArray& data);
		protected:
			LBLSenderCardCentralCtrl_COM(QObject* parent = 0); //禁用外部创建
			LBLSenderCardCentralCtrl_COM(LBLSenderCardAbstractPrivate& dd, QObject* parent = 0); // 允许子类通过它们自己的私有结构体来初始化
			friend class LBLSenderCardFactory<LBLSenderCardAbstract, LBLSenderCardCentralCtrl_COM>; //声明为一对一的好友关系，让工厂可以访问protected构造函数
		};
	}
}
#endif
