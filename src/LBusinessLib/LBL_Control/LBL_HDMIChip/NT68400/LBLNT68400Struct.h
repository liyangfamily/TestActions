#pragma once
#ifndef CVTE_H_LBLNT68400CENTRALCTRL_STRUCT
#define CVTE_H_LBLNT68400CENTRALCTRL_STRUCT
#include <QtGlobal>
#include <QByteArray>

#include <LBL_Core/LBLUIHelper>
#ifdef Q_CC_MSVC
#ifdef QT_DEBUG
#pragma comment(lib,"LBL_Cored.lib")
#else
#pragma comment(lib,"LBL_Core.lib")
#endif
#endif

namespace LBL
{
	namespace NT68400
	{
		const unsigned char g_ChannelCount = 4;
		static unsigned char g_NT68400SerialNumber = 0;
		const unsigned short g_NT68400PenetratePackageLen = 40;
		const unsigned short g_NT68400AppendDataLen = g_NT68400PenetratePackageLen - 14;

#pragma pack(1)
		class SNT68400PenetratCommunicat
		{
		public:
			SNT68400PenetratCommunicat() {};
			SNT68400PenetratCommunicat(QByteArray reData){
					memcpy_s(this, reData.size(), reData.constData(), reData.size());
			}
			SNT68400PenetratCommunicat(quint8 mainCMDFlage, quint8 childCMDFlage, quint8 channel, QByteArray data)
			{
				header[0] = 0xAA;
				header[1] = 0xBB;
				header[2] = 0xCC;
				transMainCmd = 0x03;
				transChildCmd = 0x02;
				m_data.mainCMDFlage = mainCMDFlage;
				m_data.childCMDFlage = childCMDFlage;
				m_data.channel = channel;
				memcpy_s(m_data.addData, data.size(), data.constData(), data.size());
				dateLength = 6 + data.size();
			}
			
			//解析用
			quint16 getOperationResult() {
				return m_data.status;
			}

			QByteArray getReplyData() {
				QByteArray tempData((const char*)m_data.addData, dateLength - 6);
				return tempData;
			}
			//构建用
			QByteArray build(quint16 serialNum) {
                            Q_UNUSED(serialNum);
							QByteArray buildData;
				buildData.clear();
				buildData.append((const char*)header, 3);
				buildData.append(transMainCmd);
				buildData.append(transChildCmd);
				buildData.append(dateLength);
				buildData.append(reservedByte);
				m_data.serialNumber = g_NT68400SerialNumber++;
				buildData.append(m_data.serialNumber);
				buildData.append(m_data.mainCMDFlage);
				buildData.append(m_data.childCMDFlage);
				buildData.append(m_data.channel);
				buildData.append((const char*)&m_data.status, 2);
				buildData.append((const char*)m_data.addData, g_NT68400AppendDataLen);
				checkSum = LBLUIHelper::getCheckSum(QByteArray((const char*)&m_data, sizeof(tagData)));
				buildData.append(checkSum);
				return buildData;
			}
		private:
			unsigned char header[3]{ 0 };	//固定 - 包头
			unsigned char transMainCmd=0;	//固定 - 透传主命令码
			unsigned char transChildCmd=0;//固定 - 子命令码
			unsigned char dateLength=0;	//包内数据长度 - tagData中的有效数据长度
			unsigned char reservedByte=0;	//保留位 置0

			struct tagData
			{
				unsigned char serialNumber = 0;	//流水号
				unsigned char mainCMDFlage = 0;	//主命令
				unsigned char childCMDFlage = 0;//子命令
				unsigned char channel = 0;		//通道 0x00:全部通道；0x01: main window, 0x02: pip1; 0x03: pip2; 0x03:pip4
				unsigned short status = 0;		//状态位，NT68400 返回设置/获取的状态。0：normal, 1: ok, 2~65535: error code. 
				unsigned char addData[g_NT68400AppendDataLen]{ 0 };
			}m_data;
			unsigned char checkSum;

		};
#pragma pack()
		//主命令标志码
		enum ENT68400MainFlagCMDCode
		{
			E_PictureQuality = 0x60,	//PQ-画质
			E_DisplayPlay = 0x61,		//DS-显示
			E_Setting = 0x62,			//Setting
			E_System = 0x63,			//Sys
			E_FacTest = 0x64,			//Factory test
			E_Signal = 0x65,			//Signal
		};

