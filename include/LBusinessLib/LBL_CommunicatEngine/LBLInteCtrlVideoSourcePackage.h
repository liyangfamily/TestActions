#pragma once
#include "LBL_CommunicatEngine/LBLInteCtrlPackage.h"

class LBL_COMMUNICATENGINE_EXPORT LBLPackageInteCtrl_ReadVideoSourceVolume : public LBLInteCtrlPackage
{
	LBL_DECLARE_PACKAGECONSTRUCTOR(LBLPackageInteCtrl_ReadVideoSourceVolume, LBLInteCtrlPackage)
public:

	quint8 getVolume() const;

protected:
	quint16 CmdNum() const override {
		return quint16(ECommand::EC_Read_VideoSourceVolume);
	}
	QByteArray CmdContent() const override {
		return QByteArray();
	}
};

class LBL_COMMUNICATENGINE_EXPORT LBLPackageInteCtrl_WriteVideoSourceVolume : public LBLInteCtrlPackage
{
	LBL_DECLARE_PACKAGECONSTRUCTOR(LBLPackageInteCtrl_WriteVideoSourceVolume, LBLInteCtrlPackage)
public:
	LBLPackageInteCtrl_WriteVideoSourceVolume(quint8 volume);
	quint16 getOperationResult() const;
	void  setBypass(quint8 volume) {
		m_volume = volume;
	}

protected:
	quint16 CmdNum() const override {
		return quint16(ECommand::EC_Write_VideoSourceVolume);
	}
	QByteArray CmdContent() const override {
		return QByteArray((char *)&m_volume, 1);
	}
private:
	quint8 m_volume = 0;
};

class LBL_COMMUNICATENGINE_EXPORT LBLPackageInteCtrl_ReadVideoSourceByPass : public LBLInteCtrlPackage
{
	LBL_DECLARE_PACKAGECONSTRUCTOR(LBLPackageInteCtrl_ReadVideoSourceByPass, LBLInteCtrlPackage)
public:

	quint8 getBypass() const;

protected:
	quint16 CmdNum() const override {
		return quint16(ECommand::EC_Read_VideoSourceByPass);
	}
	QByteArray CmdContent() const override {
		return QByteArray();
	}
};

class LBL_COMMUNICATENGINE_EXPORT LBLPackageInteCtrl_WriteVideoSourceByPass : public LBLInteCtrlPackage
{
	LBL_DECLARE_PACKAGECONSTRUCTOR(LBLPackageInteCtrl_WriteVideoSourceByPass, LBLInteCtrlPackage)
public:
	LBLPackageInteCtrl_WriteVideoSourceByPass(quint8 bypass);
	quint16 getOperationResult() const;
	void  setBypass(quint8 bypass) {
		m_bypass = bypass;
	}
	
protected:
	quint16 CmdNum() const override {
		return quint16(ECommand::EC_Write_VideoSourceByPass);
	}
	QByteArray CmdContent() const override {
		return QByteArray((char *)&m_bypass, 1);
	}
private:
	quint8 m_bypass = 0;
};

class LBL_COMMUNICATENGINE_EXPORT LBLPackageInteCtrl_ReadVideoSourceRatio : public LBLInteCtrlPackage
{
	LBL_DECLARE_PACKAGECONSTRUCTOR(LBLPackageInteCtrl_ReadVideoSourceRatio, LBLInteCtrlPackage)
public:
	quint8 getRatio() const;

protected:
	quint16 CmdNum() const override {
		return quint16(ECommand::EC_Read_VideoSourceRatio);
	}
	QByteArray CmdContent() const override {
		return QByteArray();
	}
};

class LBL_COMMUNICATENGINE_EXPORT LBLPackageInteCtrl_WriteVideoSourceRatio : public LBLInteCtrlPackage
{
	LBL_DECLARE_PACKAGECONSTRUCTOR(LBLPackageInteCtrl_WriteVideoSourceRatio, LBLInteCtrlPackage)
public:
	LBLPackageInteCtrl_WriteVideoSourceRatio(quint8 size);
	quint16 getOperationResult() const;
	void  seSize(quint8 size) {
		m_size = size;
	}

protected:
	quint16 CmdNum() const override {
		return quint16(ECommand::EC_Write_VideoSourceRatio);
	}
	QByteArray CmdContent() const override {
		return QByteArray((char *)&m_size, 1);
	}
private:
	quint8 m_size = 0;
};

