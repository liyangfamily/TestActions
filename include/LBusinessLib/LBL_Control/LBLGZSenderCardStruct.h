#ifndef CCCD_H_GZSENDCARDSTRUCT
#define CCCD_H_GZSENDCARDSTRUCT
#pragma once
#include <QtGlobal>
#include <QString>
#include <QRectF>
namespace LBL
{
	namespace SC
	{
#pragma pack(1)
		////区域结构体
		//typedef struct tagPortArea
		//{
		//	tagPortArea() {
		//		clear();
		//	}
		//	tagPortArea(int portIndex, const QRectF& rect):
		//		m_portIndex(portIndex),m_rect(rect)
		//	{
		//	}
		//	void setPortIndex(unsigned short index) {
		//		m_portIndex = index;
		//	}
		//	unsigned short portIndex() const{
		//		return m_portIndex;
		//	}

		//	void clear() {
		//		m_portIndex = 0xFFFF;
		//		m_rect = QRectF();
		//	}

		//	bool fromByteArray(const QByteArray& array) {
		//		if (8 != array.size())
		//			return false;
		//		quint16 value;
        //		memcpy(&value, array.constData(), sizeof(quint16));
		//		m_rect.setX(value);
        //		memcpy(&value, array.constData() + 2, sizeof(quint16));
		//		m_rect.setY(value);
        //		memcpy(&value, array.constData() + 4, sizeof(quint16));
		//		m_rect.setWidth(value);
        //		memcpy(&value, array.constData() + 6, sizeof(quint16));
		//		m_rect.setHeight(value);
		//		return true;
		//	}

		//	QByteArray toByteArray() {
		//		QByteArray temp;
		//		quint16 value = m_rect.x();
		//		temp.append((char *)&value, 2); 
		//		value = m_rect.y();
		//		temp.append((char *)&value, 2);
		//		value = m_rect.width();
		//		temp.append((char *)&value, 2);
		//		value = m_rect.height();
		//		temp.append((char *)&value, 2);
		//		return temp;
		//	}
		//private:
		//	unsigned short m_portIndex = 0xFFFF;
		//	QRectF m_rect;

		//}LBLSPortArea;

		/*********************************************************************常规设置(64BYTE)************************************************************************/
		//常规设置寄存器地址枚举
		enum ENormalSettingRegAddrs
		{
			ENSRA_DeviceType = 0x000000,
			ENSRA_HardWareVersion = 0x000001,
			ENSRA_FPGABigVersion = 0x000002,
			ENSRA_FPGASmallVersion = 0x000003,
			ENSRA_DataTime = 0x000004,
			ENSRA_SendCardFeatureDef = 0x000007,
			ENSRA_AuthorizationMark = 0x00000F,
			ENSRA_ParamFromSendCard = 0x000010,
			ENSRA_ConnectionFromSendCard = 0x000011,
			ENSRA_DataPackageGap = 0x000012,
			ENSRA_Brightness = 0x000013,
			ENSRA_ColorTemperature_R = 0x000014,
			ENSRA_ColorTemperature_G = 0x000015,
			ENSRA_ColorTemperature_B = 0x000016,
			ENSRA_LineFreInfo = 0x000017,
			ENSRA_FieldFreInfo = 0x000019,
			ENSRA_LoadWidth = 0x00001B,
			ENSRA_LoadHeight = 0x00001D,
			ENSRA_SenderCardFeatureSwitch = 0x00001F,
			ENSRA_EthCount = 0x000020,
			ENSRA_AudioOpenSetting = 0x000021,
			ENSRA_AudioFilterValue = 0x000022,
			ENSRA_CurrentGain_R = 0x000024,
			ENSRA_CurrentGain_G = 0x000025,
			ENSRA_CurrentGain_B = 0x000026,
			ENSRA_ReceiveCardFeatureSwitch = 0x000027,
			ENSRA_ZoomWidht = 0x00002A,
			ENSRA_ZoomHeight = 0x00002C,
			ENSRA_ReservedSpace = 0x000028,
		};

