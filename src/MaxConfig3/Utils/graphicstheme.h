#pragma once
#include <QString>
#include <QVector>
#include <QColor>
#include <QSize>
#include <QMap>
#include <QFont>

namespace Utils {
	namespace GraphicsTheme {

		class ModultItemTheme
		{
		public:
			enum PortColor
			{
				Port_1 = 0,
				Port_2,
				Port_3,
				Port_4,
				Port_5,
				Port_6,
				Port_7,
				Port_8,
				Port_9,
				Port_10,
				Port_11,
				Port_12,
				Port_13,
				Port_14,
				Port_15,
				Port_16,
				Port_17,
				Port_18,
				Port_19,
				Port_20,

				Port_Null,
			};

			enum ItemColor 
			{
				RectBorderColor = 0,
				RectAnchorPointBorderColor,
				RectAnchorPointColor,
				TextColor,
				ArrowColor,
				ArrowSelectColor,
			};

			ModultItemTheme();
			QColor portColor(PortColor role);
			QColor itemColor(ItemColor role);
		public:
			int BorderPenWidth;
			int ArrowPenWidth;
			qreal RectAnchorPointSize;
			qreal ArrowSize;
			QFont ItemFont;
		private:
			void initPortColor();
			void initItemColor();
			void initItem();
			QVector<QPair<QColor, QString>> m_portColor;
			QVector<QPair<QColor, QString>> m_itemColor;
		};
		static ModultItemTheme g_ModuleTheme;
	}
}