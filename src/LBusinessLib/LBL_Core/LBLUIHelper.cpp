#include "LBL_Core/LBLUIHelper.h"

#include <QCoreApplication>
#include <QDir>
#include <QStandardPaths>
#include <QLineF>
#include <QRectF>
#include <QPolygonF>

QString LBLUIHelper::appName()
{
	//没有必要每次都获取,只有当变量为空时才去获取一次
    static QString appName;
    if (appName.isEmpty()) {
        appName = qApp->applicationFilePath();
        QStringList list = appName.split("/");
        appName = list.at(list.count() - 1).split(".").at(0);
	}

    return appName;
}

QString LBLUIHelper::appPath()
{
    return qApp->applicationDirPath();
}

QString LBLUIHelper::appDocumentsPath()
{
    static QString appDocumentsPath;
    if (appDocumentsPath.isEmpty()) {
        QString tempPath= QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
        tempPath.append(tr("/MaxConfig3"));
        appDocumentsPath=tempPath;
    }
    return appDocumentsPath;
}

QString LBLUIHelper::appDataLocation()
{
    static QString appDataLocation;
    if (appDataLocation.isEmpty()) {
        QDir _appPath(appPath());
        QString tempPath = _appPath.absolutePath();
		QDir dir;
		if (dir.mkpath(tempPath)) {
            appDataLocation = tempPath;
		}
	}
    return appDataLocation;
}

QString LBLUIHelper::appConfigDataLocation()
{
    static QString appConfigDataLocation;
    if (appConfigDataLocation.isEmpty()) {
        QString tempPath = LBLUIHelper::appDocumentsPath();
		tempPath.append(tr("/Config"));
		QDir dir;
		if (dir.mkpath(tempPath)) {
            appConfigDataLocation = tempPath;
		}
	}
    return appConfigDataLocation;
}

QString LBLUIHelper::appParamDataLocation()
{
    static QString appParamDataLocation;
    if (appParamDataLocation.isEmpty()) {
		QString tempPath = LBLUIHelper::appDataLocation();
        tempPath.append(tr("/Parameter"));
		QDir dir;
		if (dir.mkpath(tempPath)) {
            appParamDataLocation = tempPath;
		}
	}
    return appParamDataLocation;
}

QString LBLUIHelper::appLocalsLocation()
{
    static QString appLocalsLocation;
    if (appLocalsLocation.isEmpty()) {
        QString tempPath = LBLUIHelper::appDataLocation();
        tempPath.append(tr("/Locals"));
        QDir dir;
        if (dir.mkpath(tempPath)) {
            appLocalsLocation = tempPath;
        }
    }
    return appLocalsLocation;
}

QString LBLUIHelper::appLogDataLocation()
{
	static QString path;
	if (path.isEmpty()) {
        QString tempPath = LBLUIHelper::appDocumentsPath();
		tempPath.append(tr("/Log"));
		QDir dir;
		if (dir.mkpath(tempPath)) {
			path = tempPath;
		}
	}
	return path;
}

QString LBLUIHelper::appRunTimeDataLocation()
{
	static QString path;
	if (path.isEmpty()) {
        QString tempPath = LBLUIHelper::appDocumentsPath();
		tempPath.append(tr("/RunTime"));
		QDir dir;
		if (dir.mkpath(tempPath)) {
			path = tempPath;
		}
	}
	return path;
}

QString LBLUIHelper::appRunTimeConnectionDataFileName()
{
	static QString name;
	if (name.isEmpty()) {
		name.append(tr("connectionData.bin"));
	}
	return name;
}

QString LBLUIHelper::appMonitorTemperatureTableFileName()
{
	static QString name;
	if (name.isEmpty()) {
		name.append(tr("EG4S20BG25.mif"));
	}
	return name;
}

bool LBLUIHelper::isIP(const QString &ip)
{
	QRegExp RegExp("((2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){3}(2[0-4]\\d|25[0-5]|[01]?\\d\\d?)");
	return RegExp.exactMatch(ip);
}

bool LBLUIHelper::isMac(const QString &mac)
{
	QRegExp RegExp("^[A-F0-9]{2}(-[A-F0-9]{2}){5}$");
	return RegExp.exactMatch(mac);
}

bool LBLUIHelper::isTel(const QString &tel)
{
	if (tel.length() != 11) {
		return false;
	}

	if (!tel.startsWith("13") && !tel.startsWith("14") && !tel.startsWith("15") && !tel.startsWith("18")) {
		return false;
	}

	return true;
}

bool LBLUIHelper::isEmail(const QString &email)
{
	if (!email.contains("@") || !email.contains(".com")) {
		return false;
	}

	return true;
}

