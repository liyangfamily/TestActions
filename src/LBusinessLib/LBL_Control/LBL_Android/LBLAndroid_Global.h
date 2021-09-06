#pragma once

#include <QtCore/qglobal.h>

#include <LBL_Core/LBLDef.h>
#if(LBL_MemoryLeaksDetect)
#include <vld.h>
#endif


#ifndef BUILD_STATIC
# if defined(LBL_ANDROID_LIB)
#  define LBL_ANDROID_EXPORT Q_DECL_EXPORT
# else
#  define LBL_ANDROID_EXPORT Q_DECL_IMPORT
# endif
#else
# define LBL_ANDROID_EXPORT
#endif