		//画质 从命令标志码
		enum ENT68400PQ_ChildFlagCMDCode
		{
			EPQ_SetContrast = 0x01,
			EPQ_GetContrast = 0x02,
			EPQ_RetContrast = 0x03,

			EPQ_SetDCRStatus = 0x04,
			EPQ_GetDCRStatus = 0x05,
			EPQ_RetDCRStatus = 0x06,

			EPQ_SetSharpness = 0x07,
			EPQ_GetSharpness = 0x08,
			EPQ_RetSharpness = 0x09,

			EPQ_SetScreenColorTemp = 0x0A,
			EPQ_GetScreenColorTemp = 0x0B,
			EPQ_RetScreenColorTemp = 0x0C,

			EPQ_SetColor_R = 0x0D,
			EPQ_GetColor_R = 0x0E,
			EPQ_RetColor_R = 0x0F,

			EPQ_SetColor_G = 0x10,
			EPQ_GetColor_G = 0x11,
			EPQ_RetColor_G = 0x12,

			EPQ_SetColor_B = 0x13,
			EPQ_GetColor_B = 0x14,
			EPQ_RetColor_B = 0x15,

			EPQ_SetSceneMode = 0x16,
			EPQ_GetSceneMode = 0x17,
			EPQ_RetSceneMode = 0x18,

			EPQ_GetAllNormalParam = 0x9E,
			EPQ_RetAllNormalParam = 0x9F,

			EPQ_Set3D_DEI_Status = 0xA0,
			EPQ_Get3D_DEI_Status = 0xA1,
			EPQ_Ret3D_DEI_Status = 0xA2,

			EPQ_SetHDR = 0xA3,
			EPQ_GetHDR = 0xA4,
			EPQ_RetHDR = 0xA5,

			EPQ_SetBrightFrame = 0xA6,
			EPQ_GetBrightFrame = 0xA7,
			EPQ_RetBrightFrame = 0xA8,

			EPQ_GetAllAdvancedParam = 0xFE,
			EPQ_RetAllAdvancedParam = 0xFF,
		};

		//显示 从命令标志码
		enum ENT68400DP_ChildFlagCMDCode
		{
			EDP_SetAspectRatio = 0x01,
			EDP_GetAspectRatio = 0x02,
			EDP_RetAspectRatio = 0x03,

			EDP_SetOverScanStatus = 0x04,
			EDP_GetOverScanStatus = 0x05,
			EDP_RetOverScanStatus = 0x06,

			EDP_SetPivotStatus = 0x07,
			EDP_GetPivotStatus = 0x08,
			EDP_RetPivotStatus = 0x09,

			EDP_SetFlipMode = 0x0A,
			EDP_GetFlipMode = 0x0B,
			EDP_RetFlipMode = 0x0C,

			EDP_GetAllNormalParam = 0x4E,
			EDP_RetAllNormalParam = 0x4F,

			EDP_SetPIPPBP = 0x50,
			EDP_GetPIPPBP = 0x51,
			EDP_RetPIPPBP = 0x52,

			EDP_SetMainPIP_Input = 0x53,
			EDP_GetMainPIP_Input = 0x54,
			EDP_RetMainPIP_Input = 0x55,

			EDP_SetWindowSize = 0x56,
			EDP_GetWindowSize = 0x57,
			EDP_RetWindowSize = 0x58,

			EDP_SetWindowPos = 0x59,
			EDP_GetWindowPos = 0x5A,
			EDP_RetWindowPos = 0x5B,

			EDP_SetVideoWall = 0x5C,
			EDP_GetVideoWall = 0x5D,
			EDP_RetVideoWall = 0x5E,

			EDP_SetRatio_H = 0x5F,
			EDP_GetRatio_H = 0x60,
			EDP_RetRatio_H = 0x61,

			EDP_SetRatio_V = 0x62,
			EDP_GetRatio_V = 0x63,
			EDP_RetRatio_V = 0x64,

			EDP_SetStart_H = 0x65,
			EDP_GetStart_H = 0x66,
			EDP_RetStart_H = 0x67,

			EDP_SetStart_V = 0x68,
			EDP_GetStart_V = 0x69,
			EDP_RetStart_V = 0x6A,

			EDP_SetSize_H = 0x6B,
			EDP_GetSize_H = 0x6C,
			EDP_RetSize_H = 0x6D,

			EDP_SetSize_V = 0x6E,
			EDP_GetSize_V = 0x6F,
			EDP_RetSize_V = 0x70,
			EDP_SetPIPWindowStatus = 0x71,
			EDP_GetPIPWindowStatus = 0x72,
			EDP_RetPIPWindowStatus = 0x73,