class LBL_COMMUNICATENGINE_EXPORT LBLPackageInteCtrl_ReadVideoSource : public LBLInteCtrlPackage
{
	LBL_DECLARE_PACKAGECONSTRUCTOR(LBLPackageInteCtrl_ReadVideoSource, LBLInteCtrlPackage)
public:
	quint8 getSource() const;

protected:
	quint16 CmdNum() const override {
		return quint16(ECommand::EC_Read_VideoSource);
	}
	QByteArray CmdContent() const override {
		return QByteArray();
	}
};

class LBL_COMMUNICATENGINE_EXPORT LBLPackageInteCtrl_WriteVideoSource : public LBLInteCtrlPackage
{
	LBL_DECLARE_PACKAGECONSTRUCTOR(LBLPackageInteCtrl_WriteVideoSource, LBLInteCtrlPackage)
public:
	LBLPackageInteCtrl_WriteVideoSource(quint8 source);
	quint16 getOperationResult() const;
	void  seSize(quint8 source) {
		m_source = source;
	}

protected:
	quint16 CmdNum() const override {
		return quint16(ECommand::EC_Write_VideoSource);
	}
	QByteArray CmdContent() const override {
		return QByteArray((char *)&m_source, 1);
	}
private:
	quint8 m_source = 0;
};

class LBL_COMMUNICATENGINE_EXPORT LBLPackageInteCtrl_ReadVideoSourceContrast : public LBLInteCtrlPackage
{
	LBL_DECLARE_PACKAGECONSTRUCTOR(LBLPackageInteCtrl_ReadVideoSourceContrast, LBLInteCtrlPackage)
public:
	quint8 getContrast() const;

protected:
	quint16 CmdNum() const override {
		return quint16(ECommand::EC_Read_VideoSourceContrast);
	}
	QByteArray CmdContent() const override {
		return QByteArray();
	}
};

class LBL_COMMUNICATENGINE_EXPORT LBLPackageInteCtrl_WriteVideoSourceContrast : public LBLInteCtrlPackage
{
	LBL_DECLARE_PACKAGECONSTRUCTOR(LBLPackageInteCtrl_WriteVideoSourceContrast, LBLInteCtrlPackage)
public:
	LBLPackageInteCtrl_WriteVideoSourceContrast(quint8 contrast);
	quint16 getOperationResult() const;
	void  setContrast(quint8 contrast) {
		m_contrast = contrast;
	}

protected:
	quint16 CmdNum() const override {
		return quint16(ECommand::EC_Write_VideoSourceContrast);
	}
	QByteArray CmdContent() const override {
		return QByteArray((char *)&m_contrast, 1);
	}
private:
	quint8 m_contrast = 0;
};

class LBL_COMMUNICATENGINE_EXPORT LBLPackageInteCtrl_ReadVideoSourceColortemperature : public LBLInteCtrlPackage
{
	LBL_DECLARE_PACKAGECONSTRUCTOR(LBLPackageInteCtrl_ReadVideoSourceColortemperature, LBLInteCtrlPackage)
public:
	quint8 getColortemperature() const;

protected:
	quint16 CmdNum() const override {
		return quint16(ECommand::EC_Read_VideoSourceColortemperature);
	}
	QByteArray CmdContent() const override {
		return QByteArray();
	}
};

class LBL_COMMUNICATENGINE_EXPORT LBLPackageInteCtrl_WriteVideoSourceColortemperature : public LBLInteCtrlPackage
{
	LBL_DECLARE_PACKAGECONSTRUCTOR(LBLPackageInteCtrl_WriteVideoSourceColortemperature, LBLInteCtrlPackage)
public:
	LBLPackageInteCtrl_WriteVideoSourceColortemperature(quint8 colortemperature);
	quint16 getOperationResult() const;
	void  setColortemperature(quint8 colortemperature) {
		m_colortemperature = colortemperature;
	}

protected:
	quint16 CmdNum() const override {
		return quint16(ECommand::EC_Write_VideoSourceColortemperature);
	}
	QByteArray CmdContent() const override {
		return QByteArray((char *)&m_colortemperature, 1);
	}
private:
	quint8 m_colortemperature = 0;
};