quint8 LBLUIHelper::getCheckSum(const QByteArray & data)
{
	//计算和
	if (data.isEmpty() || data.isNull())
	{
		return 0;
	}

	unsigned char sum = 0;
	for (int i = 0; i < data.size(); i++)
	{
		sum += data.at(i);
	}
    return sum;
}

int LBLUIHelper::strHexToDecimal(const QString &strHex)
{
    bool ok;
    return strHex.toInt(&ok, 16);
}

QString LBLUIHelper::decimalToStrHex(int decimal)
{
    QString temp = QString::number(decimal, 16);
    if (temp.length() == 1) {
        temp = "0" + temp;
    }

    return temp;
}

QString LBLUIHelper::byteArrayToAsciiStr(const QByteArray &data)
{
    QString temp;
    int len = data.size();

    for (int i = 0; i < len; i++) {
        //0x20为空格,空格以下都是不可见字符
        char b = data.at(i);

        if (0x00 == b) {
            temp += QString("\\NUL");
        } else if (0x01 == b) {
            temp += QString("\\SOH");
        } else if (0x02 == b) {
            temp += QString("\\STX");
        } else if (0x03 == b) {
            temp += QString("\\ETX");
        } else if (0x04 == b) {
            temp += QString("\\EOT");
        } else if (0x05 == b) {
            temp += QString("\\ENQ");
        } else if (0x06 == b) {
            temp += QString("\\ACK");
        } else if (0x07 == b) {
            temp += QString("\\BEL");
        } else if (0x08 == b) {
            temp += QString("\\BS");
        } else if (0x09 == b) {
            temp += QString("\\HT");
        } else if (0x0A == b) {
            temp += QString("\\LF");
        } else if (0x0B == b) {
            temp += QString("\\VT");
        } else if (0x0C == b) {
            temp += QString("\\FF");
        } else if (0x0D == b) {
            temp += QString("\\CR");
        } else if (0x0E == b) {
            temp += QString("\\SO");
        } else if (0x0F == b) {
            temp += QString("\\SI");
        } else if (0x10 == b) {
            temp += QString("\\DLE");
        } else if (0x11 == b) {
            temp += QString("\\DC1");
        } else if (0x12 == b) {
            temp += QString("\\DC2");
        } else if (0x13 == b) {
            temp += QString("\\DC3");
        } else if (0x14 == b) {
            temp += QString("\\DC4");
        } else if (0x15 == b) {
            temp += QString("\\NAK");
        } else if (0x16 == b) {
            temp += QString("\\SYN");
        } else if (0x17 == b) {
            temp += QString("\\ETB");
        } else if (0x18 == b) {
            temp += QString("\\CAN");
        } else if (0x19 == b) {
            temp += QString("\\EM");
        } else if (0x1A == b) {
            temp += QString("\\SUB");
        } else if (0x1B == b) {
            temp += QString("\\ESC");
        } else if (0x1C == b) {
            temp += QString("\\FS");
        } else if (0x1D == b) {
            temp += QString("\\GS");
        } else if (0x1E == b) {
            temp += QString("\\RS");
        } else if (0x1F == b) {
            temp += QString("\\US");
        } else if (0x7F == b) {
            temp += QString("\\x7F");
        } else if (0x5C == b) {
            temp += QString("\\x5C");
        } else if (0x20 >= b) {
            temp += QString("\\x%1").arg(decimalToStrHex((quint8)b));
        } else {
            temp += QString("%1").arg(b);
        }
    }

    return temp.trimmed();
}

