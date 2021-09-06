#ifndef CVTE_H_SENDERCARDITEM_GLOBAL
#define CVTE_H_SENDERCARDITEM_GLOBAL
#pragma once

#include <QtCore/qglobal.h>

#include <LBL_Core/LBLDef>
#if(LBL_MemoryLeaksDetect)
#include <vld.h>
#endif

#ifndef BUILD_STATIC
# if defined(LBL_SENDERCARDITEM_LIB)
#  define LBL_SENDERCARDITEM_EXPORT Q_DECL_EXPORT
#  define LBL_SENDERCARDITEM_TEMPLATE Q_DECL_EXPORT
# else
#  define LBL_SENDERCARDITEM_EXPORT Q_DECL_IMPORT
#  define SENDERCARDITEM_TEMPLATE
# endif
#else
# define LBL_SENDERCARDITEM_EXPORT
#endif

#endif