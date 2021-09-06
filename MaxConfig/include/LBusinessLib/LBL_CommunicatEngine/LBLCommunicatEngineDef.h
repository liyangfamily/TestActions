﻿#pragma once

#include <QObject>
#include <QString>
#include <QUuid>

enum ECommunicatType
{
	ECT_NULL,
	ECT_UDP,
	ECT_TCP,
	ECT_COM,
};

enum EPackageFromType
{
	EPFT_NULL,
	EPFT_Send,
	EPFT_Receive,
};

//发送卡探测方式
enum EDeviceDetectType
{
	EDDT_NULL = 0x00,
	EDDT_AUTO = 0x01,	//自动探卡
	EDDT_Manual = 0x02,	//手动指定
	EDDT_Test = 0xFF, //FIXME:演示模式

};

//发送卡系列
enum ESenderCardStatus
{
	ESS_OffLine = 0x00,
	ESS_StandBy = 0x01, //待机
    ESS_OnlyAndroidOnline = 0x02,
	ESS_Online = 0x03, //在线
};

//发送卡系列
enum ESenderCardClass
{
	ESC_NULL = 0x00,
	ESC_2nd = 0x01,			//二代发送卡
	ESC_2nd_Plus = 0x02,	//二代Plus发送卡
	ESC_2nd_GZ = 0x03,	    //二代广州发送卡
	ESC_PCON600 = 0x04,		//PCON600
	ESC_Test = 0xFF,		//测试发送卡（预留）
};
//FIXME: 每个系列对应的具体发送卡列表枚举

//产品类型
enum EProductType
{
	EPT_NULL = 0x00,
	EPT_AIO = 0x01, //一体机
	EPT_DoubleAIO = 0x02, //双拼
	EPT_AndroidEngineeringScreen = 0x03, //带Android工程屏
	EPT_UnAndroidEngineeringScreen = 0x04, //不带Android工程屏
	EPT_Test = 0xFF,
};

#pragma pack(1)
/*探卡能读取到的信息,用于添加发送卡*/
//网络信息部分
typedef struct tagNetInfo
{
	QString ipAddr = 0;
	quint16 port = 0;
}SNetInfo;
//串口信息部分
typedef struct tagComInfo
{
	QString comName = 0;
}SComInfo;
typedef struct tagDetectItemInfo
{
	EDeviceDetectType detectType;
	ECommunicatType communType;

	ESenderCardStatus senderCardStatus;
	ESenderCardClass senderCardClass;
	EProductType productType;

	SNetInfo netInfo;
	SComInfo comInfo;

	QObject* socketObj = nullptr;
	QString hostName;

	quint8 uuidType;
	QUuid uuid;
	quint8 senderCardIndex;

	quint16 sourceDeviceType;
	tagDetectItemInfo()
	{
		this->clear();
	}
	void clear()
	{
		this->detectType = EDeviceDetectType::EDDT_NULL;
		this->communType = ECommunicatType::ECT_NULL;
		this->senderCardStatus = ESenderCardStatus::ESS_OffLine;
		this->senderCardClass = ESenderCardClass::ESC_NULL;
		this->productType = EProductType::EPT_NULL;
		this->netInfo.ipAddr.clear();
		this->netInfo.port = 0;
		this->comInfo.comName.clear();

		this->socketObj = nullptr;
		this->hostName.clear();

		uuidType = 0;
		uuid = 0;
		senderCardIndex = 0; 
		sourceDeviceType = 0;
	}
	void set(const tagDetectItemInfo& other)
	{
		this->detectType = other.detectType;
		this->communType = other.communType;
		this->senderCardStatus = other.senderCardStatus;
		this->senderCardClass = other.senderCardClass;
		this->productType = other.productType;
		this->netInfo.ipAddr = other.netInfo.ipAddr;
		this->netInfo.port = other.netInfo.port;
		this->comInfo.comName = other.comInfo.comName;

		this->socketObj = other.socketObj;
		this->hostName = other.hostName;

		if (other.uuidType != 0x00 && !other.uuid.isNull())
		{
			this->uuidType = other.uuidType;
			this->uuid = other.uuid;
		}
		this->senderCardIndex = other.senderCardIndex;
		this->sourceDeviceType = other.sourceDeviceType;
	}
	tagDetectItemInfo(const tagDetectItemInfo&ohter)
	{
		this->set(ohter);
	}

	tagDetectItemInfo& operator=(const tagDetectItemInfo&other)
	{
		this->set(other);
		return *this;
	}

	bool operator==(const tagDetectItemInfo& other)const
	{
		if (/*this->uuidType == other.uuidType&& //Uuid后续启用,不启用期间可能会出现问题，因为无法唯一识别
			this->uuid == other.uuid&&*/
			this->productType == other.productType&&
			this->senderCardClass == other.senderCardClass&&
			this->senderCardIndex == other.senderCardIndex&&
			this->socketObj == other.socketObj&&
			this->hostName==other.hostName)
		{
			return true;
		}
		else
		{
			return false;
		}
		//return memcmp(this, &other, sizeof(tagDetectItemInfo)) == 0 ? true : false;
	}

}SDetectItemInfo;
Q_DECLARE_METATYPE(SDetectItemInfo);
#pragma pack()
