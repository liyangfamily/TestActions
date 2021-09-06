#include "correctdatahelper.h"
#include <LAPIControl>
#include <app.h>
#include "Core/icore.h"
#include "Utils/utilsfilefilter.h"
#include "testscreenhelper.h"

#include <QFileDialog>
#include <QApplication>
#include <QtConcurrent/QtConcurrentMap>
#include <QSharedPointer>


S6PPixelData::S6PPixelData(const QPoint& pt, const QRgb& pixel, const QSize& moduleSize)
	:m_pt(pt),
	m_moduleSize(moduleSize)
{
	m_r = ucharEqualRatioConvTouShort(qRed(pixel));
	m_g = ucharEqualRatioConvTouShort(qGreen(pixel));
	m_b = ucharEqualRatioConvTouShort(qBlue(pixel));
}

S6PPixelData::S6PPixelData(const QPoint& pt, const char* pixel, const int& len, const QSize& moduleSize)
	:m_pt(pt),
	m_moduleSize(moduleSize)
{
	if (len >= 18) {
		int pos = 0;
		memcpy_s(&m_r, 2, pixel + pos, 2);
		pos += 2;
		memcpy_s(&m_rg, 2, pixel + pos, 2);
		pos += 2;
		memcpy_s(&m_rb, 2, pixel + pos, 2);
        pos += 2;

		memcpy_s(&m_gr, 2, pixel + pos, 2);
		pos += 2;
		memcpy_s(&m_g, 2, pixel + pos, 2);
		pos += 2;
		memcpy_s(&m_gb, 2, pixel + pos, 2);
        pos += 2;

		memcpy_s(&m_br, 2, pixel + pos, 2);
		pos += 2;
		memcpy_s(&m_bg, 2, pixel + pos, 2);
		pos += 2;
		memcpy_s(&m_b, 2, pixel + pos, 2);
	}
	else {
		qDebug() << __FUNCTION__ << ": ByteArray is too short, less than 18Byte, this class will not work.";
	}
}


bool S6PPixelData::build(char* data)
{
    data=buildHeader(data);
    if (!data) {
		return false;
	}
    data=buildFlage(data);
    if (!data) {
        return false;
    }
    data=buildR(data);
    if (!data) {
        return false;
    }
    data=buildG(data);
    if (!data) {
        return false;
    }
    data=buildB(data);
    if (!data) {
        return false;
    }
	return true;
}

char* S6PPixelData::buildHeader(char* d)
{
    *d++ = char(0x55);
    *d++ = char(0x00);
    *d++ = char(0xAA);
    *d++ = char(0x00);
    *d++ = char(0xFF);
    return d;
}

char* S6PPixelData::buildFlage(char* d)
{
	int totalPixel = m_moduleSize.width()*m_moduleSize.height();
	if (totalPixel <= 0) {
        return nullptr;
	}
	//计算当前点在第几张图片
	char index = (m_pt.x() + m_pt.y()*m_moduleSize.width()) / (totalPixel / 6) + 1;
    *d++ = index;
    return d;
}

char* S6PPixelData::buildR(char* d)
{
	quint32 value = pixelColorConvert_R(m_r, m_rg, m_rg);
    memcpy_s(d, 4, &value, 4);
    d+=4;
    return d;
}

char* S6PPixelData::buildG(char* d)
{
	quint32 value = pixelColorConvert_G(m_gr, m_g, m_gb);
    memcpy_s(d, 4, &value, 4);
    d+=4;
    return d;
}

char* S6PPixelData::buildB(char* d)
{
	quint32 value = pixelColorConvert_B(m_br, m_bg, m_b);
    memcpy_s(d, 4, &value, 4);
    d+=4;
    return d;
}

quint16 S6PPixelData::ucharEqualRatioConvTouShort(quint8 value)
{
	return USHRT_MAX * value / UCHAR_MAX;
}

