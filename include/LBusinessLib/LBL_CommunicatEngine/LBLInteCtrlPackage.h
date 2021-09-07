/*********************************************************************************************************
** This file is part of the LBL_CommunicatEngine module of the LBL Toolkit.
*********************************************************************************************************/
#ifndef CVTE_H_LBLINTECTRLPACKAGE
#define CVTE_H_LBLINTECTRLPACKAGE
#pragma once

#include <LBL_CommunicatEngine/LBLPackage>

class LBL_COMMUNICATENGINE_EXPORT LBLInteCtrlPackage : public LBLPackage
{
	friend class LBLPackageManager;
	friend class LBLPackageDispatcher;
public:
	enum ECommand
	{
		//通用指令
		EC_NULL_Penetrate=0xC011,

		//发送卡相关
		EC_Read_SCBrightness = 0xC105, //目前只有广州MCU调亮度用这条指令，其他全都是用的0xC21D，后续要MCU去改
		EC_Write_SCBrightness = 0xC107,
		EC_Read_SCFPGARegister = 0xC015,
		EC_Write_SCFPGARegister = 0xC013,
		EC_Write_Connection = 0xC133,
		EC_Read_Connection = 0xC135,
		EC_Write_ModuleParam = 0xC137,
		EC_Read_ModuleParam = 0xC139,
		EC_Read_MCUAppVersion = 0xC13D,
		EC_Read_MCUBootVersion = 0xC13F,
		EC_Write_SaveSCParam = 0xC1FF,

        //接收卡相关
        EC_Write_RCFPGARegister = 0xC01B,
        EC_Read_RCFPGARegister = 0xC01D,
		EC_Read_RCStatusInfo = 0xC13B,
		EC_Read_RCMonitorInfo=0xC141,
		EC_Write_SaveRCParam = 0xC1FD,


		//视频源相关
		EC_Read_VideoSourceVolume = 0xC201,
		EC_Write_VideoSourceVolume = 0xC203,
		EC_Read_VideoSourceByPass=0xC205,
		EC_Write_VideoSourceByPass=0xC207,
		EC_Read_VideoSourceRatio = 0xC20D,
		EC_Write_VideoSourceRatio = 0xC20F,
		EC_Read_VideoSource = 0xC211,
		EC_Write_VideoSource = 0xC213,
		EC_Read_VideoSourceContrast = 0xC215,
		EC_Write_VideoSourceContrast = 0xC217,
		EC_Read_VideoSourceColortemperature = 0xC219,
		EC_Write_VideoSourceColortemperature = 0xC21B,

		EC_Read_VideoSourceBrightness = 0xC21D, //特殊，实际不是调节的视频源，还是调节的发送卡
		EC_Write_VideoSourceBrightness = 0xC21F,

		EC_Read_VideoSourceRGain = 0xC221,
		EC_Write_VideoSourceRGain = 0xC223,
		EC_Read_VideoSourceGGain = 0xC225,
		EC_Write_VideoSourceGGain = 0xC227,
		EC_Read_VideoSourceBGain = 0xC229,
		EC_Write_VideoSourceBGain = 0xC22B,
		EC_Read_VideoSourceRGBGain = 0xC22D,
		EC_Write_VideoSourceRGBGain = 0xC22F,
        EC_Read_VideoSourceResolution = 0xC231, //0xC231 分辨率设置（仅9570）
        EC_Write_VideoSourceResolution = 0xC233, //0xC233 分辨率设置（仅9570）
        EC_Read_VideoSourceCombinationInfo = 0xC241, //0xC241 获取视频组合信息（仅68400）
        EC_Read_VideoSourceSceneMode = 0xC243, //0xC243 情景模式
        EC_Write_VideoSourceSceneMode = 0xC245, //0xC245 情景模式
        EC_Read_VideoSourceSplitScreenMode = 0xC247, //0xC247 分屏模式
        EC_Write_VideoSourceSplitScreenMode = 0xC249, //0xC249 分屏模式

