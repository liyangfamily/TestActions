#ifndef CVTE_H_LBLRECIVESCARDSTRUCT
#define CVTE_H_LBLRECIVESCARDSTRUCT
#pragma once
#include <QtGlobal>
#include <QString>
#include <QRectF>
#include <QByteArray>
#include <QList>
namespace LBL
{
	namespace RC
	{
#pragma pack(1)
		/******************************************************************自研接收卡***********************************************************************/
		typedef struct tagSelfReciverCardModuleParam
		{
			unsigned char reserved1;  //预留
			unsigned char decodingChipNum; //译码芯片型号
			unsigned char chipNum;		//芯片型号
			unsigned char splicingMode; //拼接模式
			unsigned char rotationMethod; //旋转方式
			unsigned char adapterBoardModel; //转接板型号
			unsigned short LEDBoardWidth;	//灯板宽度
			unsigned short LEDBoardHeight;	//灯板高度
			unsigned short boxWidth;		//屏幕宽度
			unsigned short boxHeight;		//屏幕高度
			unsigned int boxLoadLEDCount; //显示屏带载点数

			unsigned char DCLKFrequencyDivisionCoefficient; //DCLK分频系数
			unsigned char DCLKHighElectricalCoefficient; //DCLK分频系数
			unsigned char DCLKPhaseCoefficient; //DCLK分频系数

			unsigned char GCLKFrequencyDivisionCoefficient; //GCLK分频系数
			unsigned char GCLKHighElectricalCoefficient; //GCLK分频系数
			unsigned char GCLKPhaseCoefficient; //GCLK分频系数

			unsigned char ICConcatenationCount; //IC级联数
			unsigned char dataGroupCount;		//数据组数
			unsigned char ICZDiscountCount;		//IC Z型打折数
			unsigned char scanCount;			//扫描数

			unsigned short lineIntervalTime;    //行间隔时间
			unsigned short lineSwitchingTime;   //行切换时间
			unsigned short lineBlankingTime;    //行消影时间
			unsigned char eliminateAfterglow;	//消除余晖

			unsigned char ICRegister[30];		//IC寄存器

			unsigned char DecodingICBuffer;     //译码芯片位置
			unsigned char reserved2[958];		//预留

			tagSelfReciverCardModuleParam()
			{
				Q_ASSERT(sizeof(tagSelfReciverCardModuleParam) == 1024);
				clear();
			}

			void clear()
			{
				memset(this, 0, sizeof(tagSelfReciverCardModuleParam));
			}
		}SSelfReciverCardModuleParam;

		typedef struct tagSelfReciverCardDriveICParam
		{
			unsigned char reserved1[2];  //预留

			unsigned char chipbuffer[1022];		//芯片参数

			tagSelfReciverCardDriveICParam()
			{
				Q_ASSERT(sizeof(tagSelfReciverCardDriveICParam) == 1024);
				clear();
			}

			void clear()
			{
				memset(this, 0, sizeof(tagSelfReciverCardDriveICParam));
			}
		}SSelfReciverCardDriveICParam;

		typedef struct tagSelfReciverCardDecodingICParam
		{
			unsigned char reserved1[2];  //预留

			unsigned char chipbuffer[1022];		//芯片参数

			tagSelfReciverCardDecodingICParam()
			{
				Q_ASSERT(sizeof(tagSelfReciverCardDecodingICParam) == 1024);
				clear();
			}

			void clear()
			{
				memset(this, 0, sizeof(tagSelfReciverCardDecodingICParam));
			}
		}SSelfReciverCardDecodingICParam;


