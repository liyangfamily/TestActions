/*********************************************************************************************************
** This file is part of the LBL_CommunicatEngine module of the LBL Toolkit.
*********************************************************************************************************/

/*!
\class LBLFileTransferPackage

\inmodule LBL_CommunicatEngine

\brief The class is base class of the fileTransfer protocol. it is used to define some fixed protocol parameters.
Generally not used directly.

\code

\endcode

\note:

*/

#include "LBL_CommunicatEngine/LBLFileTransferPackage.h"

LBLFileTransferPackage::LBLFileTransferPackage()
{
	defalutInit();
}

LBLFileTransferPackage::LBLFileTransferPackage(const QByteArray& data) :
	LBLPackage(data)
{

}

LBLFileTransferPackage::~LBLFileTransferPackage()
{
}

quint8 LBLFileTransferPackage::CmdProtocolNum() const
{
	return quint8(EPackageClass::EPC_FileTransfer);
}

quint8 LBLFileTransferPackage::CmdProtocolVersion() const
{
	return quint8(EPackageVersion::EPV_3_0);
}

void LBLFileTransferPackage::defalutInit()
{
	m_targetDeviceType = EDeviceType::EDT_NULL;
	m_sourceDeviceType = EDeviceType::EDT_CtrlSW;
	m_uuidType = 0;
	m_uuid = QUuid();
	m_sendCardIndex = 0;
}

LBLPackageFileTransfer_CommonRequestFile::LBLPackageFileTransfer_CommonRequestFile(quint16 type, QString name):
	m_fileType(type)
{
	setFileName(name);
}

quint16 LBLPackageFileTransfer_CommonRequestFile::getOperationResult() const
{
	DO_GETOPERATIONRESULT()
}

QByteArray LBLPackageFileTransfer_CommonRequestFile::CmdContent() const
{
	QByteArray temp;
	temp.append((char *)&m_fileType, 2);
	temp.append((char *)&m_fileNameLength, 2);
	temp.append(m_fileName);
	return temp;
}

LBLPackageFileTransfer_CommonStartSendFile::LBLPackageFileTransfer_CommonStartSendFile(quint16 type, quint32 fileLength, QString name) :
	m_fileType(type), m_fileLenght(fileLength)
{
	setFileName(name);
}

quint16 LBLPackageFileTransfer_CommonStartSendFile::getOperationResult() const
{
	DO_GETOPERATIONRESULT()
}

quint16 LBLPackageFileTransfer_CommonStartSendFile::getMaxLengthOfSinglePackage() const
{
	quint16 value = 0;
	QByteArray buffer = getContent();
	if (buffer.size() < 4) {
		return value;
	}
	memcpy_s(&value, 2, buffer.constData() + 2, 2);
	return value;
}

quint32 LBLPackageFileTransfer_CommonStartSendFile::getSendFileID() const
{
	quint32 value = 0;
	QByteArray buffer = getContent();
	if (buffer.size() < 8) {
		return value;
	}
	memcpy_s(&value, 4, buffer.constData() + 4, 4);
	return value;
}

QByteArray LBLPackageFileTransfer_CommonStartSendFile::CmdContent() const
{
	QByteArray temp;
	temp.append((char *)&m_fileType, 2);
	temp.append((char *)&m_fileLenght, 4);
	temp.append((char *)&m_fileNameLength, 2);
	temp.append(m_fileName);
	return temp;
}

LBLPackageFileTransfer_CommonSendFileData::LBLPackageFileTransfer_CommonSendFileData(quint32 sendFileID, quint16 packageIndex, QByteArray package):
	m_sendFileID(sendFileID),m_packageIndex(packageIndex)
{
	setPackage(package);
}

quint16 LBLPackageFileTransfer_CommonSendFileData::getOperationResult() const
{
	DO_GETOPERATIONRESULT()
}

QByteArray LBLPackageFileTransfer_CommonSendFileData::CmdContent() const
{
	QByteArray temp;
	temp.append((char *)&m_sendFileID, 4);
	temp.append((char *)&m_packageIndex, 2);
	temp.append((char *)&m_packageLength, 2);
	temp.append(m_package);
	return temp;
}

LBLPackageFileTransfer_CommonRequestUpgrade::LBLPackageFileTransfer_CommonRequestUpgrade(quint16 fileType):
	m_fileType(fileType)
{
}

quint16 LBLPackageFileTransfer_CommonRequestUpgrade::getOperationResult() const
{
	DO_GETOPERATIONRESULT()
}