		typedef struct tagNormalSetting
		{
			unsigned char deviceType;				//[0x000000] 设备类型
			unsigned char hardWareVersion;			//[0x000001] 硬件版本
			unsigned char FPGABigVersio;			//[0x000002] FPGA大版本
			unsigned char FPGASmallVersion;			//[0x000003] FPGA小版本
			unsigned char dataTime[3];				//[0x000004] 年月日
			unsigned char sendCardFeatureDef[8];	//[0x000007] 发送卡功能定义
			unsigned char authorizationMark;		//[0x00000F] 控制器授权标志
			unsigned char paramFromSendCard;		//[0x000010] 参数文件来自发送卡
			unsigned char connectionFromSendCard;	//[0x000011] 连接关系来自发送卡
			unsigned char dataPackageGap;			//[0x000012] 数据包空隙
			unsigned char brightness;				//[0x000013] 亮度
			unsigned char colorTemperature_R;		//[0x000014] 主控色温R
			unsigned char colorTemperature_G;		//[0x000015] 主控色温G
			unsigned char colorTemperature_B;		//[0x000016] 主控色温B
			unsigned short lineFreInfo;				//[0x000017] 行频信息
			unsigned short fieldFreInfo;			//[0x000019] 场频信息
			unsigned short loadWidth;				//[0x00001B] 带载宽度
			unsigned short loadHeight;				//[0x00001D] 带载高度
			unsigned char scFeatureSwitch;			//[0x00001F] 发送卡功能开关
			unsigned char ethCount;					//[0x000020] 发送卡网口个数
			unsigned char audioOpenSetting;			//[0x000021] 音频开启设置
			unsigned short audioFilterValue;		//[0x000022] 音频滤波值
			unsigned char currentGain_R;			//[0x000024] 电流增益R
			unsigned char currentGain_G;			//[0x000025] 电流增益G
			unsigned char currentGain_B;			//[0x000026] 电流增益B
			unsigned char rcFeatureSwitch;			//[0x000027] 接收卡功能开关
			unsigned char NT68400SignlaSwitch;		//[0x000028] NT68400信号切换开关
			unsigned char masterAndStandbyCard;		//[0x000029] 发送卡主备卡设置
			unsigned short zoomWidth;				//[0x00002A] 缩放宽度设置
			unsigned short zoomHeight;				//[0x00002C] 缩放高度设置
			unsigned char NT68400SignalResolution;	//[0x00002E] NT68400信号源分辨率
			unsigned char reservedSpace[17];		//[0x00002F] 预留

			tagNormalSetting()
			{
                Q_ASSERT(sizeof(tagNormalSetting) == 64);
				clear();
			}
			void clear()
			{
                memset(this, 0, sizeof(tagNormalSetting));
			}

			QString getSendCardFPGAVersion()
			{
				return QString("%1-%2-%3 %4.%5").arg(QString::number(2000 + dataTime[0])).arg(dataTime[1])\
					.arg(dataTime[2]).arg(QString::number(FPGABigVersio, 16)).arg(QString::number(FPGASmallVersion, 16));
			}
		}SNormalSetting;

		/*******************************************************************发送卡自测试(6BYTE)***********************************************************************/
		//发送卡自测试寄存器地址枚举
		enum ESelfTestRegAddrs
		{
			ESTRA_TestModeStatus = 0x000040,
			ESTRA_TestSourceMode = 0x000041,
			ESTRA_TestSourceSpeed = 0x000042,
			ESTRA_ReservedSpace = 0x000043,
		};

		typedef struct tagSelfTest
		{
			unsigned char testModeStatus;				//[0x000040] 发送卡自测试模式状态
			unsigned char testSourceMode;				//[0x000041] 测试源的各种模式选择
			unsigned char testSourceSpeed;				//[0x000042] 测试源时的速度选择
			unsigned char reservedSpace[3];				//[0x000043] 预留

			tagSelfTest()
			{
                Q_ASSERT(sizeof(tagSelfTest) == 6);
				clear();
			}
			void clear()
			{
                memset(this, 0, sizeof(tagSelfTest));
			}

		}SSelfTest;