quint32 S6PPixelData::pixelColorConvert_R(const quint16& r, const quint16& r_g, const quint16& r_b)
{
	quint32 _r = (r & 0x7FF8) >> 3; //去掉最高1bit和低3bit,右移3bit得到新值，数据所占位[0-11]
	quint32 _rg = ((r_g & 0x1FF8) >> 3) << 12; //去掉高3bit和低3bit,右移3bit得到新值，再左移12bit，数据所占位[12-21]
	quint32 _rb = ((r_b & 0x1FF8) >> 3) << 22; //去掉高3bit和低3bit,右移3bit得到新值，再左移22bit，数据所占位[22-31]
	return (_r | _rg | _rb); //最后按位或得到最终值
}

quint32 S6PPixelData::pixelColorConvert_G(const quint16& g_r, const quint16& g, const quint16& g_b)
{
	quint32 _gr = (g_r & 0x1FF8) >> 3; //去掉高3bit和低3bit,右移3bit得到新值，数据所占位[0-9]
	quint32 _g = ((g & 0x7FF8) >> 3) << 10; //去掉高1bit和低3bit,右移3bit得到新值，再左移10bit，数据所占位[10-21]
	quint32 _gb = ((g_b & 0x1FF8) >> 3) << 22; //去掉高3bit和低3bit,右移3bit得到新值，再左移22bit，数据所占位[22-31]
	return (_gr | _g | _gb); //最后按位或得到最终值
}

quint32 S6PPixelData::pixelColorConvert_B(const quint16& b_r, const quint16& b_g, const quint16& b)
{
	quint32 _br = (b_r & 0x1FF8) >> 3; //去掉高3bit和低3bit,右移3bit得到新值，数据所占位[0-9]
	quint32 _bg = ((b_g & 0x1FF8) >> 3) << 10; //去掉高3bit和低3bit,右移3bit得到新值，再左移10bit，数据所占位[10-19]
	quint32 _b = ((b & 0x7FF8) >> 3) << 20; //去掉高1bit和低3bit,右移3bit得到新值，再左移20bit，数据所占位[20-31]
	return (_br | _bg | _b); //最后按位或得到最终值
}


/*********************************************************************************************************
**
*********************************************************************************************************/


S8PPixelData::S8PPixelData(const QPoint &pt, const QRgb &pixel, const QSize &moduleSize)
    :S6PPixelData(pt,pixel,moduleSize)
{

}

S8PPixelData::S8PPixelData(const QPoint &pt, const char *pixel, const int &len, const QSize &moduleSize)
    :S6PPixelData(pt,pixel,len,moduleSize)
{
}

bool S8PPixelData::build(char *data)
{
    data=buildR(data);
    if (!data) {
        return false;
    }
    data=buildG(data);
    if (!data) {
        return false;
    }
    data=buildB(data);
    if (!data) {
        return false;
    }
    return true;
}


/*********************************************************************************************************
**                                                                     
*********************************************************************************************************/
CorrectDataHelper::CorrectDataType CorrectDataHelper::m_correctDataType=CorrectDataHelper::CDT_8P;

CorrectDataHelper::CorrectDataHelper(QObject *parent)
    : QObject(parent)
{
    m_testScrrenHelper = new TestScreenHelper();

	m_addCorrectFileAction = new QAction(QIcon(":/Defaluat/Resources/Default/Menu/load.png"), tr("Load Correct File"), this);
	connect(m_addCorrectFileAction, &QAction::triggered, this, &CorrectDataHelper::addCorrectFile);
    m_deleteCorrectFileAction = new QAction(QIcon(":/Defaluat/Resources/Default/Menu/delete.png"), tr("Delete Correct File"), this);
	connect(m_deleteCorrectFileAction, &QAction::triggered, this, &CorrectDataHelper::deleteCorrectFile);
	m_sendCorrectDataAction = new QAction(QIcon(":/Defaluat/Resources/Default/Menu/send.png"), tr("Send Correct Data"), this);
	connect(m_sendCorrectDataAction, &QAction::triggered, this, &CorrectDataHelper::sendCorrectData);
	m_saveCorrectDataAction = new QAction(QIcon(":/Defaluat/Resources/Default/Menu/save.png"), tr("Save Correct Data"), this);
	connect(m_saveCorrectDataAction, &QAction::triggered, this, &CorrectDataHelper::saveCorrectData);
	m_eraseCorrectDataAction = new QAction(QIcon(":/Defaluat/Resources/Default/Menu/erase.png"), tr("Erase Correct Data"), this);
	connect(m_eraseCorrectDataAction, &QAction::triggered, this, &CorrectDataHelper::eraseCorrectData);
	m_reloadCorrectDataAction = new QAction(QIcon(":/Defaluat/Resources/Default/Menu/reloade.png"), tr("Reload Correct File"), this);
	connect(m_reloadCorrectDataAction, &QAction::triggered, this, &CorrectDataHelper::reloadCorrectData);

	m_itemCorrectMenu.addAction(m_addCorrectFileAction);
	m_itemCorrectMenu.addAction(m_deleteCorrectFileAction);
	m_itemCorrectMenu.addAction(m_sendCorrectDataAction);
	m_itemCorrectMenu.addAction(m_saveCorrectDataAction);
	m_itemCorrectMenu.addAction(m_eraseCorrectDataAction);
	m_itemCorrectMenu.addAction(m_reloadCorrectDataAction);

    m_correctWatcher.blockSignals(true);
    connect(&m_correctWatcher, &QFutureWatcher<QPair<CorrectDataHelper*, QByteArray>>::finished,
        this, &CorrectDataHelper::correctDataCalculateFinished);

}