class LBL_COMMUNICATENGINE_EXPORT LBLPackageInteCtrl_ReadVideoSourceBrightness : public LBLInteCtrlPackage
{
	LBL_DECLARE_PACKAGECONSTRUCTOR(LBLPackageInteCtrl_ReadVideoSourceBrightness, LBLInteCtrlPackage)
public:

	quint8 getBrightness() const;

protected:
	quint16 CmdNum() const override {
		return quint16(ECommand::EC_Read_VideoSourceBrightness);
	}
	QByteArray CmdContent() const override {
		return QByteArray();
	}
};

class LBL_COMMUNICATENGINE_EXPORT LBLPackageInteCtrl_WriteVideoSourceBrightness : public LBLInteCtrlPackage
{
	LBL_DECLARE_PACKAGECONSTRUCTOR(LBLPackageInteCtrl_WriteVideoSourceBrightness, LBLInteCtrlPackage)
public:
	LBLPackageInteCtrl_WriteVideoSourceBrightness(quint8 brightness);
	quint16 getOperationResult() const;
	void  setBrightness(quint8 brightness) {
		m_brightness = brightness;
	}

protected:
	quint16 CmdNum() const override {
		return quint16(ECommand::EC_Write_VideoSourceBrightness);
	}
	QByteArray CmdContent() const override {
		return QByteArray((char *)&m_brightness, 1);
	}
private:
	quint8 m_brightness = 0;
};

class LBL_COMMUNICATENGINE_EXPORT LBLPackageInteCtrl_ReadVideoSourceRGain : public LBLInteCtrlPackage
{
	LBL_DECLARE_PACKAGECONSTRUCTOR(LBLPackageInteCtrl_ReadVideoSourceRGain, LBLInteCtrlPackage)
public:
	quint8 getRGain() const;

protected:
	quint16 CmdNum() const override {
		return quint16(ECommand::EC_Read_VideoSourceRGain);
	}
	QByteArray CmdContent() const override {
		return QByteArray();
	}
};

class LBL_COMMUNICATENGINE_EXPORT LBLPackageInteCtrl_WriteVideoSourceRGain : public LBLInteCtrlPackage
{
	LBL_DECLARE_PACKAGECONSTRUCTOR(LBLPackageInteCtrl_WriteVideoSourceRGain, LBLInteCtrlPackage)
public:
	LBLPackageInteCtrl_WriteVideoSourceRGain(quint8 rGain);
	quint16 getOperationResult() const;
	void setRGain(quint8 rGain) {
		m_rGain = rGain;
	}

protected:
	quint16 CmdNum() const override {
		return quint16(ECommand::EC_Write_VideoSourceRGain);
	}
	QByteArray CmdContent() const override {
		return QByteArray((char *)&m_rGain, 1);
	}
private:
	quint8 m_rGain = 0;
};

class LBL_COMMUNICATENGINE_EXPORT LBLPackageInteCtrl_ReadVideoSourceGGain : public LBLInteCtrlPackage
{
	LBL_DECLARE_PACKAGECONSTRUCTOR(LBLPackageInteCtrl_ReadVideoSourceGGain, LBLInteCtrlPackage)
public:
	quint8 getGGain() const;

protected:
	quint16 CmdNum() const override {
		return quint16(ECommand::EC_Read_VideoSourceGGain);
	}
	QByteArray CmdContent() const override {
		return QByteArray();
	}
};

class LBL_COMMUNICATENGINE_EXPORT LBLPackageInteCtrl_WriteVideoSourceGGain : public LBLInteCtrlPackage
{
	LBL_DECLARE_PACKAGECONSTRUCTOR(LBLPackageInteCtrl_WriteVideoSourceGGain, LBLInteCtrlPackage)
public:
	LBLPackageInteCtrl_WriteVideoSourceGGain(quint8 gGain);
	quint16 getOperationResult() const;
	void setGGain(quint8 gGain) {
		m_gGain = gGain;
	}

protected:
	quint16 CmdNum() const override {
		return quint16(ECommand::EC_Write_VideoSourceGGain);
	}
	QByteArray CmdContent() const override {
		return QByteArray((char *)&m_gGain, 1);
	}
private:
	quint8 m_gGain = 0;
};
class LBL_COMMUNICATENGINE_EXPORT LBLPackageInteCtrl_ReadVideoSourceBGain : public LBLInteCtrlPackage
{
	LBL_DECLARE_PACKAGECONSTRUCTOR(LBLPackageInteCtrl_ReadVideoSourceBGain, LBLInteCtrlPackage)
public:
	quint8 getBGain() const;

protected:
	quint16 CmdNum() const override {
		return quint16(ECommand::EC_Read_VideoSourceBGain);
	}
	QByteArray CmdContent() const override {
		return QByteArray();
	}
};

