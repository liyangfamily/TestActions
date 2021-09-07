#include "LBLReceiveCardCentralCtrl.h"
#include "LBLReceiveCardAbstract_p.h"
#include <LBL_CommunicatEngine/LBLClusterProxy>
namespace LBL
{
	namespace RC
	{

		LBLReceiveCardCentralCtrl::LBLReceiveCardCentralCtrl(QObject* parent) :
			LBLReceiveCardAbstract(parent)
		{
			Q_D(LBLReceiveCardAbstract);
			d->q_ptr = this;
		}


		LBLReceiveCardCentralCtrl::LBLReceiveCardCentralCtrl(LBLReceiveCardAbstractPrivate& dd, QObject* parent) :
			LBLReceiveCardAbstract(dd, parent)
		{
			Q_D(LBLReceiveCardAbstract);
			d->q_ptr = this;
		}

		LBLReceiveCardCentralCtrl::~LBLReceiveCardCentralCtrl()
		{
			qDebug() << __FUNCTION__;
		}

		quint16 LBLReceiveCardCentralCtrl::writeFPGARegister(quint8 port,quint8 module,quint32 addr, QByteArray value, bool sync, int msec)
		{
			if (0 == value.size()) {
				return LAPI::EResult::ER_InDataError;
			}
			Q_D(LBLReceiveCardAbstract);
			//发送开始发送文件指令
			quint16 singlePackgeLen = 512;
			//计算分包数
			quint16 packageCount = 0;
			int paramLen = value.size();
			packageCount = paramLen / singlePackgeLen;
			if (0 != paramLen % singlePackgeLen) {
				packageCount += 1;
			}
			quint32 pos = addr;
			for (int i = 0; i < packageCount; i++)
			{
				int tempSendLen = singlePackgeLen;
				if (i == packageCount - 1)
				{
					tempSendLen = paramLen - singlePackgeLen * (packageCount - 1);
				}
				QByteArray temp(value.mid(i * singlePackgeLen, tempSendLen));
				//在此处组好集控的包，直接调用通信层
				LBLPackageInteCtrl_WriteRCFPGARegister pack(port, module, pos, temp);
				pack.SetCmdTargetDevice(d->m_registerTargetDeviceType);
				pack.initByDetectInfo(d->m_parentItemDetectInfo);
				pack.build(0);
				LBLEnginePackage enginePack;
				enginePack.initByDetectInfo(d->m_parentItemDetectInfo);
				enginePack.setData(pack.getDataToSend());
				if (sync) {
					LBLEnginePackage recEnginePack;
					if (!LBLClusterProxy::syncSend(enginePack, recEnginePack, msec)) {
						return LAPI::EResult::ER_SyncSendTimeOut;
					}
					quint16 ret = d->m_packageMgr.handle(LBLPackage(recEnginePack.data()));
					if (LAPI::EResult::ER_INTECTRL_Success != ret) {
						return ret;
					}
				}
				else{
					LBLClusterProxy::asyncSend(enginePack);
				}
				pos += singlePackgeLen;
			}

			return LAPI::EResult::ER_INTECTRL_Success;
		}