			EDP_GetAllPIPAdvanceParam = 0x9C,
			EDP_RetAllPIPAdvanceParam = 0x9D,
			EDP_GetAllVideoWallAdvanceParam = 0x9E,
			EDP_RetAllVideoWallAdvanceParam = 0x9F,

			EDP_SetTX = 0xA0,
			EDP_GetTX = 0xA1,
			EDP_RetTX = 0xA2,

		};

		//设置 从命令标志码
		enum ENT68400Setting_ChildFlagCMDCode
		{
			ESetting_SetMuteStatus = 0x01,
			ESetting_GetMuteStatus = 0x02,
			ESetting_RetMuteStatus = 0x03,

			ESetting_SetVolume = 0x04,
			ESetting_GetVolume = 0x05,
			ESetting_RetVolume = 0x06,

			ESetting_SetAudioSrc = 0x07,
			ESetting_GetAudioSrc = 0x08,
			ESetting_RetAudioSrc = 0x09,

			ESetting_GetAllAudioParam = 0x4E,
			ESetting_RetAllAudioParam = 0x4F,

			ESetting_SetDPSpeed = 0x50,
			ESetting_GetDPSpeed = 0x51,
			ESetting_RetDPSpeed = 0x52,

			ESetting_SetByPassStatus = 0x53,
			ESetting_GetByPassStatus = 0x54,
			ESetting_RetByPassStatus = 0x55,

			ESetting_GetAllOtherParam = 0xFE,
			ESetting_RetAllOtherParam = 0xFF,
		};

		//系统 从命令标志码
		enum ENT68400Sys_ChildFlagCMDCode
		{
			ESys_SetPowerON = 0x01,
			ESys_SetPowerOFF = 0x02,
			ESys_SetReboot = 0x03,

			ESys_SetReset68400 = 0x50,
			ESys_RetReset68400Status = 0x51,
			ESys_Upgarad68400 = 0x52,
			ESys_RetUpgarad68400Status = 0x53,
			ESys_SetDisplayArea = 0x54,
			ESys_GetDisplayArea = 0x55,
			ESys_RetDisplayArea = 0x56,

			Esys_GetVersion = 0xA0,
			Esys_RetVersion = 0xA1,
		};

		enum ENT68400FacTest_ChildFlagCMDCode
		{
			EFacTest_SetPowerRelay = 0x01,
			EFacTest_RetPowerRelay = 0x02,
			EFacTest_SetEraseEDID = 0x03,
			EFacTest_RetEraseEDID = 0x04,
			EFacTest_SetUpdateEDID = 0x05,
			EFacTest_RetUpdateEDID = 0x06,
		};

		enum ENT68400Signal_ChildFlagCMDCode
		{
			ESignal_GetSignalInfo = 0x30,
			ESignal_RetSignalInfo = 0x31,
			ESignal_GetCableConnectInfo = 0x32,
			ESignal_RetCableConnectInfo = 0x33,
		};

		enum ENT68400StatusCMDCode
		{
			EStatus_SetSuccess = 0x0010,
			EStatus_SetFaild = 0x0011,
			EStatus_GetSuccess = 0x0020,
			EStatus_GetFaild = 0x0021,
		};

		enum ENT68400ChannelCMDCode
		{
			EChannel_All,
			EChannel_Main,
			EChannel_P1,
			EChannel_P2,
			EChannel_P3,
		};

		enum ENT68400PIPModeCode
		{
			EPIP_Mode_Off,
			EPIP_Mode_OneWindow,
			EPIP_Mode_TwoWindow,
			EPIP_Mode_SideBySide,
			EPIP_Mode_3Division_1,
			EPIP_Mode_3Division_2,
			EPIP_Mode_4Division,
			EPIP_Mode_User,
			EPIP_Mode_Num,
		};

		enum ENT68400InputSourceCode
		{
			EInputSrc_Android,
			EInputSrc_PC,
			EInputSrc_HDMI1,
			EInputSrc_HDMI2,
			EInputSrc_HDMI3,
			EInputSrc_Num,
		};

		enum ENT68400WindowCode
		{
			EWindow_Main,
			EWindow_P1,
			EWindow_P2,
			EWindow_P3,
			EWindow_Num,
		};

		enum ENT68400AspectRatioCode
		{
			EAspectRatio_Full,
			EAspectRatio_Original,
			EAspectRatio_4x3,
			EAspectRatio_16x9,
			EAspectRatio_P2P,	//Point to point.
			EAspectRatio_SmartView, //Display as 3/4 scaler
			EAspectRatio_Num,
		};