class LBL_COMMUNICATENGINE_EXPORT LBLPackageInteCtrl_WriteVideoSourceBGain : public LBLInteCtrlPackage
{
	LBL_DECLARE_PACKAGECONSTRUCTOR(LBLPackageInteCtrl_WriteVideoSourceBGain, LBLInteCtrlPackage)
public:
	LBLPackageInteCtrl_WriteVideoSourceBGain(quint8 bGain);
	quint16 getOperationResult() const;
	void setBGain(quint8 bGain) {
		m_bGain = bGain;
	}

protected:
	quint16 CmdNum() const override {
		return quint16(ECommand::EC_Write_VideoSourceBGain);
	}
	QByteArray CmdContent() const override {
		return QByteArray((char *)&m_bGain, 1);
	}
private:
	quint8 m_bGain = 0;
};

class LBL_COMMUNICATENGINE_EXPORT LBLPackageInteCtrl_ReadVideoSourceRGBGain : public LBLInteCtrlPackage
{
	LBL_DECLARE_PACKAGECONSTRUCTOR(LBLPackageInteCtrl_ReadVideoSourceRGBGain, LBLInteCtrlPackage)
public:
	quint8 getRGain() const;
	quint8 getGGain() const;
	quint8 getBGain() const;

protected:
	quint16 CmdNum() const override {
		return quint16(ECommand::EC_Read_VideoSourceRGBGain);
	}
	QByteArray CmdContent() const override {
		return QByteArray();
	}
};

class LBL_COMMUNICATENGINE_EXPORT LBLPackageInteCtrl_WriteVideoSourceRGBGain : public LBLInteCtrlPackage
{
	LBL_DECLARE_PACKAGECONSTRUCTOR(LBLPackageInteCtrl_WriteVideoSourceRGBGain, LBLInteCtrlPackage)
public:
	LBLPackageInteCtrl_WriteVideoSourceRGBGain(quint8 rGain, quint8 gGain, quint8 bGain);
	quint16 getOperationResult() const;
	void setRGain(quint8 rGain) {
		m_rGain = rGain;
	}
	void setGGain(quint8 gGain) {
		m_gGain = gGain;
	}
	void setBGain(quint8 bGain) {
		m_bGain = bGain;
	}

protected:
	quint16 CmdNum() const override {
		return quint16(ECommand::EC_Write_VideoSourceRGBGain);
	}
	QByteArray CmdContent() const override;
private:
	quint8 m_rGain = 0;
	quint8 m_gGain = 0;
	quint8 m_bGain = 0;
};

class LBL_COMMUNICATENGINE_EXPORT LBLPackageInteCtrl_ReadVideoSourceResolution : public LBLInteCtrlPackage
{
	LBL_DECLARE_PACKAGECONSTRUCTOR(LBLPackageInteCtrl_ReadVideoSourceResolution, LBLInteCtrlPackage)
public:
	QSize getResolution() const;
	quint8 getRefreshRate() const;

protected:
	quint16 CmdNum() const override {
		return quint16(ECommand::EC_Read_VideoSourceResolution);
	}
	QByteArray CmdContent() const override {
		return QByteArray();
	}
};

