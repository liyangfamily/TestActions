#pragma once
#include <QtGlobal>
#include <QUuid>
#include <QByteArray>
#include "LBLGZSenderCardStruct.h"

namespace LBL
{
	namespace SC
	{
		typedef struct tagSenderCardInfoAck
		{
			bool bVaild = false;
			quint8 brightness = 0;
			quint8 senderCardUuidType = 0;
			QUuid senderCardUuid;

			QString fpgaVersion;
			QString mcuAppVersion;
			QString mcuBootVersion;

		}SSenderCardInfoAck;
	}
}