CorrectDataHelper::~CorrectDataHelper()
{
    if (m_testScrrenHelper) {
        delete m_testScrrenHelper;
        m_testScrrenHelper = nullptr;
    }
}

QSharedPointer<QByteArray> CorrectDataHelper::imageToCorrectData(const QImage & img, const QRect& rect, const CorrectDataType type)
{
	switch (type)
	{
	case CorrectDataHelper::CDT_6P:
		return imageTo6PData(img, rect);
	case CorrectDataHelper::CDT_8P:
        return imageTo8PData(img, rect);
//	case CorrectDataHelper::CDT_2P_Lowgray:
//		return imageTo2PLowGrayData(img, rect);
//	case CorrectDataHelper::CDT_2P_Gap:
//		return imageTo2PGapData(img, rect);
	default:
		break;
	}
    return nullptr;
}

QSharedPointer<QByteArray> CorrectDataHelper::fileToCorrectData(const QByteArray& fileData, const QRect& rect, const CorrectDataType type)
{
	switch (type)
	{
	case CorrectDataHelper::CDT_6P:
		return fileTo6PData(fileData, rect);
	case CorrectDataHelper::CDT_8P:
        return fileTo8PData(fileData, rect);
	case CorrectDataHelper::CDT_2P_Lowgray:
		break;
	case CorrectDataHelper::CDT_2P_Gap:
		break;
	default:
		break;
	}
    return nullptr;
}

QList<QImage> CorrectDataHelper::correctDataToImageList(const QByteArray *data, const QRect & rect, const CorrectDataType type)
{
	switch (type)
	{
	case CorrectDataHelper::CDT_6P:
		return convert6PDataToImageList(data, rect, type);
	case CorrectDataHelper::CDT_8P:
        return convert8PDataToImageList(data, rect, type);
	case CorrectDataHelper::CDT_2P_Lowgray:
		break;
	case CorrectDataHelper::CDT_2P_Gap:
		break;
	default:
		break;
	}
	return QList<QImage>();
}

QPair<CorrectDataHelper*, QSharedPointer<QByteArray>> CorrectDataHelper::concurrentCreatImage(const QPair<CorrectDataHelper*, QString>& pair)
{
    qDebug() << pair.first << pair.second;
    QSharedPointer<QByteArray> data;
    qDebug() << QTime::currentTime();
    if (pair.first->selectFilter() == Utils::FileFilter::PICTURECORRECT_FILTER) {
        QImage image;
        if (!image.load(pair.second)) {
            if(image.isNull()){
                QFile file(pair.second);
                if (!file.open(QIODevice::ReadOnly)) {
                    qDebug() << __FUNCTION__ << ": Correct File Open Failed.";
                    return qMakePair(pair.first, data);
                }
                QByteArray data = file.readAll();
                image = QImage::fromData(data);
            }
            qDebug() << __FUNCTION__ << ": Correct Image Open Failed.";
            return qMakePair(pair.first, data);
        }
        image = image.scaled(pair.first->paintRect().size());
        data = imageToCorrectData(image, pair.first->paintRect(), pair.first->correctDataType());
    }
    else if (pair.first->selectFilter() == Utils::FileFilter::CORRECT_FILTER) {
        QFile file(pair.second);
        if (!file.open(QIODevice::ReadOnly)) {
            qDebug() << __FUNCTION__ << ": Correct File Open Failed.";
            return qMakePair(pair.first, data);
        }
        QByteArray fileData = file.readAll();
        file.close();
        data = fileToCorrectData(fileData, pair.first->paintRect(), pair.first->correctDataType());
    }
    qDebug() << QTime::currentTime();
    return qMakePair(pair.first, data);
}

