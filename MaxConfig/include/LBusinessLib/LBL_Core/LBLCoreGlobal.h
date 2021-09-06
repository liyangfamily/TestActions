/*********************************************************************************************************
** This file is part of the LBL_Core module of the LBL Toolkit.
*********************************************************************************************************/

#pragma once

#include <QtCore/qglobal.h>

#include <LBL_Core/LBLDef>
#if(LBL_MemoryLeaksDetect)
#include <vld.h>
#endif

#ifndef BUILD_STATIC
# if defined(LBL_CORE_LIB)
#  define LBL_CORE_EXPORT Q_DECL_EXPORT
# else
#  define LBL_CORE_EXPORT Q_DECL_IMPORT
# endif
#else
# define LBL_CORE_EXPORT
#endif
