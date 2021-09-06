/*********************************************************************************************************
** This file is part of the LBL_CommunicatEngine module of the LBL Toolkit.
*********************************************************************************************************/

/*!
\class LBLPackageEvent

\inmodule LBL_CommunicatEngine

\brief The LBL_CommunicatEngine class is a custom registration event of Qt system, used to dispatcher communication data package.

\code
	LBLPackageEvent *event = new LBLPackageEvent(LBLPackageEvent::s_disPatcherPackage_eventType);
	event->setPackage(package);
	QCoreApplication::postEvent(item, event);
\endcode

\note:

*/

#include "LBL_CommunicatEngine/LBLPackageEvent.h"

QEvent::Type LBLPackageEvent::s_disPatcherPackage_eventType = QEvent::Type(QEvent::registerEventType());
QEvent::Type LBLPackageEvent::s_transitPackage_eventType = QEvent::Type(QEvent::registerEventType()); 