bool CorrectDataHelper::addCorrectFile()
{
	QString imagePath = QFileDialog::getOpenFileName(nullptr,
		QApplication::tr("Open Correction File"),
		App::lastOpenPath,
		QString("%1;;%2").arg(Utils::FileFilter::CORRECT_FILTER).arg(Utils::FileFilter::PICTURECORRECT_FILTER),
		&m_selectFilter);
	if (imagePath.isEmpty())
	{
		return false;
	}
	App::lastOpenPath = imagePath;
	App::writeConfig();

	m_correctFilePath = imagePath;
	return true;
}

bool CorrectDataHelper::deleteCorrectFile()
{
    m_correctFilePath.clear();
    return true;
}

bool CorrectDataHelper::sendCorrectData()
{
    if(m_correctFilePath.isEmpty()){
        Core::ICore::instance()->showMessage(tr("Correct File Path is Empty."));
        return false;
    }
    QList<QPair<CorrectDataHelper*, QString>> filelist;
    filelist.append(this->correctFileInfo());
    QFuture<QPair<CorrectDataHelper*, QSharedPointer<QByteArray>>> future =
            QtConcurrent::mapped(filelist, CorrectDataHelper::concurrentCreatImage);
    m_correctWatcher.blockSignals(false);
    m_correctWatcher.setFuture(future);
    return true;
}

bool CorrectDataHelper::saveCorrectData()
{
    LAPI::EResult ret = LAPI::WriteCalibrationDataSave(m_port,m_moduleIndex);
    Core::ICore::showMessageLAPIResult(ret);
    return true;
}

bool CorrectDataHelper::eraseCorrectData()
{
    LAPI::EResult ret = LAPI::WriteCalibrationDataErase(m_port,m_moduleIndex);
    Core::ICore::showMessageLAPIResult(ret);
    return true;
}

bool CorrectDataHelper::reloadCorrectData()
{
    LAPI::EResult ret = LAPI::WriteCalibrationDataReload(m_port,m_moduleIndex);
    Core::ICore::showMessageLAPIResult(ret);
    return true;
}

void CorrectDataHelper::correctDataCalculateFinished()
{
    m_correctWatcher.blockSignals(true);
    QList<QPair<CorrectDataHelper*, QSharedPointer<QByteArray>>> ret = m_correctWatcher.future().results();
    m_correctWatcher.setFuture(QFuture<QPair<CorrectDataHelper*, QSharedPointer<QByteArray>>>());
    m_testScrrenHelper->showImageList(ret, this->correctDataType());
}

QSharedPointer<QByteArray> CorrectDataHelper::imageTo6PData(const QImage & img, const QRect& rect)
{
	if (img.size() != rect.size()) {
		qDebug() << __FUNCTION__ << ": The mage size does not match the region.";
        return nullptr;
	}
	const int countPerPixel = 18;	//单点占用字节长度
	int tileByteCount = countPerPixel * rect.width() * rect.height();
    QSharedPointer<QByteArray> dataArray(new QByteArray(tileByteCount, 0));
	for (int h = 0; h < rect.height(); ++h) {
		for (int w = 0; w < rect.width(); ++w) {
			QRgb rgb = img.pixel(w, h);
			int startPos = (h*rect.width() + w)*countPerPixel;
			S6PPixelData pixelData(QPoint(w, h), rgb, rect.size());
            pixelData.build(dataArray->data() + startPos);
		}
	}
	return dataArray;
}

