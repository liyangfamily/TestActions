#include "gammatablehelper.h"
#include <math.h>
#include <cfloat>
#include <QDebug>
namespace Utils
{
namespace Gamma
{
class GammaTableHelperPrivate
{
public:
    explicit GammaTableHelperPrivate(GammaTableHelper *q);

    GammaTableHelper *m_q;

    //输入参数
    qreal m_gammaValue = 0U;                       //Gamma 值
    qreal m_grayScaleSlope = 0U;                   //灰度斜率
    GammaTableHelper::EColorDepth m_colorDepthBit; //8bit 10bit 色深bit
    GammaTableHelper::EColorDepthBroaden m_colorDepthBroadenBit;   //16bit 24bit 灰度bit
    GammaTableHelper::EGrayscaleLevel  m_grayScaleLevelBit; //16bit 19bit 有效灰度bit
    quint16 m_grayScaleMin = 0;                    //最小灰度
    quint16 m_grayScaleMax = 0;                    //最大灰度
    //输出参数
    quint16 m_calculateGrayScaleMax=0;
    quint32 m_gammaNodeCount = 0;    //Gamma节点个数
    QVector<GammaNode> m_gammaValueTable;
};

GammaTableHelperPrivate::GammaTableHelperPrivate(GammaTableHelper *q)
    : m_q(q)
{

}

GammaTableHelper::GammaTableHelper()
    : d(new GammaTableHelperPrivate(this))
{
}

GammaTableHelper::~GammaTableHelper()
{
    delete d;
}

bool GammaTableHelper::isVaild()
{
    if (d->m_gammaValue <= DBL_EPSILON){
        qDebug() << ":gammaValue<=0.";
        return false;
    }
    if (d->m_grayScaleSlope <= DBL_EPSILON){
        qDebug() << ":grayScaleSlope<=0.";
        return false;
    }
    if (d->m_gammaNodeCount <= 0){
        qDebug() << ":gammaNodeCount<=0.";
        return false;
    }
    if (d->m_grayScaleMax <= 0){
        qDebug() << ":grayScaleMax<=0.";
        return false;
    }
    return true;
}

void GammaTableHelper::initGammaTable(qreal gammaValue, qreal grayScaleSlope,
                                      GammaTableHelper::EColorDepth cd, GammaTableHelper::EColorDepthBroaden gs,
                                      quint32 grayScaleMin, quint32 grayScaleMax)
{
    setGammaValue(gammaValue);
    setGrayScaleSlope(grayScaleSlope);
    setColorDepthBit(cd);
    setColorDepthBroadenBit(gs);
    setGrayScaleMin(grayScaleMin);
    setGrayScaleMax(grayScaleMax);
}

void GammaTableHelper::setGammaValue(qreal gammaValue)
{
    d->m_gammaValue = gammaValue;
}

qreal GammaTableHelper::gammaValue() const
{
    return d->m_gammaValue;
}

void GammaTableHelper::setColorDepthBit(GammaTableHelper::EColorDepth cd)
{
    d->m_colorDepthBit = cd;
    d->m_gammaNodeCount = pow(2, (quint8)d->m_colorDepthBit);
}

GammaTableHelper::EColorDepth GammaTableHelper::colorDepthBit() const
{
    return d->m_colorDepthBit;
}

quint32 GammaTableHelper::gammaNodeCount() const
{
    return d->m_gammaNodeCount;
}

void GammaTableHelper::setColorDepthBroadenBit(GammaTableHelper::EColorDepthBroaden cdb)
{
    d->m_colorDepthBroadenBit = cdb;
}

GammaTableHelper::EColorDepthBroaden GammaTableHelper::colorDepthBroadenBit() const
{
    return d->m_colorDepthBroadenBit;
}

void GammaTableHelper::setGrayscaleLevel(GammaTableHelper::EGrayscaleLevel gl)
{
    d->m_grayScaleLevelBit= gl;
    //根据灰度等级计算灰度最大值最小值
    int shiftPos=(int)GammaTableHelper::EGrayscaleLevel::EGL_16Bit-(int)d->m_grayScaleLevelBit; //取有效位数
    d->m_grayScaleMax = (0xFFFF<<shiftPos);
}

quint8 GammaTableHelper::grayscaleLevel() const
{
    return d->m_grayScaleLevelBit;
}

void GammaTableHelper::setGrayScaleMin(quint32 mgs)
{
    d->m_grayScaleMin = mgs;
}

quint32 GammaTableHelper::grayScaleMin() const
{
    return d->m_grayScaleMin;
}

void GammaTableHelper::setGrayScaleMax(quint32 mgs)
{
    d->m_grayScaleMax = mgs;
}

quint32 GammaTableHelper::grayScaleMax() const
{
    return d->m_grayScaleMax;
}

void GammaTableHelper::setGrayScaleSlope(qreal slope)
{
    d->m_grayScaleSlope = slope;
}

qreal GammaTableHelper::grayScaleSlope() const
{
    return d->m_grayScaleSlope;
}

QVector<GammaNode>& GammaTableHelper::gammaTable() const
{
    return d->m_gammaValueTable;
}

QVector<GammaNode>& GammaTableHelper::buildGammaTable()
{
    d->m_gammaValueTable.clear();
    d->m_gammaValueTable.resize(d->m_gammaNodeCount);

    d->m_calculateGrayScaleMax=pow(2,(int)d->m_grayScaleLevelBit)-1;
    d->m_calculateGrayScaleMax=d->m_calculateGrayScaleMax>d->m_grayScaleMax?d->m_grayScaleMax:d->m_calculateGrayScaleMax;


    for (int i = 0; i < (int)d->m_gammaNodeCount; ++i)
    {
        qreal nodeValue = caluValueByIndex(i);
        GammaNode node(nodeValue,d->m_colorDepthBroadenBit,d->m_grayScaleLevelBit);
        d->m_gammaValueTable[i]=node;
    }
    return d->m_gammaValueTable;
}

int GammaTableHelper::rawDataLength(GammaTableHelper::EColorDepth cd) const
{
    int filelen=0;
    int nodeCont=0;
    switch(cd)
    {
    case EColorDepth::ECD_8bit:
        nodeCont=pow(2, (quint8)cd);
        break;
    case EColorDepth::ECD_10bit:
        nodeCont=pow(2, (quint8)cd);
        break;
    default:
        break;
    }
    filelen= nodeCont*3*3;
    return filelen;
}

QByteArray GammaTableHelper::rawGammaData()
{
    if((quint32)d->m_gammaValueTable.size()!=d->m_gammaNodeCount){
        return QByteArray();
    }
    int filelen=rawDataLength(d->m_colorDepthBit);
    QByteArray rawData;
    rawData.resize(filelen);
    rawData.fill(0,filelen);
    char * data=rawData.data();
    int pos1=0,pos2=0;
    for(int i=0;i<(int)d->m_gammaNodeCount;++i){
        const GammaNode &node=d->m_gammaValueTable[i];
        memcpy(data+pos1+d->m_gammaNodeCount*0,&node.r_int,2);
        memcpy(data+pos1+d->m_gammaNodeCount*2,&node.g_int,2);
        memcpy(data+pos1+d->m_gammaNodeCount*4,&node.b_int,2);
        pos1+=2;

        memcpy(data+pos2+d->m_gammaNodeCount*6,&node.r_dec,1);
        memcpy(data+pos2+d->m_gammaNodeCount*7,&node.g_dec,1);
        memcpy(data+pos2+d->m_gammaNodeCount*8,&node.b_dec,1);
        pos2+=1;
    }
    return rawData;
}

bool GammaTableHelper::setRawGammaData(const QByteArray &rawData)
{
    int filelen=rawDataLength(d->m_colorDepthBit);
    if(filelen!=rawData.size()){
        qDebug() << "RawGammaData len not match.";
        return false;
    }
    if (rawData.size() == rawDataLength(GammaTableHelper::ECD_8bit)) {
        setColorDepthBit(GammaTableHelper::ECD_8bit);
    }
    if (rawData.size() == rawDataLength(GammaTableHelper::ECD_10bit)) {
        setColorDepthBit(GammaTableHelper::ECD_10bit);
    }

    d->m_gammaValueTable.clear();
    d->m_gammaValueTable.resize(d->m_gammaNodeCount);
    const char * data=rawData.constData();
    int pos1=0,pos2=0;
    for(int i=0;i<(int)d->m_gammaNodeCount;++i){
        GammaNode &node=d->m_gammaValueTable[i];
        memcpy(&node.r_int,data+pos1+d->m_gammaNodeCount*0,2);
        memcpy(&node.g_int,data+pos1+d->m_gammaNodeCount*2,2);
        memcpy(&node.b_int,data+pos1+d->m_gammaNodeCount*4,2);
        pos1+=2;

        memcpy(&node.r_dec,data+pos2+d->m_gammaNodeCount*6,1);
        memcpy(&node.g_dec,data+pos2+d->m_gammaNodeCount*7,1);
        memcpy(&node.b_dec,data+pos2+d->m_gammaNodeCount*8,1);
        if(colorDepthBroadenBit()!=GammaTableHelper::ECDB_24bit){
            if((node.r_dec&node.g_dec&node.b_dec)!=0){
                setColorDepthBroadenBit(GammaTableHelper::ECDB_24bit);
            }
        }
        pos2+=1;
    }
    return true;
}

bool GammaTableHelper::setRawGammaDataFromOld(const QByteArray &rawData)
{
    int rawDataLen=rawDataLength(d->m_colorDepthBit)/3*2;
    if(rawDataLen!=rawData.size()){
        qDebug() << "old RawGammaData len not match.";
        return false;
    }
    if (rawData.size() == rawDataLength(GammaTableHelper::ECD_8bit)/3*2) {
        setColorDepthBit(GammaTableHelper::ECD_8bit);
    }
    if (rawData.size() == rawDataLength(GammaTableHelper::ECD_10bit)/3*2) {
        setColorDepthBit(GammaTableHelper::ECD_10bit);
    }
    setColorDepthBroadenBit(GammaTableHelper::ECDB_16bit);

    d->m_gammaValueTable.clear();
    d->m_gammaValueTable.resize(d->m_gammaNodeCount);
    const char * data=rawData.constData();
    int pos1=0;
    for(int i=0;i<(int)d->m_gammaNodeCount;++i){
        GammaNode &node=d->m_gammaValueTable[i];
        memcpy(&node.r_int,data+pos1+d->m_gammaNodeCount*0,2);
        memcpy(&node.g_int,data+pos1+d->m_gammaNodeCount*2,2);
        memcpy(&node.b_int,data+pos1+d->m_gammaNodeCount*4,2);
        pos1+=2;

        quint8 k = 0;
        memcpy(&node.r_dec,&k,1);
        memcpy(&node.g_dec,&k,1);
        memcpy(&node.b_dec,&k,1);
    }
    return true;
}

bool GammaTableHelper::setRawGammaDataFromGamdat(const QByteArray &rawData)
{
    setColorDepthBit(GammaTableHelper::ECD_8bit);
    setColorDepthBroadenBit(GammaTableHelper::ECDB_16bit);

    d->m_gammaValueTable.clear();
    d->m_gammaValueTable.resize(d->m_gammaNodeCount);
    QString rawDataStr = rawData;
    if(rawDataStr.isEmpty()){
        qDebug() << "Gamdat RawGammaData is Empty.";
        return false;
    }
    QString dataStr = rawDataStr.split('#').last();
    QStringList dataList = dataStr.split(',');

    bool rgbSame = (quint32)dataList.size() == d->m_gammaNodeCount; //只有一张表
    bool rgbDiff = false;
    if(!rgbSame){
        rgbDiff = (quint32)dataList.size() == d->m_gammaNodeCount * 3; //有三张表
    }
    if(!rgbSame&&!rgbDiff){
        qDebug() << "Gamdat RawGammaData Count illegal.";
        return false;
    }
    for(int i=0;i<(int)d->m_gammaNodeCount;++i){
        GammaNode &node=d->m_gammaValueTable[i];
        node.r_int = dataList.at(i).toUShort();
        if(rgbSame){
            node.g_int = dataList.at(i).toUShort();
            node.b_int = dataList.at(i).toUShort();
        }
        if(rgbDiff){
            node.g_int = dataList.at(i+d->m_gammaNodeCount).toUShort();
            node.b_int = dataList.at(i+d->m_gammaNodeCount*2).toUShort();
        }

        quint8 k = 0;
        memcpy(&node.r_dec,&k,1);
        memcpy(&node.g_dec,&k,1);
        memcpy(&node.b_dec,&k,1);
    }
    return true;
}

qreal GammaTableHelper::caluValueByIndex(quint32 index)
{
    if(!isVaild()){
        return 0U;
    }
    quint32 nodeCount = d->m_gammaNodeCount-1;

    qreal initX = ((qreal)index) / (nodeCount); //归一初始值

    if (qFuzzyCompare(initX, 0.0))
    {
        return d->m_grayScaleMin;
    }
    qreal tempValue = 0.0;
    {

        /*
         * 根据这个公式求Gamma曲线和起灰直线的相交的点，小于交点x用直线的值，反之用Gamma的值
         * kx = （x/count）^γ*Gray
         *
         * k:d->m_gray ScaleSlope(直线斜率)
         * count:nodeCount(255级灰度/1024级灰度)
         * γ：m_gammaValue(Gamma值)
         * Gray：(d->m_calculateGrayScaleMax - d->m_grayScaleMin)(Gamma有效范围最大值)
         *
        */
        qreal t0=pow(qreal(1.0/nodeCount),d->m_gammaValue);
        if(qFuzzyCompare(t0, 0.0)){
            return d->m_grayScaleMin;
        }
        qreal t1=t0*(d->m_calculateGrayScaleMax - d->m_grayScaleMin);
        qreal t2= d->m_grayScaleSlope/t1;
        qreal tx=pow(t2,1.0/(d->m_gammaValue-1));

        if (tx>=index){
            tempValue = d->m_grayScaleSlope * index;
        }
        else{
            tempValue = pow(initX, d->m_gammaValue);
            tempValue *= d->m_calculateGrayScaleMax - d->m_grayScaleMin; //乘以最大值
            tempValue+=0.5;
        }
    }

    tempValue += d->m_grayScaleMin;

    return tempValue;
}

qreal GammaTableHelper::calculateGammaValue(int value)
{
    if(d->m_colorDepthBit<=0||d->m_grayScaleMin<=0||d->m_grayScaleMax<d->m_grayScaleMin){
        return 0U;
    }
    //s=cr^γ(c为灰度缩放系数，通常取1；γ为gamma因子大小)
    qreal r = (qreal)value / (pow(2,int(d->m_colorDepthBit))-1); //归一
    qreal s = pow(r, d->m_gammaValue); //计算gamma曲线y值
    qreal z = s * (d->m_grayScaleMax - d->m_grayScaleMin); //乘以最大值
    z += d->m_grayScaleMin;
    return z;
}
}
}