QByteArray LBLUIHelper::asciiStrToByteArray(const QString &str)
{
    QByteArray buffer;
    int len = str.length();
    QString letter;
    QString hex;

    for (int i = 0; i < len; i++) {
        letter = str.at(i);

        if (letter == "\\") {
            i++;
            letter = str.mid(i, 1);

            if (letter == "x") {
                i++;
                hex = str.mid(i, 2);
                buffer.append(strHexToDecimal(hex));
                i++;
                continue;
            } else if (letter == "N") {
                i++;
                hex = str.mid(i, 1);

                if (hex == "U") {
                    i++;
                    hex = str.mid(i, 1);

                    if (hex == "L") {           //NUL=0x00
                        buffer.append((char)0x00);
                        continue;
                    }
                } else if (hex == "A") {
                    i++;
                    hex = str.mid(i, 1);

                    if (hex == "K") {           //NAK=0x15
                        buffer.append(0x15);
                        continue;
                    }
                }
            } else if (letter == "S") {
                i++;
                hex = str.mid(i, 1);

                if (hex == "O") {
                    i++;
                    hex = str.mid(i, 1);

                    if (hex == "H") {           //SOH=0x01
                        buffer.append(0x01);
                        continue;
                    } else {                    //SO=0x0E
                        buffer.append(0x0E);
                        i--;
                        continue;
                    }
                } else if (hex == "T") {
                    i++;
                    hex = str.mid(i, 1);

                    if (hex == "X") {           //STX=0x02
                        buffer.append(0x02);
                        continue;
                    }
                } else if (hex == "I") {        //SI=0x0F
                    buffer.append(0x0F);
                    continue;
                } else if (hex == "Y") {
                    i++;
                    hex = str.mid(i, 1);

                    if (hex == "N") {           //SYN=0x16
                        buffer.append(0x16);
                        continue;
                    }
                } else if (hex == "U") {
                    i++;
                    hex = str.mid(i, 1);

                    if (hex == "B") {           //SUB=0x1A
                        buffer.append(0x1A);
                        continue;
                    }
                }
            } else if (letter == "E") {
                i++;
                hex = str.mid(i, 1);

                if (hex == "T") {
                    i++;
                    hex = str.mid(i, 1);

                    if (hex == "X") {           //ETX=0x03
                        buffer.append(0x03);
                        continue;
                    } else if (hex == "B") {    //ETB=0x17
                        buffer.append(0x17);
                        continue;
                    }
                } else if (hex == "O") {
                    i++;
                    hex = str.mid(i, 1);

                    if (hex == "T") {           //EOT=0x04
                        buffer.append(0x04);
                        continue;
                    }
                } else if (hex == "N") {
                    i++;
                    hex = str.mid(i, 1);

                    if (hex == "Q") {           //ENQ=0x05
                        buffer.append(0x05);
                        continue;
                    }
                } else if (hex == "M") {        //EM=0x19
                    buffer.append(0x19);
                    continue;
                } else if (hex == "S") {
                    i++;
                    hex = str.mid(i, 1);

                    if (hex == "C") {           //ESC=0x1B
                        buffer.append(0x1B);
                        continue;
                    }
                }
            } else if (letter == "A") {
                i++;
                hex = str.mid(i, 1);

                if (hex == "C") {
                    i++;
                    hex = str.mid(i, 1);

                    if (hex == "K") {           //ACK=0x06
                        buffer.append(0x06);
                        continue;
                    }
                }
            } else if (letter == "B") {
                i++;
                hex = str.mid(i, 1);

                if (hex == "E") {
                    i++;
                    hex = str.mid(i, 1);

                    if (hex == "L") {           //BEL=0x07
                        buffer.append(0x07);
                        continue;
                    }
                } else if (hex == "S") {        //BS=0x08
                    buffer.append(0x08);
                    continue;
                }
            } else if (letter == "C") {
                i++;
                hex = str.mid(i, 1);

                if (hex == "R") {               //CR=0x0D
                    buffer.append(0x0D);
                    continue;
                } else if (hex == "A") {
                    i++;
                    hex = str.mid(i, 1);

                    if (hex == "N") {           //CAN=0x18
                        buffer.append(0x18);
                        continue;
                    }
                }
            } else if (letter == "D") {
                i++;
                hex = str.mid(i, 1);

                if (hex == "L") {
                    i++;
                    hex = str.mid(i, 1);

                    if (hex == "E") {           //DLE=0x10
                        buffer.append(0x10);
                        continue;
                    }
                } else if (hex == "C") {
                    i++;
                    hex = str.mid(i, 1);

                    if (hex == "1") {           //DC1=0x11
                        buffer.append(0x11);
                        continue;
                    } else if (hex == "2") {    //DC2=0x12
                        buffer.append(0x12);
                        continue;
                    } else if (hex == "3") {    //DC3=0x13
                        buffer.append(0x13);
                        continue;
                    } else if (hex == "4") {    //DC2=0x14
                        buffer.append(0x14);
                        continue;
                    }
                }
            } else if (letter == "F") {
                i++;
                hex = str.mid(i, 1);

                if (hex == "F") {               //FF=0x0C
                    buffer.append(0x0C);
                    continue;
                } else if (hex == "S") {        //FS=0x1C
                    buffer.append(0x1C);
                    continue;
                }
            } else if (letter == "H") {
                i++;
                hex = str.mid(i, 1);

                if (hex == "T") {               //HT=0x09
                    buffer.append(0x09);
                    continue;
                }
            } else if (letter == "L") {
                i++;
                hex = str.mid(i, 1);

                if (hex == "F") {               //LF=0x0A
                    buffer.append(0x0A);
                    continue;
                }
            } else if (letter == "G") {
                i++;
                hex = str.mid(i, 1);

                if (hex == "S") {               //GS=0x1D
                    buffer.append(0x1D);
                    continue;
                }
            } else if (letter == "R") {
                i++;
                hex = str.mid(i, 1);

                if (hex == "S") {               //RS=0x1E
                    buffer.append(0x1E);
                    continue;
                }
            } else if (letter == "U") {
                i++;
                hex = str.mid(i, 1);

                if (hex == "S") {               //US=0x1F
                    buffer.append(0x1F);
                    continue;
                }
            } else if (letter == "V") {
                i++;
                hex = str.mid(i, 1);

                if (hex == "T") {               //VT=0x0B
                    buffer.append(0x0B);
                    continue;
                }
            } else if (letter == "\\") {
                //如果连着的是多个\\则对应添加\对应的16进制0x5C
                buffer.append(0x5C);
                continue;
            } else {
                //将对应的\[前面的\\也要加入
                buffer.append(0x5C);
                buffer.append(letter.toLatin1());
                continue;
            }
        }

        buffer.append(str.mid(i, 1).toLatin1());

    }

    return buffer;
}