class LBL_COMMUNICATENGINE_EXPORT LBLPackageInteCtrl_WriteVideoSourceResolution : public LBLInteCtrlPackage
{
	LBL_DECLARE_PACKAGECONSTRUCTOR(LBLPackageInteCtrl_WriteVideoSourceResolution, LBLInteCtrlPackage)
public:
	LBLPackageInteCtrl_WriteVideoSourceResolution(QSize value, quint8 rate);
	quint16 getOperationResult() const;
	void setResolution(QSize value) {
		m_resolution = value;
	}
	void setRefreshRate(quint8 value) {
		m_refreshRate = value;
	}

protected:
	quint16 CmdNum() const override {
		return quint16(ECommand::EC_Write_VideoSourceResolution);
	}
	QByteArray CmdContent() const override;
private:
	QSize m_resolution;
	quint8 m_refreshRate = 0;
};

class LBL_COMMUNICATENGINE_EXPORT LBLPackageInteCtrl_ReadVideoSourceCombinationInfo : public LBLInteCtrlPackage
{
	LBL_DECLARE_PACKAGECONSTRUCTOR(LBLPackageInteCtrl_ReadVideoSourceCombinationInfo, LBLInteCtrlPackage)
public:
	quint8 getBrightness() const;
	quint8 getColortemperature() const;
	quint8 getRatio() const;
	quint8 getSource() const;
	quint8 getVolume() const;
	quint8 getContrast() const;
	quint8 getSceneMode() const;

protected:
	quint16 CmdNum() const override {
		return quint16(ECommand::EC_Read_VideoSourceCombinationInfo);
	}
	QByteArray CmdContent() const override {
		return QByteArray();
	}
};

class LBL_COMMUNICATENGINE_EXPORT LBLPackageInteCtrl_ReadVideoSourceSceneMode : public LBLInteCtrlPackage
{
	LBL_DECLARE_PACKAGECONSTRUCTOR(LBLPackageInteCtrl_ReadVideoSourceSceneMode, LBLInteCtrlPackage)
public:
	quint8 getSceneMode() const;

protected:
	quint16 CmdNum() const override {
		return quint16(ECommand::EC_Read_VideoSourceSceneMode);
	}
	QByteArray CmdContent() const override {
		return QByteArray();
	}
};

class LBL_COMMUNICATENGINE_EXPORT LBLPackageInteCtrl_WriteVideoSourceSceneMode : public LBLInteCtrlPackage
{
	LBL_DECLARE_PACKAGECONSTRUCTOR(LBLPackageInteCtrl_WriteVideoSourceSceneMode, LBLInteCtrlPackage)
public:
	LBLPackageInteCtrl_WriteVideoSourceSceneMode(quint8 value);
	quint16 getOperationResult() const;
	void setSceneMode(quint8 value) {
		m_sceneMode = value;
	}

protected:
	quint16 CmdNum() const override {
		return quint16(ECommand::EC_Write_VideoSourceSceneMode);
	}
	QByteArray CmdContent() const override {
		return QByteArray((char*)&m_sceneMode, 1);
	}
private:
	quint8 m_sceneMode = 0;
};

class LBL_COMMUNICATENGINE_EXPORT LBLPackageInteCtrl_ReadVideoSourceSplitScreenMode : public LBLInteCtrlPackage
{
	LBL_DECLARE_PACKAGECONSTRUCTOR(LBLPackageInteCtrl_ReadVideoSourceSplitScreenMode, LBLInteCtrlPackage)
public:
	quint8 getSplitScreenMode() const;

protected:
	quint16 CmdNum() const override {
		return quint16(ECommand::EC_Read_VideoSourceSplitScreenMode);
	}
	QByteArray CmdContent() const override {
		return QByteArray();
	}
};

class LBL_COMMUNICATENGINE_EXPORT LBLPackageInteCtrl_WriteVideoSourceSplitScreenMode : public LBLInteCtrlPackage
{
	LBL_DECLARE_PACKAGECONSTRUCTOR(LBLPackageInteCtrl_WriteVideoSourceSplitScreenMode, LBLInteCtrlPackage)
public:
	LBLPackageInteCtrl_WriteVideoSourceSplitScreenMode(quint8 value);
	quint16 getOperationResult() const;
	void setSplitScreenMode(quint8 value) {
		m_splitScreenMode = value;
	}

protected:
	quint16 CmdNum() const override {
		return quint16(ECommand::EC_Write_VideoSourceSplitScreenMode);
	}
	QByteArray CmdContent() const override {
		return QByteArray((char*)&m_splitScreenMode, 1);
	}
private:
	quint8 m_splitScreenMode = 0;
};