QSharedPointer<QByteArray> CorrectDataHelper::fileTo6PData(const QByteArray& fileData, const QRect& rect)
{
	const int originalDataBlockLen = 22;
	const int effectiveDataBlockLen = 18;
	if (fileData.size() != rect.width()*rect.height() * originalDataBlockLen) {
		qDebug() << __FUNCTION__ << ": The file length does not match the region calculate length.";
        return nullptr;
	}
    int pos = 0;
    int tileByteCount = effectiveDataBlockLen * rect.width() * rect.height();
    QSharedPointer<QByteArray> dataArray(new QByteArray(tileByteCount, 0));
	for (int h = 0; h < rect.height(); ++h){
		for (int w = 0; w < rect.width(); ++w){
			pos += 4;
			int startPos = (h*rect.width() + w)*effectiveDataBlockLen;
			S6PPixelData pixelData(QPoint(w, h), fileData.constData() + pos, effectiveDataBlockLen, rect.size());
            pixelData.build(dataArray->data() + startPos);
			pos += effectiveDataBlockLen;
		}
	}
	return dataArray;
}

QList<QImage> CorrectDataHelper::convert6PDataToImageList(const QByteArray * data, const QRect & rect, const CorrectDataType type)
{
    if (type != CorrectDataType::CDT_6P) {
        qDebug() << __FUNCTION__ << " :CorrectData Type Mismatch.";
        return QList<QImage>();
    }
    if (nullptr == data) {
        qDebug() << __FUNCTION__ << " :Image Data is NULL.";
        return QList<QImage>();
    }
	int imageCount = 6;
    const char * d = data->constData();
	int w = rect.width();
	int h = rect.height();

    if (data->size() != 3 * imageCount*w*h) {
		return QList<QImage>();
	}
	QList<QImage> list;
	int pos = 0;
	for (int i = 0; i < imageCount; ++i) {
		QImage image = QImage((uchar*)(d + pos), w, h, QImage::Format_RGB888);
		pos += 3 * w*h;
		list.append(image);
	}
	if (list.size() != imageCount) {
		return QList<QImage>();
	}
	return list;
}

QSharedPointer<QByteArray> CorrectDataHelper::imageTo8PData(const QImage & img, const QRect& rect)
{
    if (img.size() != rect.size()) {
        qDebug() << __FUNCTION__ << ": The mage size does not match the region.";
         return nullptr;
    }
    const int countPerPixel = 12;	//单点占用字节长度
    const int effectivePicCount = 4; //有效图片数量
    const int offset = countPerPixel / effectivePicCount;
    int tileByteCount = countPerPixel * rect.width() * rect.height();

    QSharedPointer<QByteArray> dataArray(new QByteArray(tileByteCount, 0));
    //按照图片格式生成4张图
    char cache[countPerPixel]{ 0 };
    for (int h = 0; h < rect.height(); ++h) {
        for (int w = 0; w < rect.width(); ++w) {
            int insideBlockStartPos = (h*rect.width() + w)*offset;
            QRgb rgb = img.pixel(w, h);
            S8PPixelData pixelData(QPoint(w, h), rgb, rect.size());
            pixelData.build(cache);
            //每个像素12字节，分布在4张图片中
            for (int i = 0; i < effectivePicCount; ++i) {
                int blockOffset = (i*(tileByteCount / 4));
                int pos = insideBlockStartPos + blockOffset;
                memcpy_s(dataArray->data() + pos, offset, cache + (i*offset), offset);
            }
        }
    }
    return dataArray;
}

QSharedPointer<QByteArray> CorrectDataHelper::fileTo8PData(const QByteArray& fileData, const QRect& rect)
{
    const int originalDataBlockLen = 22;
    const int effectiveDataBlockLen = 18;
    if (fileData.size() != rect.width()*rect.height() * originalDataBlockLen) {
        qDebug() << __FUNCTION__ << ": The file length does not match the region calculate length.";
        return nullptr;
    }
    int filePos = 0;
    const int countPerPixel = 12;	//单点占用字节长度
    const int effectivePicCount=4; //有效图片数量
    const int offset=countPerPixel/effectivePicCount;
    int tileByteCount = countPerPixel * rect.width() * rect.height();

    QSharedPointer<QByteArray> dataArray(new QByteArray(tileByteCount, 0));
    //按照图片格式生成4张图
    char cache[countPerPixel]{ 0 };
    for (int h = 0; h < rect.height(); ++h) {
        for (int w = 0; w < rect.width(); ++w) {
            filePos += 4;
            int insideBlockStartPos = (h*rect.width() + w)*offset;
            S8PPixelData pixelData(QPoint(w, h), fileData.constData() + filePos, effectiveDataBlockLen, rect.size());
            memset(cache,0,countPerPixel);
            pixelData.build(cache);
            //每个像素12字节，分布在4张图片中
            for (int i = 0; i < effectivePicCount; ++i) {
                int blockOffset = (i*(tileByteCount / 4));
                int pos = insideBlockStartPos + blockOffset;
                memcpy_s(dataArray->data() + pos, offset, cache + (i*offset), offset);
            }
            filePos += effectiveDataBlockLen;
        }
    }
    return dataArray;
}

