#pragma once

#include <QtCore/qglobal.h>

#include <LBL_Core/LBLDef>
#if(LBL_MemoryLeaksDetect)
#include <vld.h>
#endif

#ifndef BUILD_STATIC
# if defined(LBL_RECEIVECARD_LIB)
#  define LBL_RECEIVECARD_EXPORT Q_DECL_EXPORT
# else
#  define LBL_RECEIVECARD_EXPORT Q_DECL_IMPORT
# endif
#else
# define LBL_RECEIVECARD_EXPORT
#endif
