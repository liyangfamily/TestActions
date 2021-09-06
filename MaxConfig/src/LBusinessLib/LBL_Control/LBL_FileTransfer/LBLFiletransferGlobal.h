#pragma once

#include <QtCore/qglobal.h>

#include <LBL_Core/LBLDef>
#if(LBL_MemoryLeaksDetect)
#include <vld.h>
#endif

#ifndef BUILD_STATIC
# if defined(LBL_FILETRANSFER_LIB)
#  define LBL_FILETRANSFER_EXPORT Q_DECL_EXPORT
# else
#  define LBL_FILETRANSFER_EXPORT Q_DECL_IMPORT
# endif
#else
# define LBL_FILETRANSFER_EXPORT
#endif
