#pragma once

#include <QObject>
#include <QAction>
#include <QMenu>
#include <QMap>
#include <QList>
#include <QPair>
#include <QFutureWatcher>


class S6PPixelData
{
    /*********************************************************************************************************
    校正数据原始数据：(数据位为内存排列顺序）
    -------------------------------------------------------------------------------------------------------------------------
    |  2Byte R  |  2Byte R_g  |  2Byte R_b  |  2Byte G_r  |  2Byte G  |  2Byte G_b  |  2Byte B_r  |  2Byte B_g  |  2Byte B  |
    -------------------------------------------------------------------------------------------------------------------------
    6张图像素点转换,每个像素数据构成:（数据位为内存排列顺序）
    -------------------------------------------------------------------------------------
    |  5Byte Header  |  1Byte index  |  4Byte R_Data  |  4Byte G_Data  |  4Byte B_Data  |
    -------------------------------------------------------------------------------------

    R:
    0bit                                     ->                                       48bit
    ---------------------------------------------------------------------------------------
    |  R L_Byte  |  R H_Byte  |  R_g L_Byte  |  R_g H_Byte  |  R_b L_Byte  |  R_b H_Byte  |
    ---------------------------------------------------------------------------------------

    G:
    0bit                                     ->                                       48bit
    ---------------------------------------------------------------------------------------
    |  G_r L_Byte  |  G_r H_Byte  |  G L_Byte  |  G H_Byte  |  G_b L_Byte  |  G_b H_Byte  |
    ---------------------------------------------------------------------------------------

    B:
    0bit                                     ->                                       48bit
    ---------------------------------------------------------------------------------------
    |  B_r L_Byte  |  B_r H_Byte  |  B_g L_Byte  |  B_g H_Byte  |  B L_Byte  |  B H_Byte  |
    ---------------------------------------------------------------------------------------

    以R为例,转换前：
    0bit                                     ->                                       48bit
    ---------------------------------------------------------------------------------------
    |  R L_Byte  |  R H_Byte  |  R_g L_Byte  |  R_g H_Byte  |  R_b L_Byte  |  R_b H_Byte  |
    ---------------------------------------------------------------------------------------
                                     ||
                                     \/
                主色去掉最高1bit和低3bit，辅色去掉最高和最低3bit
    转换后：
    0bit               ->               32bit
    -----------------------------------------
    |  12bit R  |  10bit R_g  |  10bit R_b  | ==> 32bit ==> 4Byte R_Data
    -----------------------------------------
    *********************************************************************************************************/
public:
    //用于图片生成6P校正数据图片，pixel代表每个像素点主色值，辅色值为0
    S6PPixelData(const QPoint& pt, const QRgb& pixel, const QSize& moduleSize);
    //用于校正文件生成6P校正数据图片，pixel代表每个像素点的主色值和辅色值，共18Byte
    S6PPixelData(const QPoint& pt, const char* pixel, const int& len, const QSize& moduleSize);
    virtual bool build(char* data);
protected:
    char* buildHeader(char* d);
    char* buildFlage(char* d);
    char* buildR(char* d);
    char* buildG(char* d);
    char* buildB(char* d);
protected:
    static quint16 ucharEqualRatioConvTouShort(quint8);
    static quint32 pixelColorConvert_R(const quint16& r, const quint16& r_g, const quint16& r_b);
    static quint32 pixelColorConvert_G(const quint16& g_r, const quint16& g, const quint16& g_b);
    static quint32 pixelColorConvert_B(const quint16& b_r, const quint16& b_g, const quint16& b);
private:
    quint16 m_r = 0, m_rg = 0, m_rb = 0;
    quint16 m_gr = 0, m_g = 0, m_gb = 0;
    quint16 m_br = 0, m_bg = 0, m_b = 0;
    QPoint m_pt;
    QSize m_moduleSize;
};

class S8PPixelData : public S6PPixelData
{
    /*********************************************************************************************************
    校正数据原始数据：(数据位为内存排列顺序）
    -------------------------------------------------------------------------------------------------------------------------
    |  2Byte R  |  2Byte R_g  |  2Byte R_b  |  2Byte G_r  |  2Byte G  |  2Byte G_b  |  2Byte B_r  |  2Byte B_g  |  2Byte B  |
    -------------------------------------------------------------------------------------------------------------------------
    8张图像素点转换,每个像素数据构成:（数据位为内存排列顺序）
    ----------------------------------------------------
    |  4Byte R_Data  |  4Byte G_Data  |  4Byte B_Data  |
    ----------------------------------------------------

    校正数据原始排列详情：
    R:
    0bit                                     ->                                       48bit
    ---------------------------------------------------------------------------------------
    |  R L_Byte  |  R H_Byte  |  R_g L_Byte  |  R_g H_Byte  |  R_b L_Byte  |  R_b H_Byte  |
    ---------------------------------------------------------------------------------------

    G:
    0bit                                     ->                                       48bit
    ---------------------------------------------------------------------------------------
    |  G_r L_Byte  |  G_r H_Byte  |  G L_Byte  |  G H_Byte  |  G_b L_Byte  |  G_b H_Byte  |
    ---------------------------------------------------------------------------------------

    B:
    0bit                                     ->                                       48bit
    ---------------------------------------------------------------------------------------
    |  B_r L_Byte  |  B_r H_Byte  |  B_g L_Byte  |  B_g H_Byte  |  B L_Byte  |  B H_Byte  |
    ---------------------------------------------------------------------------------------

    以R为例,转换前：
    0bit                                     ->                                       48bit
    ---------------------------------------------------------------------------------------
    |  R L_Byte  |  R H_Byte  |  R_g L_Byte  |  R_g H_Byte  |  R_b L_Byte  |  R_b H_Byte  |
    ---------------------------------------------------------------------------------------
                                     ||
                                     \/
                主色去掉最高1bit和低3bit，辅色去掉最高和最低3bit
    转换后：
    0bit               ->               32bit
    -----------------------------------------
    |  12bit R  |  10bit R_g  |  10bit R_b  | ==> 32bit ==> 4Byte R_Data
    -----------------------------------------
    *********************************************************************************************************/
public:
    //用于图片生成6P校正数据图片，pixel代表每个像素点主色值，辅色值为0
    S8PPixelData(const QPoint& pt, const QRgb& pixel, const QSize& moduleSize);
    //用于校正文件生成6P校正数据图片，pixel代表每个像素点的主色值和辅色值，共18Byte
    S8PPixelData(const QPoint& pt, const char* pixel, const int& len, const QSize& moduleSize);
    bool build(char* data) override;
};