		enum ENT68400ColorTempCode
		{
			EColorTemp_Cool,
			EColorTemp_Warm,
			EColorTemp_Standard,
			EColorTemp_User,
			EColorTemp_Num,
		};

		enum ENT68400WindowStatus
		{
			EWindow_Main_Enable = 0x01,
			EWindow_P1_Enable = 0x02,
			EWindow_P2_Enable = 0x04,
			EWindow_P3_Enable = 0x08,
			EWindow_Main_Num = 0x00,
		};

		enum ENT68400SignalType
		{
			ESignal_Progressive = 0x00,
			ESignal_Interlace = 0x01,
		};

		const ENT68400InputSourceCode mutexInputSrcArray[] =
		{
			EInputSrc_PC,
			EInputSrc_HDMI3,
		};
	}
}


namespace LBL
{
	namespace NT68400
	{
#pragma pack(1)
		const int g_NT68400ChannelCount = 4;

		typedef struct tagNT68400ChannelInfo
		{
			bool restoreValidable = false;
			unsigned char channel = 0x00;
			unsigned char inputSource = 0x00;
			unsigned char pippbp = 0x00;
			unsigned short windowSize_Width = 0x00;
			unsigned short windowSize_Height = 0x00;

			unsigned short windowPos_X = 0x00;
			unsigned short windowPos_Y = 0x00;

		}SNT68400ChannelInfo;

		//画质-常规数据
		typedef struct tagNT68400PictureQualityNormal
		{
			unsigned char contrast; //对比度
			unsigned char status_DCR; //DCR状态
			unsigned char sharpness;
			unsigned char colorTemp;
			unsigned char color_R;
			unsigned char color_G;
			unsigned char color_B;
			unsigned char sceneMode;

			tagNT68400PictureQualityNormal()
			{
				Q_ASSERT(sizeof(tagNT68400PictureQualityNormal) == 8);
				SetToDefault();
			}
			void SetToDefault()
			{
				memset(this, 0, sizeof(tagNT68400PictureQualityNormal));
			}
		}SNT68400PictureQualityNormal;

		//画质-高级数据
		typedef struct tagNT68400PictureQualityAdvanced
		{
			unsigned char status_3DDEI; //
			unsigned char status_HDR; //
			unsigned char brightFrame;

			tagNT68400PictureQualityAdvanced()
			{
				Q_ASSERT(sizeof(tagNT68400PictureQualityAdvanced) == 3);
				SetToDefault();
			}
			void SetToDefault()
			{
				memset(this, 0, sizeof(tagNT68400PictureQualityAdvanced));
			}
		}SNT68400PictureQualityAdvanced;

		//显示-常规数据
		typedef struct tagNT68400DisPlayNormal
		{
			unsigned char aspectRatio; //
			unsigned char status_overScan; //
			unsigned char status_pivot;
			unsigned char flipMode;

			tagNT68400DisPlayNormal()
			{
				Q_ASSERT(sizeof(tagNT68400DisPlayNormal) == 4);
				SetToDefault();
			}
			void SetToDefault()
			{
				memset(this, 0, sizeof(tagNT68400DisPlayNormal));
			}
		}SNT68400DisPlayNormal;

		//显示-高级数据
		typedef struct tagNT68400DisPlayAdvanced
		{
			unsigned char PIPorPBP; //

			unsigned char main_Input;
			unsigned char PIP1_Input;
			unsigned char PIP2_Input;
			unsigned char PIP3_Input;

			unsigned short windowSize_Width;
			unsigned short windowSize_Height;

			unsigned short windowPos_X;
			unsigned short windowPos_Y;

			unsigned char videoWall;

			unsigned short ratio_H;
			unsigned short ratio_V;

			unsigned short start_H;
			unsigned short start_V;

			unsigned short size_H;
			unsigned short size_V;

			unsigned char windowEnable;

			tagNT68400DisPlayAdvanced()
			{
				Q_ASSERT(sizeof(tagNT68400DisPlayAdvanced) == 27);
				SetToDefault();
			}
			void SetToDefault()
			{
				memset(this, 0, sizeof(tagNT68400DisPlayAdvanced));
			}
		}SNT68400DisPlayAdvanced;