		typedef struct tagRCStatusInfo
		{
			unsigned char reserve1;
			unsigned char reserve2;
			unsigned char portIndex;
			unsigned char moduleInex;
			unsigned int recivedPackages;
			unsigned int correctPackages;
			unsigned int totalPackages;
            unsigned short hardwareVersion1;
            unsigned short hardwareVersion2;
            unsigned short hardwareVersion3;
            unsigned short hardwareVersion4;
			unsigned char softwareVendor[4];
			unsigned char softwareVersion_Year1;
			unsigned char softwareVersion_Year2;
			unsigned char softwareVersion_Month1;
			unsigned char softwareVersion_Month2;
			unsigned char softwareVersion_Day1;
			unsigned char softwareVersion_Day2;
			unsigned char softwareVersion;
			unsigned char softwareVersion_SmallA;
			unsigned char softwareVersion_SmallB;
			unsigned short reciveCardPixel_Width;
            unsigned short reciveCardPixel_Height;
            unsigned char protocolType;
            unsigned char reserve3[214];

			tagRCStatusInfo() {
				SetToDefalut();
			}

			void SetToDefalut() {
				Q_ASSERT(sizeof(tagRCStatusInfo) == 256);
				memset(this, 0, sizeof(tagRCStatusInfo));
			}
			void SetData(QByteArray& data) {
                quint16 size = data.size() > quint16(sizeof(tagRCStatusInfo)) ? quint16(sizeof(tagRCStatusInfo)) : data.size();
                memcpy(this, data.constData(), size);
			}
			bool IsVaild() const{
				QByteArray reData;
				reData.append(reserve1);
				reData.append(reserve2);
				return reData.startsWith(QByteArray::fromHex("F00F")) && portIndex != 0xFF && moduleInex != 0xFF;
			}
			double GetPackageLoseRate()const {
				if (0 == totalPackages) {
					return -1.0;
				}
				int lossPack = totalPackages - recivedPackages;
				if (lossPack < 0) {
					return -1.0;
				}
				return double(lossPack*1e+7) / double(totalPackages);
			}
			double GetBitErrorRate()const {
				if (0 == totalPackages) {
					return 0;
				}
				int errorPack = totalPackages - correctPackages;
				if (errorPack < 0) {
					return -1.0;
				}
				return double(errorPack*1e+7) / double(totalPackages);
			}
			quint8 GetPortIndex() const {
				return portIndex;
			}
			quint8 GetModuleIndex()const {
				return moduleInex;
			}
            QString GetHardwareVendor()const {
                return QString("%1-%2-%3-%4").arg(hardwareVersion1,4,16,QLatin1Char('0'))
                        .arg(hardwareVersion2,4,16,QLatin1Char('0'))
                        .arg(hardwareVersion3,4,16,QLatin1Char('0'))
                        .arg(hardwareVersion4,4,16,QLatin1Char('0'));
                //QByteArray ver((const char*)hardwareVersion, 8);
                //return ver;
			}
			QString GetSoftwareVendor()const {
				QByteArray ver((const char*)softwareVendor, 4);
				return ver;
			}
            QString GetSoftwareVersion()const {
				QString strVersion;
				strVersion.sprintf(("20%c%c-%c%c-%c%c %c %c.%c"), softwareVersion_Year1, softwareVersion_Year2,
					softwareVersion_Month1, softwareVersion_Month2,
					softwareVersion_Day1, softwareVersion_Day2,
					softwareVersion, softwareVersion_SmallA, softwareVersion_SmallB);
				return strVersion;
			}
			QSize GetModuleResolution()const {
				return QSize(reciveCardPixel_Width, reciveCardPixel_Height);
            }

            QString GetPotocolType()const {
                switch(protocolType)
                {
                case 0:
                    return QString("V2.0");
                case 1:
                    return QString("V3.2");
                case 2:
                    return QString("V3.3");
                default:
                    return QString("-");
                }
            }
		}SRCStatusInfo;

		/*接收卡模组监控信息结构体*/
		typedef struct tagRCModuleMonitorInfoStruct
		{
			unsigned char voltage;
			unsigned char tempature;
			unsigned char reserve1;
			unsigned char reserve2;
			unsigned char reserve3;
			unsigned char reserve4;
			unsigned char reserve5;
			unsigned char reserve6;

			int GetTempature() const
			{
				return tempature;
			}

			float GetVoltage() const
			{
				float tempV = (float)(voltage / 256.0) * (float)3.3 * (float)(2760.0 / 560.0);
				return tempV;
			}

			bool IsEmpty()
			{
				if (0 == (voltage | tempature | reserve1 | reserve2 | reserve3 | reserve4 | reserve5 | reserve6))
				{
					return true;
				}
				else
				{
					return false;
				}
			}
		}SRCModuleMonitorInfoStruct;

		/*给外部使用的模组监控信息带有端口号和模组号等信息*/
		typedef struct tagRCMonitorInfo
		{
			int		port;		//端口号
			int		sendCardIndex;		//发送卡序号
			int		moduleCardIndex; //接收卡序号

			SRCModuleMonitorInfoStruct monitorStuct;
		}SRCMonitorInfo;

		typedef struct tagMonitorPortInfo
		{
			unsigned char portNum;
			unsigned char senderCardIndex;
			SRCModuleMonitorInfoStruct moduleMonitorList[32];
			unsigned char checkSum;

			tagMonitorPortInfo() {
				SetToDefalut();
			}

			void SetToDefalut() {
				Q_ASSERT(sizeof(tagMonitorPortInfo) == 259);
				memset(this, 0, sizeof(tagMonitorPortInfo));
			}
			void SetData(QByteArray& data) {
				if (data.size() == sizeof(tagMonitorPortInfo)) {
                    memcpy(this, data.constData(), data.size());
				}
			}
			QList<SRCMonitorInfo> GetPortMonitorList() {
				if (!IsValid()) {
					return QList<SRCMonitorInfo>();
				}
				QList<SRCMonitorInfo> tempList;
				for (int i = 0; i < 32; ++i)
				{
					if (!moduleMonitorList[i].IsEmpty()) {
						SRCMonitorInfo temp;
						temp.port = portNum;
						temp.sendCardIndex = senderCardIndex;
						temp.moduleCardIndex = i;
						temp.monitorStuct = moduleMonitorList[i];
						tempList.append(temp);
					}
				}
				return tempList;
			}
			bool IsValid() 
			{
				if (0xFF == portNum)
				{
					return false;
				}
				/*QByteArray data((char*)(this), sizeof(tagMonitorPortInfo));
				unsigned char sum = 0;
				for (int i = 0; i < data.size() - 1; ++i) {
					sum += data.at(i);
				}
				if (sum != data.back()) {
					return false;
				}*/
				return true;
			}
		}SRCMonitorPortInfo;
#pragma pack()
	}
}
#endif