quint8 LBLPackageFileTransfer_CommonRequestUpgrade::getOperatFailReason() const
{
	quint8 value = 0;
	QByteArray buffer = getContent();
	if (buffer.size() < 3) {
		return value;
	}
	memcpy_s(&value, 1, buffer.constData() + 2, 1);
	return value;
}

QByteArray LBLPackageFileTransfer_CommonRequestUpgrade::CmdContent() const
{
	QByteArray temp;
	temp.append((char *)&m_fileType, 2);
	return temp;
}

LBLPackageFileTransfer_CommonQueryUpgradeStatus::LBLPackageFileTransfer_CommonQueryUpgradeStatus(quint16 fileType) :
	m_fileType(fileType)
{
}

quint16 LBLPackageFileTransfer_CommonQueryUpgradeStatus::getOperationResult() const
{
	DO_GETOPERATIONRESULT()
}

quint8 LBLPackageFileTransfer_CommonQueryUpgradeStatus::getOperatSteps() const
{
	quint8 value = 0;
	QByteArray buffer = getContent();
	if (buffer.size() < 3) {
		return value;
	}
	memcpy_s(&value, 1, buffer.constData() + 2, 1);
	return value;
}

quint8 LBLPackageFileTransfer_CommonQueryUpgradeStatus::getOperatProgress() const
{
	quint8 value = 0;
	QByteArray buffer = getContent();
	if (buffer.size() < 4) {
		return value;
	}
	memcpy_s(&value, 1, buffer.constData() + 3, 1);
	return value;
}

QByteArray LBLPackageFileTransfer_CommonQueryUpgradeStatus::CmdContent() const
{
	QByteArray temp;
	temp.append((char *)&m_fileType, 2);
	return temp;
}











LBLPackageFileTransfer_RequestUpgradeForMCU::LBLPackageFileTransfer_RequestUpgradeForMCU(quint16 fileType, quint32 fileLength, quint8 portIndex /*= 0xFF*/,\
	quint16 moduleIndex /*= 0xFFFF*/):
	m_fileType(fileType),m_fileLength(fileLength),m_portIndex(portIndex),m_moduleIndex(moduleIndex)
{
}

quint16 LBLPackageFileTransfer_RequestUpgradeForMCU::getOperationResult() const
{
	DO_GETOPERATIONRESULT()
}

quint8 LBLPackageFileTransfer_RequestUpgradeForMCU::getPortIndex() const
{
	quint8 value = 0;
	QByteArray buffer = getContent();
	if (buffer.size() < 3) {
		return value;
	}
	memcpy_s(&value, 1, buffer.constData() + 2, 1);
	return value;
}

quint16 LBLPackageFileTransfer_RequestUpgradeForMCU::getModuleIndex() const
{
	quint16 value = 0;
	QByteArray buffer = getContent();
	if (buffer.size() < 5) {
		return value;
	}
	memcpy_s(&value, 2, buffer.constData() + 3, 2);
	return value;
}

quint16 LBLPackageFileTransfer_RequestUpgradeForMCU::getFileType() const
{
	quint16 value = 0;
	QByteArray buffer = getContent();
	if (buffer.size() < 7) {
		return value;
	}
	memcpy_s(&value, 2, buffer.constData() + 5, 2);
	return value;
}

quint16 LBLPackageFileTransfer_RequestUpgradeForMCU::getMaxLengthOfSinglePackage() const
{
	quint16 value = 0;
	QByteArray buffer = getContent();
	if (buffer.size() < 9) {
		return value;
	}
	memcpy_s(&value, 2, buffer.constData() + 7, 2);
	return value;
}

QByteArray LBLPackageFileTransfer_RequestUpgradeForMCU::CmdContent() const
{
	QByteArray temp;
	temp.append((char *)&m_portIndex, 1);
	temp.append((char *)&m_moduleIndex, 2);
	temp.append((char *)&m_fileType, 2);
	temp.append((char *)&m_fileLength, 4);
	return temp;
}

LBLPackageFileTransfer_SendFileDataForMCU::LBLPackageFileTransfer_SendFileDataForMCU(quint16 fileType, quint32 packageIndex, QByteArray package, \
	quint8 portIndex /*= 0xFF*/, quint16 moduleIndex /*= 0xFFFF*/):
    m_portIndex(portIndex),m_moduleIndex(moduleIndex),m_fileType(fileType),m_packageIndex(packageIndex),m_package(package)
{
}

quint16 LBLPackageFileTransfer_SendFileDataForMCU::getOperationResult() const
{
	DO_GETOPERATIONRESULT()
}