		QByteArray LBLReceiveCardCentralCtrl::readFPGARegister(quint8 port, quint8 module, quint32 addr, quint16 len, bool sync, int msec)
		{
			Q_D(LBLReceiveCardAbstract);
			//发送开始发送文件指令
			quint16 singlePackgeLen = 256;
			//计算分包数
			quint16 packageCount = 0;
			packageCount = len / singlePackgeLen;
			if (0 != len % singlePackgeLen) {
				packageCount += 1;
			}
			quint32 pos = addr;
			QByteArray reData;
			for (int i = 0; i < packageCount; i++)
			{
				int tempSendLen = singlePackgeLen;
				if (i == packageCount - 1)
				{
					tempSendLen = len - singlePackgeLen * (packageCount - 1);
				}
				//在此处组好集控的包，直接调用通信层
				LBLPackageInteCtrl_ReadRCFPGARegister pack(port, module, pos, tempSendLen);
				pack.SetCmdTargetDevice(d->m_registerTargetDeviceType);
				pack.initByDetectInfo(d->m_parentItemDetectInfo);
				pack.build(0);
				LBLEnginePackage enginePack;
				enginePack.initByDetectInfo(d->m_parentItemDetectInfo);
				enginePack.setData(pack.getDataToSend());
				if (sync) {
					LBLEnginePackage recEnginePack;
					if (!LBLClusterProxy::syncSend(enginePack, recEnginePack, msec)) {
						return  QByteArray();
					}
					LBLPackageInteCtrl_ReadRCFPGARegister pack(recEnginePack.data());
					quint16 ret = pack.getOperationResult();
					if (LAPI::EResult::ER_INTECTRL_Success != ret)
						return QByteArray();
					quint16 len = pack.getDataLength();
					Q_UNUSED(len);
					reData.append(pack.getReplyData());
				}
				else {
					LBLClusterProxy::asyncSend(enginePack);
				}
				pos += singlePackgeLen;
			}
			return reData;
		}

		QByteArray LBLReceiveCardCentralCtrl::getFPGARegister()
		{
			Q_D(LBLReceiveCardAbstract);
			return d->receiveCardFPGARegister;
		}

		quint16 LBLReceiveCardCentralCtrl::writeModuleParam(quint8 port, quint8 module, QByteArray value, bool sync, int msec)
		{
			QByteArray tempData;
			tempData.append(value);
			quint32 addr = 0;
			return writeFPGARegister(port, module, addr, tempData, sync, msec);
		}

		QByteArray LBLReceiveCardCentralCtrl::readModuleParam(quint8 port, quint8 module, bool sync, int msec)
		{
			Q_D(LBLReceiveCardAbstract);
			quint32 addr = 0;
			d->moduleParam = readFPGARegister(port, module, addr, 1024, sync, msec);
			return d->moduleParam;
		}

		QByteArray LBLReceiveCardCentralCtrl::getModuleParam()
		{
			Q_D(LBLReceiveCardAbstract);
			return d->moduleParam;
		}

		quint16 LBLReceiveCardCentralCtrl::writeDriveICParam(quint8 port, quint8 module, QByteArray value, bool sync, int msec)
		{
			QByteArray tempData;
			tempData.append(value);
			quint32 addr = 0x800;
			return writeFPGARegister(port, module, addr, tempData, sync, msec);
		}

		QByteArray LBLReceiveCardCentralCtrl::readDriveICParam(quint8 port, quint8 module, bool sync, int msec)
		{
			Q_D(LBLReceiveCardAbstract);
			quint32 addr = 0x800;
			d->driveICParam = readFPGARegister(port, module, addr, 1024, sync, msec);
			return d->driveICParam;
		}

		QByteArray LBLReceiveCardCentralCtrl::getDriveICParam()
		{
			Q_D(LBLReceiveCardAbstract);
			return d->driveICParam;
		}

		quint16 LBLReceiveCardCentralCtrl::writeDecodingICParam(quint8 port, quint8 module, QByteArray value, bool sync, int msec)
		{
			QByteArray tempData;
			tempData.append(value);
			quint32 addr = 0x400;
			return writeFPGARegister(port, module, addr, tempData, sync, msec);
		}

		QByteArray LBLReceiveCardCentralCtrl::readDecodingICParam(quint8 port, quint8 module, bool sync, int msec)
		{
			Q_D(LBLReceiveCardAbstract);
			quint32 addr = 0x400;
			d->decodingICParam = readFPGARegister(port, module, addr, 1024, sync, msec);
			return d->decodingICParam;
		}

		QByteArray LBLReceiveCardCentralCtrl::getDecodingICParam()
		{
			Q_D(LBLReceiveCardAbstract);
			return d->decodingICParam;
		}

		quint16 LBLReceiveCardCentralCtrl::writeSaveRCParamByRegister(quint8 port, quint8 module, bool sync, int msec)
		{
			QByteArray tempData;
			quint8 value = 1;
			tempData.append(value);
			quint32 addr = 0x2000002;
            return writeFPGARegister(port, module, addr, tempData, sync, msec);
        }

