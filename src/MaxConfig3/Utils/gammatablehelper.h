#ifndef GAMMATABLEHELPER_H
#define GAMMATABLEHELPER_H
#include <QVector>

namespace Utils
{
namespace Gamma
{

struct GammaNode;
class GammaTableHelperPrivate;
class GammaTableHelper
{
public:
    enum EColor
    {
        EC_Red=0,
        EC_Green=1,
        EC_Blue=2,
    };

    enum EColorDepth
    {
        ECD_8bit = 8,
        ECD_10bit = 10,
    };

    enum EGrayscaleLevel
    {
        EGL_10Bit=10,
        EGL_11Bit=11,
        EGL_12Bit=12,
        EGL_13Bit=13,
        EGL_14Bit=14,
        EGL_15Bit=15,
        EGL_16Bit=16,
    };

    enum EColorDepthBroaden
    {
        ECDB_16bit = 16,
        ECDB_24bit = 24,
    };

    GammaTableHelper();
    ~GammaTableHelper();

    bool isVaild();

    void initGammaTable(qreal gammaValue, qreal grayScaleSlope,
                        GammaTableHelper::EColorDepth cd, GammaTableHelper::EColorDepthBroaden gs,
                        quint32 grayScaleMin, quint32 grayScaleMax);

    void setGammaValue(qreal gammaValue);
    qreal gammaValue() const;

    void setColorDepthBit(EColorDepth cd);
    EColorDepth colorDepthBit() const;
    quint32 gammaNodeCount() const;

    void setColorDepthBroadenBit(EColorDepthBroaden cdb);
    EColorDepthBroaden colorDepthBroadenBit() const;

    void setGrayscaleLevel(EGrayscaleLevel gl);
    quint8 grayscaleLevel() const;

    void setGrayScaleMin(quint32 mgs);
    quint32 grayScaleMin() const;
    void setGrayScaleMax(quint32 mgs);
    quint32 grayScaleMax() const;

    void setGrayScaleSlope(qreal slope);
    qreal grayScaleSlope() const;

    QVector<GammaNode>& gammaTable() const;
    QVector<GammaNode>& buildGammaTable();

    int rawDataLength(GammaTableHelper::EColorDepth cd) const;
    QByteArray rawGammaData();
    bool setRawGammaData(const QByteArray& rawData);
    bool setRawGammaDataFromOld(const QByteArray& rawData);
    bool setRawGammaDataFromGamdat(const QByteArray& rawData);

private:
    qreal caluValueByIndex(quint32 index);
    qreal calculateGammaValue(int value);
private:
    GammaTableHelperPrivate *d = nullptr;
};

struct GammaNode
{
    GammaNode(){};
    GammaNode(qreal v,\
              GammaTableHelper::EColorDepthBroaden cdb=GammaTableHelper::EColorDepthBroaden::ECDB_24bit,
             GammaTableHelper:: EGrayscaleLevel gl= GammaTableHelper::EGrayscaleLevel::EGL_13Bit){
        convertToByteData(v,cdb,gl);
    }

    bool convertToByteData(qreal value,GammaTableHelper::EColorDepthBroaden cdb=GammaTableHelper::EColorDepthBroaden::ECDB_24bit,
                           GammaTableHelper:: EGrayscaleLevel gl= GammaTableHelper::EGrayscaleLevel::EGL_13Bit){
        int shiftPos=(int)GammaTableHelper::EGrayscaleLevel::EGL_16Bit-(int)gl; //取有效位数
        quint16 integer = quint16(value)<<shiftPos;
        quint16 decimal = quint16((value-integer)*16); //只有4位有效
        r_int=integer;
        g_int=integer;
        b_int=integer;
        if(cdb==GammaTableHelper::EColorDepthBroaden::ECDB_24bit){
            r_dec=decimal<<4;
            g_dec=decimal<<4;
            b_dec=decimal<<4;
        }
        return true;
    }

    quint16 r_int=0;
    quint8  r_dec=0;
    quint16 g_int=0;
    quint8  g_dec=0;
    quint16 b_int=0;
    quint8  b_dec=0;
};

} //namespace Gamma
} //namespace Utils
#endif // GAMMATABLEHELPER_H
