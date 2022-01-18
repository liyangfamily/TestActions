#pragma once
#include <QByteArray>
#include <climits>

namespace LBL
{
	namespace MS9570
	{
		enum EMS9570StatusCMDCode
		{
			EStatus_SetSuccess = 0x10,
			EStatus_SetFaild = 0x11
		};
		class SMS9570CommunicatPackage
		{
		public:
			SMS9570CommunicatPackage(quint8 systypecode, quint8 addscode, QByteArray data)
			{
				sysTypeCode = systypecode;
				addsCode = addscode;
				m_writeData = data;
				dateLength = data.size();
			}
			QByteArray getDataToSend() const {
				return m_data;
			}
			SMS9570CommunicatPackage& build(quint16 serialNum) {
                Q_UNUSED(serialNum);
				m_data.clear();
				m_data.append(header1);
				m_data.append(header2);
				m_data.append(sysTypeCode);
				m_data.append(addsCode);
				m_data.append(dateLength);
				m_data.append(CMD);
				m_data.append(m_writeData);
				checkSum = 0;
				for (int i = 5; i < m_data.size(); i++) {
					checkSum = checkSum ^ m_data.at(i);
				}
				m_data.append(checkSum);
				return *this;
			}
		private:
			unsigned char header1 = 0x55;	//固定 - 包头
			unsigned char header2 = 0xAA;	//固定 - 包头
			unsigned char sysTypeCode = 0;	//系统类型编码
			unsigned char addsCode = 0;		//地址编码
			unsigned char dateLength = 0;	//信息长度
			unsigned char CMD = 0;			//命令字

			QByteArray m_writeData;
			unsigned char checkSum;

			QByteArray m_data;
		};

#pragma pack(1)
		class SMS9570PenetratCommunicat
		{
		public:
			SMS9570PenetratCommunicat() {};
			SMS9570PenetratCommunicat(QByteArray reData) {
				m_data = reData;
			}
			SMS9570PenetratCommunicat(quint8 mainCMD, quint8 childCMD, QByteArray data)
			{
				mainCMDFlage = mainCMD;
				childCMDFlage = childCMD;
				m_writeData = data;
				dateLength = data.size();
			}
			//解析用
			bool valid() {
				unsigned char sum = 0;
				for (int i = 0; i < m_data.size() - 1; i++) {
					sum = sum ^ m_data.at(i);
				}
				return sum == (unsigned char)m_data.back();
			}
			QByteArray getReplyData() {
				if (!valid()) {
					return QByteArray();
				}
				quint8 dataLen = m_data.at(2);
				return QByteArray(m_data.mid(3, dataLen));
			}
			quint8 getOperationResult() {
				if (!valid()) {
					return EMS9570StatusCMDCode::EStatus_SetFaild;
				}
				quint8 ret = getReplyData().at(2);
				return ret;
			}
			//构建用
			QByteArray getDataToSend() const {
				return m_data;
			}
			SMS9570PenetratCommunicat& build(quint16 serialNum) {
                Q_UNUSED(serialNum);
				m_data.clear();
				m_data.append(header);
				m_data.append(mainCMDFlage);
				m_data.append(childCMDFlage);
				m_data.append(dateLength);
				m_data.append(m_writeData);
				checkSum = 0;
				for (int i = 0; i < m_data.size(); i++) {
					checkSum = checkSum ^ m_data.at(i);
				}
				m_data.append(checkSum);
				return *this;
			}
		private:
			unsigned char header = 0xAA;	//固定 - 包头
			unsigned char mainCMDFlage = 0;	//固定 - 透传主命令码
			unsigned char childCMDFlage = 0;//固定 - 子命令码
			unsigned char dateLength = 0;	//包内数据长度 - tagData中的有效数据长度

			QByteArray m_writeData;
			unsigned char checkSum;

			QByteArray m_data;
		};
#pragma pack()

		typedef struct tagMS9570InfoAck
		{
			bool bVaild = false;
			unsigned short version = USHRT_MAX;
			unsigned char inputSource = UCHAR_MAX; //输入源	HDMI1：0x00, HDMI2：0x01，HDMI3：0x02
			unsigned char imageRatio = UCHAR_MAX; //画面比例	 4:3: 0x01,  16:9: 0x02, full screen: 0x03
			unsigned char resolution = UCHAR_MAX; //分辨率
			unsigned char backLight = UCHAR_MAX; //亮度
			unsigned char volume = UCHAR_MAX; //声音  0-100
			unsigned char contrast = UCHAR_MAX;	//对比度  0-100
			unsigned char colorMode = UCHAR_MAX; //颜色模式	标准：0x01, 暖色：0x02，冷色：0x03
            unsigned char bypass = 0;
			unsigned char rGain = UCHAR_MAX; //R
			unsigned char gGain = UCHAR_MAX; //R 0 G 1 B 2
			unsigned char bGain = UCHAR_MAX; //R 0 G 1 B 2
			unsigned int  outputWidth = UINT_MAX;	//EDID width
			unsigned int  outputHeight= UINT_MAX; //EDID height
			unsigned char outputFrequency = UCHAR_MAX; //频率

			unsigned int  inputWidth = UINT_MAX;
			unsigned int  inputHeight = UINT_MAX;
			unsigned char inputFrequency = UCHAR_MAX; //频率
		}SMS9570InfoAck;
	}
}