QByteArray LBLUIHelper::hexStrToByteArray(const QString &str)
{
    QByteArray senddata;
    int hexdata, lowhexdata;
    int hexdatalen = 0;
    int len = str.length();
    senddata.resize(len / 2);
    char lstr, hstr;

    for (int i = 0; i < len;) {
        hstr = str.at(i).toLatin1();
        if (hstr == ' ') {
            i++;
            continue;
        }

        i++;
        if (i >= len) {
            break;
        }

        lstr = str.at(i).toLatin1();
        hexdata = convertHexChar(hstr);
        lowhexdata = convertHexChar(lstr);

        if ((hexdata == 16) || (lowhexdata == 16)) {
            break;
        } else {
            hexdata = hexdata * 16 + lowhexdata;
        }

        i++;
        senddata[hexdatalen] = (char)hexdata;
        hexdatalen++;
    }

    senddata.resize(hexdatalen);
    return senddata;
}

char LBLUIHelper::convertHexChar(char ch)
{
    if ((ch >= '0') && (ch <= '9')) {
        return ch - 0x30;
    } else if ((ch >= 'A') && (ch <= 'F')) {
        return ch - 'A' + 10;
    } else if ((ch >= 'a') && (ch <= 'f')) {
        return ch - 'a' + 10;
    } else {
        return (-1);
    }
}

QString LBLUIHelper::byteArrayToHexStr(const QByteArray &data)
{
    QString temp = "";
    QString hex = data.toHex();

    for (int i = 0; i < hex.length(); i = i + 2) {
        temp += hex.mid(i, 2) + " ";
    }

    return temp.trimmed().toUpper();
}

QLineF LBLUIHelper::clipLineWithRect(QLineF line, QRectF box)
{
	QRectF lineBox(line.p1(), line.p2());
	if ((lineBox.width() != 0 && lineBox.height() != 0) && !box.intersects(lineBox))
	{//没有相交区域
		line = QLineF();
		return line;
	}

	bool b0 = box.contains(line.p1());
	bool b1 = box.contains(line.p2());
	if (b0 && b1)
	{//线段在矩形内
		return line;
	}
	else
	{
		//取四条边
		QLineF line1(box.topLeft(), box.topRight());
		QLineF line2(box.topRight(), box.bottomRight());
		QLineF line3(box.bottomLeft(), box.bottomRight());
		QLineF line4(box.topLeft(), box.bottomLeft());

		//取与四条边的是否相交和交点
		QPointF pt1, pt2, pt3, pt4;
		bool bi1 = QLineF::BoundedIntersection == line.intersect(line1, &pt1);
		bool bi2 = QLineF::BoundedIntersection == line.intersect(line2, &pt2);
		bool bi3 = QLineF::BoundedIntersection == line.intersect(line3, &pt3);
		bool bi4 = QLineF::BoundedIntersection == line.intersect(line4, &pt4);

		if (b0)
		{
			//起始点在区域内，取另外一个交点
			if (bi1&&line.p1() != pt1) return QLineF(line.p1(), pt1);
			if (bi2&&line.p1() != pt2) return QLineF(line.p1(), pt2);
			if (bi3&&line.p1() != pt3) return QLineF(line.p1(), pt3);
			if (bi4&&line.p1() != pt4) return QLineF(line.p1(), pt4);
		}
		else if (b1)
		{
			//结束点在区域内，取另外一个交点
			if (bi1&&line.p2() != pt1) return QLineF(line.p2(), pt1);
			if (bi2&&line.p2() != pt2) return QLineF(line.p2(), pt2);
			if (bi3&&line.p2() != pt3) return QLineF(line.p2(), pt3);
			if (bi4&&line.p2() != pt4) return QLineF(line.p2(), pt4);
		}
		else
		{
			//线段不在区域内，获取两个交点
			QPolygonF pts;
			if (bi1) pts.append(pt1);
			if (bi2) pts.append(pt2);
			if (bi3) pts.append(pt3);
			if (bi4) pts.append(pt4);
			if (!pts.isEmpty()) {
				return QLineF(pts.first(), pts.last());
			}
			else {
				line = QLineF();
				return line;
			}
		}
	}
	line = QLineF();
	return line;
}