        quint16 LBLReceiveCardCentralCtrl::writeCalibrationDataErase(quint8 port, quint8 module, bool sync, int msec)
        {
            QByteArray tempData;
            quint8 value = 2;
            tempData.append(value);
            quint32 addr = 0x2000001;
            return writeFPGARegister(port, module, addr, tempData, sync, msec);
        }

		quint16 LBLReceiveCardCentralCtrl::writeCalibrationDataSave(quint8 port, quint8 module, bool sync, int msec)
		{
			QByteArray tempData;
			quint8 value = 2;
			tempData.append(value);
			quint32 addr = 0x2000002;
			return writeFPGARegister(port, module, addr, tempData, sync, msec);
		}

		quint16 LBLReceiveCardCentralCtrl::writeCalibrationDataReload(quint8 port, quint8 module, bool sync, int msec)
		{
			QByteArray tempData;
			quint8 value = 2;
			tempData.append(value);
			quint32 addr = 0x2000000;
			return writeFPGARegister(port, module, addr, tempData, sync, msec);
		}

		quint16 LBLReceiveCardCentralCtrl::readStatusInfo(quint8 portStart, quint8 portCount, quint8 moduleStart, quint8 moduleCount, quint8 lengthFlag, bool sync, int msec)
		{
			Q_D(LBLReceiveCardAbstract);
			d->m_rcStatusInfo.clear();
			//在此处组好集控的包，直接调用通信层
			LBLPackageInteCtrl_ReadRCStatusInfo pack(portStart, portCount, moduleStart, moduleCount, lengthFlag);
			pack.SetCmdTargetDevice(d->m_registerTargetDeviceType);
			pack.initByDetectInfo(d->m_parentItemDetectInfo);
			pack.build(0);
			LBL_DECLARE_COMMANDSEND(d, pack)
		}

		QList<LBL::RC::SRCStatusInfo> LBLReceiveCardCentralCtrl::getStatusInfo()
		{
			return d_func()->m_rcStatusInfo;
		}

		quint16 LBLReceiveCardCentralCtrl::readMonitorInfo(quint8 portIndex, bool sync, int msec)
		{
			Q_D(LBLReceiveCardAbstract);
			int startAddrs = portIndex * sizeof(LBL::RC::SRCMonitorPortInfo);
			//在此处组好集控的包，直接调用通信层
			LBLPackageInteCtrl_ReadRCMonitorInfo pack(startAddrs, sizeof(LBL::RC::SRCMonitorPortInfo));
			pack.SetCmdTargetDevice(d->m_registerTargetDeviceType);
			pack.initByDetectInfo(d->m_parentItemDetectInfo);
			pack.build(0);
			LBL_DECLARE_COMMANDSEND(d, pack);
		}

		QList<SRCMonitorInfo> LBLReceiveCardCentralCtrl::getMonitorInfo()
		{
			return d_func()->m_rcMonitorInfo;
		}

		quint16 LBLReceiveCardCentralCtrl::writeSaveRCParam(quint8 port, quint16 module, bool sync, int msec)
		{
			Q_D(LBLReceiveCardAbstract);
			//在此处组好集控的包，直接调用通信层
			LBLPackageInteCtrl_WriteSaveRCParam pack(port,module);
			pack.SetCmdTargetDevice(d->m_registerTargetDeviceType);
			pack.initByDetectInfo(d->m_parentItemDetectInfo);
			pack.build(0);
			LBL_DECLARE_COMMANDSEND(d, pack)
		}

		bool LBLReceiveCardCentralCtrl::init()
		{
			registerCallBack();
			return true;
		}