class TestScreenHelper;
class CorrectDataHelper : public QObject
{
    Q_OBJECT

public:
    enum CorrectDataType {
        CDT_6P, //6图校正数据
        CDT_8P, //8图校正数据
        CDT_2P_Lowgray, //2图低灰校正数据
        CDT_2P_Gap, //2图修缝数据
    };
    CorrectDataHelper(QObject *parent = nullptr);
    ~CorrectDataHelper();
    void setPaintRect(QRect rect) {
        m_paintRect = rect;

//                m_paintRect.setWidth(3840);
//                m_paintRect.setHeight(2160);
    }
    QRect paintRect() const{
        return m_paintRect;
    }
    void setPort(int port){
        m_port=port;
    }
    int port() const{
        return m_port;
    }
    void setModuleIndex(int index){
        m_moduleIndex=index;
    }
    int moduleIndex() const{
        return m_moduleIndex;
    }

    static void setCorrectDataType(CorrectDataType type) {
        m_correctDataType = type;
    }

    static CorrectDataType correctDataType() {
        return m_correctDataType;
    }

    QString selectFilter(){
        return m_selectFilter;
    }
    QMenu* correctMenu() {
        return &m_itemCorrectMenu;
    }
    QPair<CorrectDataHelper*, QString> correctFileInfo() {
        return qMakePair(this, m_correctFilePath);
    }

    bool isLoaded(){
        return !m_correctFilePath.isEmpty();
    }

    static QSharedPointer<QByteArray> imageToCorrectData(const QImage& img, const QRect& rect, const CorrectDataType type);
    static QSharedPointer<QByteArray> fileToCorrectData(const QByteArray& fileData, const QRect& rect, const CorrectDataType type);

    static QList<QImage> correctDataToImageList(const QByteArray *data, const QRect& rect, const CorrectDataType type);

    static QPair<CorrectDataHelper*, QSharedPointer<QByteArray>> concurrentCreatImage(const QPair<CorrectDataHelper*, QString>& pair);
public slots:
    bool addCorrectFile();
    bool deleteCorrectFile();
    bool sendCorrectData();
    bool saveCorrectData();
    bool eraseCorrectData();
    bool reloadCorrectData();
private slots:
    void correctDataCalculateFinished();
private:
    static QSharedPointer<QByteArray> imageTo6PData(const QImage& img, const QRect& rect);			//生成六张图数据
    static QSharedPointer<QByteArray> fileTo6PData(const QByteArray& fileData, const QRect& rect);			//生成六张图数据
    static QList<QImage> convert6PDataToImageList(const QByteArray *data, const QRect& rect, const CorrectDataType type);

    static QSharedPointer<QByteArray> imageTo8PData(const QImage& img, const QRect& rect);		//生成四张图数据， 另四张图为固定头
    static QSharedPointer<QByteArray> fileTo8PData(const QByteArray& fileData, const QRect& rect);		//生成四张图数据， 另四张图为固定头
    static QImage creat8PHeaderImage(const int index, const QRect& rect); //固定头
    static QList<QImage> convert8PDataToImageList(const QByteArray *data, const QRect& rect, const CorrectDataType type);

    static QByteArray imageTo2PLowGrayData(const QImage& img, const QRect& rect);	//生成2张图低灰数据
    static QByteArray imageTo2PGapData(const QImage& img, const QRect& rect);		//生成2张图修缝文件
private:
    QMenu m_itemCorrectMenu;

    QAction *m_addCorrectFileAction;
    QAction *m_deleteCorrectFileAction;
    QAction *m_sendCorrectDataAction;
    QAction *m_saveCorrectDataAction;
    QAction *m_eraseCorrectDataAction;
    QAction *m_reloadCorrectDataAction;

    static CorrectDataType m_correctDataType;
    QString m_selectFilter;
    QString m_correctFilePath;
    int m_port = 0xFF;
    int m_moduleIndex = 0xFF;
    QRect m_paintRect;

    QFutureWatcher<QPair<CorrectDataHelper*, QSharedPointer<QByteArray>>> m_correctWatcher;
    TestScreenHelper* m_testScrrenHelper;
};