		//通用设置
		EC_Read_AndroidIPInfo = 0xC301,
		EC_Write_AndroidIPInfo = 0xC303,
		EC_Read_AndroidVersion = 0xC311,
		EC_Read_OnlineStatus = 0xC313,
		EC_Read_SenderCardUuid = 0xC315,
		EC_Write_SenderCardUuid = 0xC317,
		EC_Read_AndroidGroupList = 0xC319, //Not yet implemented
		EC_Read_AndroidListInGroup = 0xC31B, //Not yet implemented
		EC_Read_AndroidAddGroup = 0xC31D, //Not yet implemented
		EC_Read_AndroidDeleteGroup = 0xC31F, //Not yet implemented
		EC_Read_AndroidMainControlTypeStatus = 0xC321, //Not yet implemented
		EC_Read_AndroidAllMainControlTypeStatus = 0xC323, //Not yet implemented
		EC_Write_AndroidMainControlTypeStatus = 0xC325, //Not yet implemented
		EC_Read_AndroidDoNotSleep = 0xC327, //0xC327 禁止Android进入深度休眠
		EC_Write_AndroidDoNotSleep = 0xC329, //0xC329 禁止Android进入深度休眠
		EC_Read_AndroidHotInfo = 0xC32B, //0xC32B 获取Android热点信息
		EC_Write_AndroidHotInfo = 0xC32D, //0xC32D 获取Android热点信息
		EC_Write_AndroidKeyEvent = 0xC333, //0xC333 按键事件
		EC_Read_AndroidDeviceName = 0xC335, //0xC335 设备名
		EC_Write_AndroidDeviceName = 0xC337, //0xC337 设备名

		//测试相关
		EC_Read_AndroidNetDeviceOnlineStatus = 0xC501, //0xC501 回读安卓连接网络设备在线状态
		EC_Read_AndroidSCEthLoopTestResults = 0xC503, //0xC503 回读发送卡网口自回环测试结果
		EC_Write_AndroidUDiskMountingStatus = 0xC505, //0xC505 回读Android U盘挂载状态
		EC_Write_AndroidStatOSDTest = 0xC507, //0xC507 请求开始测试OSD测试
		EC_Write_AndroidRelaySwitc = 0xC509, //0xC509 控制继电器开关
		EC_Write_AndroidEnterKeyTest = 0xC50B, //0xC50B 进入Android 按键板按键测试
		EC_Read_AndroidKeyTestResult = 0xC50D, //0xC50D 读取Android 按键板按键测试结果
		EC_Read_AndroidOpticalSensorParam = 0xC50F, //0xC50F 回读光感元件参数
		EC_Read_AndroidRouterStatus = 0xC511, //0xC511 回读路由器状态
		EC_Write_AndroidNetworkCardMACAddr = 0xC513, //0xC513 设置安卓网卡MAC地址
		EC_Write_AndroidPalyTestSound_1KHZ = 0xC515, //0xC515 播放测试声音（1KHZ）
		EC_Write_AndroidWIFIModuleScanTest = 0xC517, //0xC517 测试wifi模块扫描
		EC_Read_AndroidWIFIScanList = 0xC519, //0xC519 回读wifi扫描列表
		EC_Read_AndroidLoadPowerAmplifierChipParame = 0xC51B, //0xC51B 加载功放芯片参数
		EC_Read_AndroidCOMLoopTestResults = 0xC51D, //0xC51D 读取串口自回环测试结果
		EC_Write_AndroidEnterTestMode = 0xC530, //0xC530 10.14.进入工厂测试模式
		//
		EC_NULL = 0xFFFF,
	};

public:
	LBLInteCtrlPackage();
	LBLInteCtrlPackage(const QByteArray& data);
	virtual ~LBLInteCtrlPackage();

protected:
	/*********************build时需要获取**************************/
	//集控协议，总定义协议类型和版本
	quint8 CmdProtocolNum() const override;
	quint8 CmdProtocolVersion() const override; 
    quint16 CmdNum() const override {
        qDebug() << "LBLInteCtrlPackage::you need to implement CmdNum() into Subclass.";
        return quint16();
    }
	quint16 CmdRetNum() const override {
        return quint16(this->CmdNum() + 1);
	}

private:
	void defalutInit();
};