		//显示-高级数据
		typedef struct tagNT68400DisPlayTX
		{
			unsigned char tx; //

			tagNT68400DisPlayTX()
			{
                                Q_ASSERT(sizeof(tagNT68400DisPlayTX) == 1);
				SetToDefault();
			}
			void SetToDefault()
			{
				memset(this, 0, sizeof(tagNT68400DisPlayTX));
			}
		}SNT68400DisPlayTX;

		//设置-常规数据
		typedef struct tagNT68400SettingAudio
		{
			unsigned char mute;
			unsigned char volume;
			unsigned char audioSrc;

			tagNT68400SettingAudio()
			{
				Q_ASSERT(sizeof(tagNT68400SettingAudio) == 3);
				SetToDefault();
			}
			void SetToDefault()
			{
				memset(this, 0, sizeof(tagNT68400SettingAudio));
			}
		}SNT68400SettingAudio;

		//设置-高级数据
		typedef struct tagNT68400SettingOther
		{
			unsigned char DP_Speed;
			unsigned char ByPass;

			tagNT68400SettingOther()
			{
				Q_ASSERT(sizeof(tagNT68400SettingOther) == 2);
				SetToDefault();
			}
			void SetToDefault()
			{
				memset(this, 0, sizeof(tagNT68400SettingOther));
			}
		}SNT68400SettingOther;

		//系统-常规数据
		typedef struct tagNT68400SystemNormal
		{
			//Software Version
			unsigned char year1;
			unsigned char year2;
			unsigned char year3;
			unsigned char year4;
			unsigned char month1;
			unsigned char month2;
			unsigned char day1;
			unsigned char day2;
			unsigned char hour1;
			unsigned char hour2;
			unsigned char minute1;
			unsigned char minute2;
			unsigned char second1;
			unsigned char second2;

			//Display area
			unsigned short disWidth;
			unsigned short disHeight;

			tagNT68400SystemNormal()
			{
				Q_ASSERT(sizeof(tagNT68400SystemNormal) == 18);
				SetToDefault();
			}
			void SetToDefault()
			{
				memset(this, 0, sizeof(tagNT68400SystemNormal));
			}

			QString getNT68400Version()
			{
				QString		strVersion;
				if (year1 == 0 && year2 == 0 && year3 == 0 && year4 == 0)
				{
                                        strVersion.sprintf(("%d%d%d%d-%d%d-%d%d %d%d:%d%d:%d%d"), year1, year2, year3, year4, month1, month2,
						day1, day2, hour1, hour2, minute1, minute2, second1, second2);
				}
				else
				{
					strVersion.sprintf(("%c%c%c%c-%c%c-%c%c %c%c:%c%c:%c%c"), year1, year2, year3, year4, month1, month2,
						day1, day2, hour1, hour2, minute1, minute2, second1, second2);
				}
				return strVersion;
			}

		}SNT68400SystemNormal;

		typedef struct tagNT68400Signal
		{
			unsigned char inputIndex;
			unsigned char signalStatus;
			unsigned short inputSignalWidth;
			unsigned short inputSignalHeight;
			unsigned char inputFreqInt;		//integer
			unsigned char inputFreqDec;		//decimal
			unsigned char isInterlaced;

			tagNT68400Signal()
			{
				Q_ASSERT(sizeof(tagNT68400Signal) == 9);
				SetToDefault();
			}
			void SetToDefault()
			{
				memset(this, 0, sizeof(tagNT68400Signal));
			}
		}SNT68400Signal;

		//系统-高级数据
		typedef struct tagNT68400Data
		{
			SNT68400PictureQualityNormal m_PQNormalData;
			SNT68400PictureQualityAdvanced m_PQAdvanceData;

			SNT68400DisPlayNormal m_DPNormalData;
			SNT68400DisPlayAdvanced m_DPAdvanceData;
			SNT68400DisPlayTX m_DPTXData;

			SNT68400SettingAudio m_SettingAudioData;
			SNT68400SettingOther m_SettingOtherData;

			SNT68400SystemNormal m_SysNormalData;

			SNT68400Signal m_SignalData;

			void SetToDefault()
			{
				m_PQNormalData.SetToDefault();
				m_PQAdvanceData.SetToDefault();
				m_DPNormalData.SetToDefault();
				m_DPAdvanceData.SetToDefault();
				m_DPTXData.SetToDefault();
				m_SettingAudioData.SetToDefault();
				m_SettingOtherData.SetToDefault();
				m_SysNormalData.SetToDefault();
				m_SignalData.SetToDefault();
			}
		}SNT68400Data;
#pragma pack()
	}
}

#endif