		/*******************************************************************接收卡控制相关(16BYTE)***********************************************************************/
		//接收卡控制相关寄存器地址枚举
		enum EReciverCtrlRegAddrs
		{
			ERCRA_ScreenCtrlParam = 0x000046,
			ERCRA_FPGAStatusInfo = 0x000047,
			ERCRA_CMDStatus = 0x000048,
			ERCRA_NeedReadColumnNum = 0x000049,
			ERCRA_NeedReadRowNum = 0x00004A,
			ERCRA_CommunicatSignal = 0x00004B,
			ERCRA_StatusData = 0x00004C,
			ERCRA_StatusAddrs = 0x00004D,
			ERCRA_ProtocolType = 0x00004E,
			ERCRA_ReservedSpace = 0x00004F,
		};

		typedef struct tagReciverCtrl
		{
			unsigned char screenCtrlPara;			//[0x000046] 屏幕控制参数
			unsigned char FPGAStatusInfo;			//[0x000047] FPGA状态信息
			unsigned char CMDStatus;				//[0x000048] 命令状态
			unsigned char needReadColumnNum;		//[0x000049] 需要回读状态模组的模组列编号
			unsigned char needReadRowNum;			//[0x00004A] 需要回读状态模组的模组行编号
			unsigned char communicatSignal;			//[0x00004B] 通信控制信号
			unsigned char statusData;				//[0x00004C] 数据
			unsigned char statusAddrs;				//[0x00004D] 地址
			unsigned char protocolType;				//[0x00004E] 协议类型
			unsigned char reservedSpace[7];			//[0x00004F] 预留

			tagReciverCtrl()
			{
                Q_ASSERT(sizeof(tagReciverCtrl) == 16);
				clear();
			}
			void clear()
			{
                memset(this, 0, sizeof(tagReciverCtrl));
			}

		}SReciverCtrl;

		/*******************************************************************发送卡网口带载(296BYTE)*********************************************************************/
		//网口带载寄存器地址枚举
		enum EEthLoadRegAddrs
		{
			EELRA_EthReciverConunt = 0x000056,
			EELRA_EthConnectFlag = 0x000076,
			EELRA_EthBackUpFlag = 0x00007A,
			EELRA_EthLoadArea = 0x00007E,
		};

		typedef struct tagSendCardEthLoad
		{
			unsigned char ethReciveCount[32];	//[0x000056]-[0x000075] 每个网口带载的接收卡数量
			unsigned char ethConnectFlag[4];	//[0x000076]-[0x000079] 每个网口是否有连接网线，Bit/网口
			unsigned char ethBackUpFlag[4];		//[0x00007A]-[0x00007D] 每个网口是否备份标志，Bit/网口
			unsigned char ethLoadArea[256];		//[0x00007E]-[0x000086] 每个网口的区域

			tagSendCardEthLoad()
			{
                Q_ASSERT(sizeof(tagSendCardEthLoad) == 296);
				clear();
			}
			void clear()
			{
                memset(this, 0, sizeof(tagSendCardEthLoad));
			}
		}SSendCardEthLoad;

		/*******************************************************************3D(24BYTE)***********************************************************************/
		//3D寄存器地址枚举
		enum E3DRegAddrs
		{
			E3DRA_Open = 0x00017E,
			E3DRA_Config = 0x00017F,
			E3DRA_LeftEyeArea = 0x000180,
			E3DRA_RightEyeArea = 0x000188,
			E3DRA_ReservedSpace = 0x000190,
		};

		//3D设置
		typedef struct tag3DSetting
		{
			unsigned char open;					//[0x00017E] 3D开启
			unsigned char config;				//[0x00017F] 3D配置
			unsigned long long leftEyeArea;		//[0x000180] 左眼区域
			unsigned long long rightEyeArea;	//[0x000188] 右眼区域
			unsigned char reservedSpace[6];		//[0x000190] 预留

			tag3DSetting()
			{
                Q_ASSERT(sizeof(tag3DSetting) == 24);
				clear();
			}
			void clear()
			{
                memset(this, 0, sizeof(tag3DSetting));
			}

		}S3DSetting;