		void LBLReceiveCardCentralCtrl::registerCallBack()
		{
			Q_D(LBLReceiveCardAbstract);

			d->m_packageMgr.registerPackage(LBLPackageInteCtrl_WriteRCFPGARegister(),
				std::bind(&LBLReceiveCardCentralCtrl::onParseWriteFPGARegister, this, std::placeholders::_1));
			d->m_packageMgr.registerPackage(LBLPackageInteCtrl_ReadRCFPGARegister(),
				std::bind(&LBLReceiveCardCentralCtrl::onParseReadFPGARegister, this, std::placeholders::_1));
			d->m_packageMgr.registerPackage(LBLPackageInteCtrl_ReadRCStatusInfo(),
				std::bind(&LBLReceiveCardCentralCtrl::onParseReadStatusInfo, this, std::placeholders::_1));
			d->m_packageMgr.registerPackage(LBLPackageInteCtrl_ReadRCMonitorInfo(),
				std::bind(&LBLReceiveCardCentralCtrl::onParseReadMonitorInfo, this, std::placeholders::_1));
			d->m_packageMgr.registerPackage(LBLPackageInteCtrl_WriteSaveRCParam(),
				std::bind(&LBLReceiveCardCentralCtrl::onParseWriteSaveRCParam, this, std::placeholders::_1));
		}

		quint16 LBLReceiveCardCentralCtrl::onParseWriteFPGARegister(const QByteArray& data)
        {
			LBLPackageInteCtrl_WriteRCFPGARegister pack(data);
			quint16 ret = pack.getOperationResult();
			if (ret == LBLPackage::EOR_Success) {}
			return ret;
		}

		quint16 LBLReceiveCardCentralCtrl::onParseReadFPGARegister(const QByteArray & data)
		{
			Q_D(LBLReceiveCardAbstract);
			LBLPackageInteCtrl_ReadRCFPGARegister pack(data);
			quint16 ret = pack.getOperationResult();
			if (LAPI::EResult::ER_INTECTRL_Success != ret)
				return ret;
			quint16 len = pack.getDataLength();
			Q_UNUSED(len);
			d->receiveCardFPGARegister = pack.getReplyData();
			return ret;
		}

		quint16 LBLReceiveCardCentralCtrl::onParseReadStatusInfo(const QByteArray & data)
		{
			Q_D(LBLReceiveCardAbstract);
			LBLPackageInteCtrl_ReadRCStatusInfo pack(data);
			quint16 ret = pack.getOperationResult();
			if (LAPI::EResult::ER_INTECTRL_Success != ret)
				return ret;
			QByteArray reData;
			//解析
			if (pack.getSourceDevice() == LBLPackage::EDeviceType::EDT_MCU_In_Sender) {
				reData = pack.getReplyData();
			}
			else if (pack.getSourceDevice() == LBLPackage::EDeviceType::EDT_Android) {
				reData = pack.getOldReplyData();
			}
			if (reData.startsWith(QByteArray::fromHex("F00F"))) {
				//广州
				d->m_rcStatusInfo.clear();
                for (int i = 0; i < reData.size() / int(sizeof(SRCStatusInfo)); ++i) {
                    SRCStatusInfo temp;
                    QByteArray data=QByteArray(reData.constData() + i * (sizeof(SRCStatusInfo)), sizeof(SRCStatusInfo));
                    temp.SetData(data);
					d->m_rcStatusInfo.append(temp);
				}
			}
			return ret;
		}

		quint16 LBLReceiveCardCentralCtrl::onParseReadMonitorInfo(const QByteArray & data)
		{
			Q_D(LBLReceiveCardAbstract);
			LBLPackageInteCtrl_ReadRCMonitorInfo pack(data);
			quint16 ret = pack.getOperationResult();
			if (LAPI::EResult::ER_INTECTRL_Success != ret)
				return ret;
			QByteArray reData;
			//解析
			/*if (pack.getSourceDevice() == LBLPackage::EDeviceType::EDT_MCU_In_Sender) {*/
				d->m_rcMonitorInfo.clear();
				reData = pack.getReplyData();
				SRCMonitorPortInfo temp;
				temp.SetData(reData);
				if (temp.IsValid()) {
					d->m_rcMonitorInfo.append(temp.GetPortMonitorList());
				}
			/*}*/
			return ret;
		}

		quint16 LBLReceiveCardCentralCtrl::onParseWriteSaveRCParam(const QByteArray & data)
        {
			LBLPackageInteCtrl_WriteSaveRCParam pack(data);
			return pack.getOperationResult();
		}

	}
}