class LBL_COMMUNICATENGINE_EXPORT LBLPackageInteCtrl_Penetrate : public LBLInteCtrlPackage
{
	LBL_DECLARE_PACKAGECONSTRUCTOR(LBLPackageInteCtrl_Penetrate, LBLInteCtrlPackage)
public:
	LBLPackageInteCtrl_Penetrate(quint16 replyDataLength, quint16 maxWaitTime, const QByteArray& data);
	quint16 getOperationResult() const;
	QByteArray getReplyData() const;

	void  setReplyDataLength(quint16 length) {
		m_replyDataLength = length;
	}
	void  setmaxWaitTime(quint16 time) {
		m_maxWaitTime = time;
	}
	void setPenetrateData(const QByteArray& data){
		m_penetratData = data;
	}
	static const unsigned short PenetrateMaxWaitTime = 500; //500ms，默认值
protected:
	quint16 CmdNum() const override {
		return quint16(ECommand::EC_NULL_Penetrate);
	}
	QByteArray CmdContent() const override;
private:
	quint16 m_replyDataLength = 0;
	quint16 m_maxWaitTime= 0;
	QByteArray m_penetratData;
};

class LBL_COMMUNICATENGINE_EXPORT LBLPackageInteCtrl_DetectInfo : public LBLInteCtrlPackage
{
	LBL_DECLARE_PACKAGECONSTRUCTOR(LBLPackageInteCtrl_DetectInfo, LBLInteCtrlPackage)
public:

	quint8 getStatus() const;
	quint8 getSenderCardClass() const;
	quint8 getProductType() const;

protected:
	quint16 CmdNum() const override {
		return quint16(ECommand::EC_Read_OnlineStatus);
	}
	QByteArray CmdContent() const override {
		return QByteArray();
	}

};

class LBL_COMMUNICATENGINE_EXPORT LBLPackageInteCtrl_ReadSenderCardUuid : public LBLInteCtrlPackage
{
	LBL_DECLARE_PACKAGECONSTRUCTOR(LBLPackageInteCtrl_ReadSenderCardUuid, LBLInteCtrlPackage)
public:

	quint8 getSenderCardUuidType() const;
	QUuid getSenderCardUuid() const;

protected:
	quint16 CmdNum() const override {
		return quint16(ECommand::EC_Read_SenderCardUuid);
	}
	QByteArray CmdContent() const override {
		return QByteArray();
	}
};

class LBL_COMMUNICATENGINE_EXPORT LBLPackageInteCtrl_WriteSenderCardUuid : public LBLInteCtrlPackage
{
	LBL_DECLARE_PACKAGECONSTRUCTOR(LBLPackageInteCtrl_WriteSenderCardUuid, LBLInteCtrlPackage)
public:
	LBLPackageInteCtrl_WriteSenderCardUuid(quint8 type, QUuid id);
	quint16 getOperationResult() const;
	quint8 getSenderCardUuidType() const;
	QUuid getSenderCardUuid() const;

	void  setSenderCardUuidType(quint8 value) {
		m_uuidType = value;
	}
	void  setSenderCardUuid(QUuid value) {
		m_uuid = value;
	}

protected:
	quint16 CmdNum() const override {
		return quint16(ECommand::EC_Write_SenderCardUuid);
	}
	QByteArray CmdContent() const override;
private:
	quint8 m_uuidType = 0;
	QUuid m_uuid = 0;
};
#endif