quint8 LBLPackageFileTransfer_SendFileDataForMCU::getPortIndex() const
{
	quint8 value = 0;
	QByteArray buffer = getContent();
	if (buffer.size() < 3) {
		return value;
	}
	memcpy_s(&value, 1, buffer.constData() + 2, 1);
	return value;
}

quint16 LBLPackageFileTransfer_SendFileDataForMCU::getModuleIndex() const
{
	quint16 value = 0;
	QByteArray buffer = getContent();
	if (buffer.size() < 5) {
		return value;
	}
	memcpy_s(&value, 2, buffer.constData() + 3, 2);
	return value;
}

quint16 LBLPackageFileTransfer_SendFileDataForMCU::getFileType() const
{
	quint16 value = 0;
	QByteArray buffer = getContent();
	if (buffer.size() < 7) {
		return value;
	}
	memcpy_s(&value, 2, buffer.constData() + 5, 2);
	return value;
}

quint32 LBLPackageFileTransfer_SendFileDataForMCU::getPackageIndex() const
{
	quint32 value = 0;
	QByteArray buffer = getContent();
	if (buffer.size() < 11) {
		return value;
	}
	memcpy_s(&value, 4, buffer.constData() + 7, 4);
	return value;
}

QByteArray LBLPackageFileTransfer_SendFileDataForMCU::CmdContent() const
{
	QByteArray temp;
	temp.append((char *)&m_portIndex, 1);
	temp.append((char *)&m_moduleIndex, 2);
	temp.append((char *)&m_fileType, 2);
	temp.append((char *)&m_packageIndex, 4);
	temp.append(m_package);
	return temp;
}

LBLPackageFileTransfer_RequestFileForMCU::LBLPackageFileTransfer_RequestFileForMCU(quint16 fileType):
	m_fileType(fileType)
{
}

quint16 LBLPackageFileTransfer_RequestFileForMCU::getOperationResult() const
{
	DO_GETOPERATIONRESULT()
}

quint16 LBLPackageFileTransfer_RequestFileForMCU::getFileType() const
{
	quint16 value = 0;
	QByteArray buffer = getContent();
	if (buffer.size() < 4) {
		return value;
	}
	memcpy_s(&value, 2, buffer.constData() + 2, 2);
	return value;
}

quint32 LBLPackageFileTransfer_RequestFileForMCU::getTotalFileLength() const
{
	quint32 value = 0;
	QByteArray buffer = getContent();
	if (buffer.size() < 8) {
		return value;
	}
	memcpy_s(&value, 4, buffer.constData() + 4, 4);
	return value;
}

quint16 LBLPackageFileTransfer_RequestFileForMCU::getSinglePackageLenth() const
{
	quint16 value = 0;
	QByteArray buffer = getContent();
	if (buffer.size() < 10) {
		return value;
	}
	memcpy_s(&value, 2, buffer.constData() + 8, 2);
	return value;
}

QByteArray LBLPackageFileTransfer_RequestFileForMCU::CmdContent() const
{
	QByteArray temp;
	temp.append((char *)&m_fileType, 2);
	return temp;
}

LBLPackageFileTransfer_ReceiveFileDataForMCU::LBLPackageFileTransfer_ReceiveFileDataForMCU(quint16 fileType, quint32 packageIndex):
	m_fileType(fileType),m_packageIndex(packageIndex)
{
}

quint16 LBLPackageFileTransfer_ReceiveFileDataForMCU::getOperationResult() const
{
	DO_GETOPERATIONRESULT()
}

quint16 LBLPackageFileTransfer_ReceiveFileDataForMCU::getFileType() const
{
	quint16 value = 0;
	QByteArray buffer = getContent();
	if (buffer.size() < 4) {
		return value;
	}
	memcpy_s(&value, 2, buffer.constData() + 2, 2);
	return value;
}

quint32 LBLPackageFileTransfer_ReceiveFileDataForMCU::getPackageIndex() const
{
	quint32 value = 0;
	QByteArray buffer = getContent();
	if (buffer.size() < 8) {
		return value;
	}
	memcpy_s(&value, 4, buffer.constData() + 4, 4);
	return value;
}

QByteArray LBLPackageFileTransfer_ReceiveFileDataForMCU::getPackageData() const
{
	QByteArray value;
	QByteArray buffer = getContent();
	if (buffer.size() < 9) {
		return value;
	}
	value.append(buffer.mid(8, buffer.size() - 8));
	return value;
}

QByteArray LBLPackageFileTransfer_ReceiveFileDataForMCU::CmdContent() const
{
	QByteArray temp;
	temp.append((char *)&m_fileType, 2);
	temp.append((char *)&m_packageIndex, 4);
	return temp;
}
