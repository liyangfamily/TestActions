#include "LBL_CommunicatEngine/LBLInteCtrlVideoSourcePackage.h"


quint8 LBLPackageInteCtrl_ReadVideoSourceVolume::getVolume() const
{
	quint8 value = 0;
	QByteArray buffer = getContent();
	if (buffer.size() < 1) {
		return value;
	}
	value = buffer.at(0);
	return value;
}

quint8 LBLPackageInteCtrl_ReadVideoSourceByPass::getBypass() const
{
	quint8 value = 0;
	QByteArray buffer = getContent();
	if (buffer.size() < 1) {
		return value;
	}
    memcpy(&value, buffer.constData(), 1);
	return value;
}

LBLPackageInteCtrl_WriteVideoSourceByPass::LBLPackageInteCtrl_WriteVideoSourceByPass(quint8 bypass) :
	m_bypass(bypass)
{
}

quint16 LBLPackageInteCtrl_WriteVideoSourceByPass::getOperationResult() const
{
	DO_GETOPERATIONRESULT()
}
 
quint8 LBLPackageInteCtrl_ReadVideoSourceRatio::getRatio() const
{
	quint8 value = 0;
	QByteArray buffer = getContent();
	if (buffer.size() < 1) {
		return value;
	}
    memcpy(&value, buffer.constData(), 1);
	return value;
}

LBLPackageInteCtrl_WriteVideoSourceRatio::LBLPackageInteCtrl_WriteVideoSourceRatio(quint8 size) :
	m_size(size)
{
}

quint16 LBLPackageInteCtrl_WriteVideoSourceRatio::getOperationResult() const
{
	DO_GETOPERATIONRESULT()
}

quint8 LBLPackageInteCtrl_ReadVideoSource::getSource() const
{
	quint8 value = 0;
	QByteArray buffer = getContent();
	if (buffer.size() < 1) {
		return value;
	}
    memcpy(&value, buffer.constData(), 1);
	return value;
}

LBLPackageInteCtrl_WriteVideoSource::LBLPackageInteCtrl_WriteVideoSource(quint8 source) :
	m_source(source)
{
}

quint16 LBLPackageInteCtrl_WriteVideoSource::getOperationResult() const
{
	DO_GETOPERATIONRESULT()
}

quint8 LBLPackageInteCtrl_ReadVideoSourceContrast::getContrast() const
{
	quint8 value = 0;
	QByteArray buffer = getContent();
	if (buffer.size() < 1) {
		return value;
	}
    memcpy(&value, buffer.constData(), 1);
	return value;
}

LBLPackageInteCtrl_WriteVideoSourceContrast::LBLPackageInteCtrl_WriteVideoSourceContrast(quint8 contrast) :
	m_contrast(contrast)
{
}

quint16 LBLPackageInteCtrl_WriteVideoSourceContrast::getOperationResult() const
{
	DO_GETOPERATIONRESULT()
}

quint8 LBLPackageInteCtrl_ReadVideoSourceColortemperature::getColortemperature() const
{
	quint8 value = 0;
	QByteArray buffer = getContent();
	if (buffer.size() < 1) {
		return value;
	}
    memcpy(&value, buffer.constData(), 1);
	return value;
}

LBLPackageInteCtrl_WriteVideoSourceColortemperature::LBLPackageInteCtrl_WriteVideoSourceColortemperature(quint8 colortemperature) :
	m_colortemperature(colortemperature)
{
}

quint16 LBLPackageInteCtrl_WriteVideoSourceColortemperature::getOperationResult() const
{
	DO_GETOPERATIONRESULT()
}

quint8 LBLPackageInteCtrl_ReadVideoSourceBrightness::getBrightness() const
{
	quint8 value = 0;
	QByteArray buffer = getContent();
	if (buffer.size() < 1) {
		return value;
	}
	value = buffer.at(0);
	return value;
}

LBLPackageInteCtrl_WriteVideoSourceBrightness::LBLPackageInteCtrl_WriteVideoSourceBrightness(quint8 brightness) :
	m_brightness(brightness)
{
}

quint16 LBLPackageInteCtrl_WriteVideoSourceBrightness::getOperationResult() const
{
	DO_GETOPERATIONRESULT()
}

