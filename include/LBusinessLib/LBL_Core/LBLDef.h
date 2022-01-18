/*********************************************************************************************************
** This file is part of the LBL_Core module of the LBL Toolkit.
*********************************************************************************************************/
#ifndef CVTE_H_LBLDEF
#define CVTE_H_LBLDEF
#pragma once

/*
   LBL_VERSION is (major << 16) + (minor << 8) + patch.
*/
#define LBL_VERSION      LBL_VERSION_CHECK(LBL_VERSION_MAJOR, LBL_VERSION_MINOR, LBL_VERSION_PATCH)
/*
   can be used like #if (LBL_VERSION >= LBL_VERSION_CHECK(4, 4, 0))
*/
#define LBL_VERSION_CHECK(major, minor, patch) ((major<<16)|(minor<<8)|(patch))


#define LBL_VERSION_STR "1.0.1"
#define LBL_VERSION_MAJOR 1
#define LBL_VERSION_MINOR 0
#define LBL_VERSION_PATCH 1

#define LBL_Defalut_SyncTimeout 1500

#define LBL_Max_UsingSenderCardPort 18
#define LBL_Max_SupportSenderCardPort 32

#ifdef _DEBUG
#define LBL_MemoryLeaksDetect false
#else
#define LBL_MemoryLeaksDetect false
#endif

#endif