QImage CorrectDataHelper::creat8PHeaderImage(const int index, const QRect& rect)
{
    //头数据
    const int ciHeaderCount = 4;	//头数据数据数量
    const int ciHeaderLength = 15; //头数据长度
    const quint8 ciEightHeader[ciHeaderCount][ciHeaderLength] =
    {
        {0x55, 0x55, 0x55, 0xAA, 0xAA, 0xAA, 0x00, 0x00, 0x00, 0xCC, 0xCC, 0xCC, 0xA0, 0xC5, 0x5A},
        {0x55, 0x55, 0x55, 0xAA, 0xAA, 0xAA, 0x00, 0x00, 0x00, 0xCC, 0xCC, 0xCC, 0xA1, 0xC5, 0x5A},
        {0x55, 0x55, 0x55, 0xAA, 0xAA, 0xAA, 0x00, 0x00, 0x00, 0xCC, 0xCC, 0xCC, 0xA2, 0xC5, 0x5A},
        {0x55, 0x55, 0x55, 0xAA, 0xAA, 0xAA, 0x00, 0x00, 0x00, 0xCC, 0xCC, 0xCC, 0xA3, 0xC5, 0x5A},
    };
    const int countPerPixel = 12;	//单点占用字节长度
    const int effectivePicCount=4; //有效图片数量
    int tileByteCount = (countPerPixel / effectivePicCount) * rect.width() * rect.height();
    QImage headerImg = QImage(rect.width(), rect.height(), QImage::Format_RGB888);
    for (int i = 0; i < tileByteCount / ciHeaderLength; ++i) {
        memcpy_s(headerImg.bits() + (i*ciHeaderLength), ciHeaderLength, ciEightHeader[index], ciHeaderLength);
    }
    return headerImg;
}

QList<QImage> CorrectDataHelper::convert8PDataToImageList(const QByteArray *data, const QRect &rect, const CorrectDataHelper::CorrectDataType type)
{
    if (type != CorrectDataType::CDT_8P) {
        qDebug() << __FUNCTION__ << " :CorrectData Type Mismatch.";
        return QList<QImage>();
    }
    if (nullptr == data) {
        qDebug() << __FUNCTION__ << " :Image Data is NULL.";
        return QList<QImage>();
    }
    int imageCount = 4; //Actual number of valid pictures
    const char * d = data->constData();
    int w = rect.width();
    int h = rect.height();

    if (data->size() != 3 * imageCount*w*h) {
        return QList<QImage>();
    }
    QList<QImage> list;
    int pos = 0;
    for (int i = 0; i < imageCount; ++i) {
        QImage headerImg = CorrectDataHelper::creat8PHeaderImage(i, rect);
        list.append(headerImg);
        QImage image = QImage((uchar*)(d + pos), w, h, QImage::Format_RGB888);
        pos += 3 * w*h;
        list.append(image);
    }
    if (list.size() != imageCount*2) {
        return QList<QImage>();
    }
    return list;
}

QByteArray CorrectDataHelper::imageTo2PLowGrayData(const QImage & img, const QRect& rect)
{
    Q_UNUSED(img)
    Q_UNUSED(rect)
	return QByteArray();
}

QByteArray CorrectDataHelper::imageTo2PGapData(const QImage & img, const QRect& rect)
{
    Q_UNUSED(img)
    Q_UNUSED(rect)
	return QByteArray();
}
