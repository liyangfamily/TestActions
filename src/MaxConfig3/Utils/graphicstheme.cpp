#include "graphicstheme.h"

namespace Utils
{
	namespace GraphicsTheme 
	{
		
		ModultItemTheme::ModultItemTheme()
		{
			initPortColor();
			initItemColor();
			initItem();
		}

		QColor ModultItemTheme::portColor(PortColor role)
		{
			if (role >= 0 && role < m_portColor.size()) {
				return m_portColor[role].first;
			}
			else {
				return m_portColor.back().first;
			}
		}

		QColor ModultItemTheme::itemColor(ItemColor role)
		{
			if (role < m_itemColor.size()) {
				return m_itemColor[role].first;
			}
			else {
				return QColor(Qt::transparent);
			}
		}

		void ModultItemTheme::initPortColor()
		{
			m_portColor.append(qMakePair(QColor("#DC24d3c9"), QString("Port_1")));
			m_portColor.append(qMakePair(QColor("#DCdd7bec"), QString("Port_2")));
			m_portColor.append(qMakePair(QColor("#DC5fc754"), QString("Port_3")));
			m_portColor.append(qMakePair(QColor("#DC6272ea"), QString("Port_4")));
			m_portColor.append(qMakePair(QColor("#DCe8e615"), QString("Port_5")));
			m_portColor.append(qMakePair(QColor("#DCef9742"), QString("Port_6")));
			m_portColor.append(qMakePair(QColor("#DCf18181"), QString("Port_7")));
			m_portColor.append(qMakePair(QColor("#DC6fb5f7"), QString("Port_8")));
			m_portColor.append(qMakePair(QColor("#DCb1b3fb"), QString("Port_9")));
			m_portColor.append(qMakePair(QColor("#DCffd2d2"), QString("Port_10")));
			m_portColor.append(qMakePair(QColor("#DCd2e9ff"), QString("Port_11")));
			m_portColor.append(qMakePair(QColor("#DCf4d2ff"), QString("Port_12")));
			m_portColor.append(qMakePair(QColor("#DC97d8d7"), QString("Port_13")));
			m_portColor.append(qMakePair(QColor("#DCffbf86"), QString("Port_14")));
			m_portColor.append(qMakePair(QColor("#DCfcfbc4"), QString("Port_15")));
			m_portColor.append(qMakePair(QColor("#DCb5e2ae"), QString("Port_16")));
			m_portColor.append(qMakePair(QColor("#DC00aa7f"), QString("Port_17")));
			m_portColor.append(qMakePair(QColor("#DCFF616D"), QString("Port_18")));
			m_portColor.append(qMakePair(QColor("#DC185ADB"), QString("Port_19")));
			m_portColor.append(qMakePair(QColor("#DC888888"), QString("Port_20")));
			m_portColor.append(qMakePair(QColor("#DCDCDCDC"), QString("Port_Null"))); //NULL
		}

		void ModultItemTheme::initItemColor()
		{
			m_itemColor.append(qMakePair(QColor("#FFFFFFFF"), QString("RectBorderColor")));
			m_itemColor.append(qMakePair(QColor("#FFFFFFFF"), QString("RectAnchorPointBorderColor")));
			m_itemColor.append(qMakePair(QColor("#FF999999"), QString("RectAnchorPointColor")));
			m_itemColor.append(qMakePair(Qt::black, QString("TextColor")));
			m_itemColor.append(qMakePair(QColor("#FFFFFFFF"), QString("ArrowColor")));
			m_itemColor.append(qMakePair(QColor("#FF256bf9"), QString("ArrowSelectColor")));
		}

		void ModultItemTheme::initItem()
		{
			BorderPenWidth = 2; 
			ArrowPenWidth = 6;
			RectAnchorPointSize = 50.0; 
			ArrowSize = 25.0;
			ItemFont = QFont("Microsoft YaHei", 19);
		}

	}
}