quint8 LBLPackageInteCtrl_ReadVideoSourceRGain::getRGain() const
{
	quint8 value = 0;
	QByteArray buffer = getContent();
	if (buffer.size() < 1) {
		return value;
	}
	value = buffer.at(0);
	return value;
}

LBLPackageInteCtrl_WriteVideoSourceRGain::LBLPackageInteCtrl_WriteVideoSourceRGain(quint8 rGain) :
	m_rGain(rGain)
{
}

quint16 LBLPackageInteCtrl_WriteVideoSourceRGain::getOperationResult() const
{
	DO_GETOPERATIONRESULT()
}

quint8 LBLPackageInteCtrl_ReadVideoSourceGGain::getGGain() const
{
	quint8 value = 0;
	QByteArray buffer = getContent();
	if (buffer.size() < 1) {
		return value;
	}
	value = buffer.at(0);
	return value;
}

LBLPackageInteCtrl_WriteVideoSourceGGain::LBLPackageInteCtrl_WriteVideoSourceGGain(quint8 gGain) :
	m_gGain(gGain)
{
}

quint16 LBLPackageInteCtrl_WriteVideoSourceGGain::getOperationResult() const
{
	DO_GETOPERATIONRESULT()
}

quint8 LBLPackageInteCtrl_ReadVideoSourceBGain::getBGain() const
{
	quint8 value = 0;
	QByteArray buffer = getContent();
	if (buffer.size() < 1) {
		return value;
	}
	value = buffer.at(0);
	return value;
}

LBLPackageInteCtrl_WriteVideoSourceBGain::LBLPackageInteCtrl_WriteVideoSourceBGain(quint8 bGain) :
	m_bGain(bGain)
{
}

quint16 LBLPackageInteCtrl_WriteVideoSourceBGain::getOperationResult() const
{
	DO_GETOPERATIONRESULT()
}

quint8 LBLPackageInteCtrl_ReadVideoSourceRGBGain::getRGain() const
{
	quint8 value = 0;
	QByteArray buffer = getContent();
	if (buffer.size() < 1) {
		return value;
	}
	value = buffer.at(0);
	return value;
}

quint8 LBLPackageInteCtrl_ReadVideoSourceRGBGain::getGGain() const
{
	quint8 value = 0;
	QByteArray buffer = getContent();
	if (buffer.size() < 2) {
		return value;
	}
	value = buffer.at(1);
	return value;
}

quint8 LBLPackageInteCtrl_ReadVideoSourceRGBGain::getBGain() const
{
	quint8 value = 0;
	QByteArray buffer = getContent();
	if (buffer.size() < 3) {
		return value;
	}
	value = buffer.at(2);
	return value;
}

LBLPackageInteCtrl_WriteVideoSourceRGBGain::LBLPackageInteCtrl_WriteVideoSourceRGBGain(quint8 rGain, quint8 gGain, quint8 bGain):
	m_rGain(rGain),m_gGain(gGain),m_bGain(bGain)
{
}

quint16 LBLPackageInteCtrl_WriteVideoSourceRGBGain::getOperationResult() const
{
	DO_GETOPERATIONRESULT()
}

QByteArray LBLPackageInteCtrl_WriteVideoSourceRGBGain::CmdContent() const
{
	QByteArray temp;
	temp.append(m_rGain);
	temp.append(m_gGain);
	temp.append(m_bGain);
	return temp;
}

LBLPackageInteCtrl_WriteVideoSourceVolume::LBLPackageInteCtrl_WriteVideoSourceVolume(quint8 volume) :
	m_volume(volume)
{
}

quint16 LBLPackageInteCtrl_WriteVideoSourceVolume::getOperationResult() const
{
	DO_GETOPERATIONRESULT()
}

QSize LBLPackageInteCtrl_ReadVideoSourceResolution::getResolution() const
{
	QSize value;
	QByteArray buffer = getContent();
	if (buffer.size() < 8) {
		return value;
	}
	quint32 tempValue = 0;
    memcpy(&tempValue, buffer.constData(), 4);
	value.setWidth(tempValue);
    memcpy(&tempValue, buffer.constData() + 4, 4);
	value.setHeight(tempValue);
	return value;
}

