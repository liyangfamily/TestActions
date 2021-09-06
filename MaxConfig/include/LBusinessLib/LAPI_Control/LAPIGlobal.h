#ifndef CVTE_H_ILAPI_CONTROL_GLOBAL
#define CVTE_H_ILAPI_CONTROL_GLOBAL
#pragma once

#include <QtCore/qglobal.h>

#include <LBL_Core/LBLDef>
#if(LBL_MemoryLeaksDetect)
#include <vld.h>
#endif

#ifndef BUILD_STATIC
# if defined(LAPI_CONTROL_LIB)
#  define ILAPI_CONTROL_EXPORT Q_DECL_EXPORT
# else
#  define ILAPI_CONTROL_EXPORT Q_DECL_IMPORT
# endif
#else
# define SENDERCARDMGR_EXPORT
#endif

#ifndef LAPI_Stdcall
#	ifdef __cplusplus
#		define LAPI_Stdcall
#	else
#		define LAPI_Stdcall __stdcall
#	endif
#endif

#endif