		/*******************************************************************OSD菜单(16BYTE)***********************************************************************/
		//OSD菜寄存器地址枚举
		enum EOSDMenuRegAddrs
		{
			EOSDRA_Open = 0x000196,
			EOSDRA_Transparency = 0x000197,
			EOSDRA_StartPos_X = 0x000198,
			EOSDRA_StartPos_Y = 0x00019A,
			EOSDRA_Menu_W = 0x00019C,
			EOSDRA_Menu_H = 0x00019E,
			EOSDRA_ReservedSpace = 0x0001A0,
		};

		//OSD菜单
		typedef struct tagOSDMenu
		{
			unsigned char open;					//[0x000196] 菜单开启
			unsigned char transparency;			//[0x000197] 透明度
			unsigned short startPos_X;			//[0x000198] 屏幕上菜单起点X
			unsigned short startPos_Y;			//[0x00019A] 屏幕上菜单起点Y
			unsigned short menu_W;				//[0x00019C] 菜单宽度W
			unsigned short menu_H;				//[0x00019E] 菜单高度H
			unsigned char reservedSpace[6];		//[0x0001A0] 预留

			tagOSDMenu()
			{
                Q_ASSERT(sizeof(tagOSDMenu) == 16);
				clear();
			}
			void clear()
			{
                memset(this, 0, sizeof(tagOSDMenu));
			}

		}SOSDMenu;

		/*******************************************************************工程自测试(20BYTE)***********************************************************************/
		//工程自测试寄存器地址枚举
		enum EProjectSelfTestRegAddrs
		{
			EPSTRA_OSDLineInfoDetection = 0x0001A6,
			EPSTRA_OSDBWScreenDetection = 0x0001A7,
			EPSTRA_NT68400LineAndFieldInfoDetection = 0x0001A8,
			EPSTRA_DDRInitDetection = 0x0001A9,
			EPSTRA_EthErrorRate = 0x0001AA,
			EPSTRA_ReservedSpace = 0x00026A,
		};

		//网口误码
		typedef struct tagEthErrorRate
		{
			unsigned int allPackageCount;
			unsigned short ErrorPackageCount;

			tagEthErrorRate()
			{
                Q_ASSERT(sizeof(tagEthErrorRate) == 6);
				clear();
			}
			void clear()
			{
                memset(this, 0, sizeof(tagEthErrorRate));
			}

		}SEthErrorRate;

		//工程自测试
		typedef struct tagProjectSelfTest
		{
			unsigned char osdLineInfoDetection;					//[0x0001A6] OSD行场信息检测
			unsigned char osdBWScreenDetection;					//[0x0001A7] OSD黑/白屏检测
			unsigned char nt68400LineAndFieldInfoDetection;		//[0x0001A8] 68400行场信息检测
			unsigned char ddrInitDetection;						//[0x0001A9] DDR初始化检测
			SEthErrorRate errorRate[32];						//[0x0001AA]-[0x000269] 网口误码
			unsigned char reservedSpace[4];						//[0x00026A] 预留

			tagProjectSelfTest()
			{
                Q_ASSERT(sizeof(tagProjectSelfTest) == 200);
				clear();
			}
			void clear()
			{
                memset(this, 0, sizeof(tagProjectSelfTest));
			}

		}SProjectSelfTest;



		typedef struct tagSSendCardData
		{
			SNormalSetting normalSetting;
			SSelfTest selfTest;
			SReciverCtrl reciverCtrl;
			SSendCardEthLoad sendCardEthLoad;
			S3DSetting threeDSetting;
			SOSDMenu osdMenu;
			SProjectSelfTest projectSelfTest;

			void clear()
			{
				normalSetting.clear();
				selfTest.clear();
				reciverCtrl.clear();
				sendCardEthLoad.clear();
				threeDSetting.clear();
				osdMenu.clear();
				projectSelfTest.clear();
			}

		}SGZSendCardData;
#pragma pack()
	}
}
#endif