quint8 LBLPackageInteCtrl_ReadVideoSourceResolution::getRefreshRate() const
{
	quint8 value=0;
	QByteArray buffer = getContent();
	if (buffer.size() < 9) {
		return value;
	}
	value = buffer.at(8);
	return value;
}

LBLPackageInteCtrl_WriteVideoSourceResolution::LBLPackageInteCtrl_WriteVideoSourceResolution(QSize value, quint8 rate):
	m_resolution(value),m_refreshRate(rate)
{
}

quint16 LBLPackageInteCtrl_WriteVideoSourceResolution::getOperationResult() const
{
	DO_GETOPERATIONRESULT();
}

QByteArray LBLPackageInteCtrl_WriteVideoSourceResolution::CmdContent() const
{
	QByteArray temp;
	quint32 tempValue = m_resolution.width();
	temp.append((char *)&tempValue, 4);
	tempValue = m_resolution.height();
	temp.append((char *)&tempValue, 4);
	temp.append(m_refreshRate);
	return temp;
}

quint8 LBLPackageInteCtrl_ReadVideoSourceCombinationInfo::getBrightness() const
{
	quint8 value=0;
	QByteArray buffer = getContent();
	if (buffer.size() < 1) {
		return value;
	}
	value = buffer.at(0);
	return value;
}

quint8 LBLPackageInteCtrl_ReadVideoSourceCombinationInfo::getColortemperature() const
{
	quint8 value=0;
	QByteArray buffer = getContent();
	if (buffer.size() < 2) {
		return value;
	}
	value = buffer.at(1);
	return value;
}

quint8 LBLPackageInteCtrl_ReadVideoSourceCombinationInfo::getRatio() const
{
	quint8 value=0;
	QByteArray buffer = getContent();
	if (buffer.size() < 3) {
		return value;
	}
	value = buffer.at(2);
	return value;
}

quint8 LBLPackageInteCtrl_ReadVideoSourceCombinationInfo::getSource() const
{
	quint8 value=0;
	QByteArray buffer = getContent();
	if (buffer.size() < 4) {
		return value;
	}
	value = buffer.at(3);
	return value;
}

quint8 LBLPackageInteCtrl_ReadVideoSourceCombinationInfo::getVolume() const
{
	quint8 value=0;
	QByteArray buffer = getContent();
	if (buffer.size() < 5) {
		return value;
	}
	value = buffer.at(4);
	return value;
}

quint8 LBLPackageInteCtrl_ReadVideoSourceCombinationInfo::getContrast() const
{
	quint8 value=0;
	QByteArray buffer = getContent();
	if (buffer.size() < 6) {
		return value;
	}
	value = buffer.at(5);
	return value;
}

quint8 LBLPackageInteCtrl_ReadVideoSourceCombinationInfo::getSceneMode() const
{
	quint8 value=0;
	QByteArray buffer = getContent();
	if (buffer.size() < 7) {
		return value;
	}
	value = buffer.at(6);
	return value;
}

quint8 LBLPackageInteCtrl_ReadVideoSourceSceneMode::getSceneMode() const
{
	quint8 value=0;
	QByteArray buffer = getContent();
	if (buffer.size() < 1) {
		return value;
	}
	value = buffer.at(0);
	return value;
}

LBLPackageInteCtrl_WriteVideoSourceSceneMode::LBLPackageInteCtrl_WriteVideoSourceSceneMode(quint8 value):
	m_sceneMode(value)
{
}

quint16 LBLPackageInteCtrl_WriteVideoSourceSceneMode::getOperationResult() const
{
	DO_GETOPERATIONRESULT();
}

quint8 LBLPackageInteCtrl_ReadVideoSourceSplitScreenMode::getSplitScreenMode() const
{
	quint8 value=0;
	QByteArray buffer = getContent();
	if (buffer.size() < 1) {
		return value;
	}
	value = buffer.at(0);
	return value;
}

LBLPackageInteCtrl_WriteVideoSourceSplitScreenMode::LBLPackageInteCtrl_WriteVideoSourceSplitScreenMode(quint8 value):
	m_splitScreenMode(value)
{
}

quint16 LBLPackageInteCtrl_WriteVideoSourceSplitScreenMode::getOperationResult() const
{
	DO_GETOPERATIONRESULT();
}
