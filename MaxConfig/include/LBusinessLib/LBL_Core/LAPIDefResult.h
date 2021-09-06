#ifndef CVTE_H_LAPI_STRUCT_RESULT
#define CVTE_H_LAPI_STRUCT_RESULT
#pragma once

namespace LAPI
{
	/*API函数返回状态*/
	enum EResult
	{
		//集控指令
		ER_INTECTRL_NULL = 0x0000, //空
		ER_INTECTRL_Success = 0x0001, //成功 
		ER_INTECTRL_Fail_NoReason = 0x0002, //失败-无具体原因
		ER_INTECTRL_Fail_NoCOM = 0x0003, //失败-找不到对应串口
		ER_INTECTRL_Fail_NoRet = 0x0004, //失败-无返回
		ER_INTECTRL_Fail_Busy = 0x0005, //失败-忙碌
		ER_INTECTRL_Fail_Exclusive = 0x0006, //失败-被占用
		ER_INTECTRL_Fail_NoCMD = 0x0007, //失败-命令码不支持

		ER_INTECTRL_PENETRAT_SetSuccess=0x0050,
		ER_INTECTRL_PENETRAT_SetFaild =0x0051,
		ER_INTECTRL_PENETRAT_GetSuccess =0x0052,
		ER_INTECTRL_PENETRAT_GetFaild =0x0053,

		//通信库
		ER_Fail = 0xE000,
		ER_Success = ER_INTECTRL_Success, //成功
		ER_InDataError = 0xE002,
		ER_InDataNullptr = 0xE003,
		ER_CannotEnterExclusiveMode = 0xE004,
		ER_NoSenderCardSelect = 0xE005,
		ER_NotSupportThisCommand = 0xE006,
		ER_SyncSendTimeOut = 0xE007,

		//连接关系
		ER_CONNECT_IllegalData=0xC000,
		ER_CONNECT_IllegalPortCount=0xC001,
		ER_CONNECT_NetPortLoadingAreaNotMatch =0xC002,
		ER_CONNECT_NetPortLoadingAreaNotRead =0xC003,
		//文件传输
		ER_FILE_StartSendFile_Success=0xF001,
		ER_FILE_Handshake_Fail=0xF002,
		ER_FILE_StartSendFile_DoNotSave=0xF003,

		ER_FILE_SendFileData_Success=0xF010,
		ER_FILE_SendFileData_SendComplite=0xF011,
		ER_FILE_SendFileData_VerificationFailed =0xF012,
		ER_FILE_SendFileData_FailedForUnknownReason =0xF013,
		ER_FILE_SendFileData_TooManyFailedRetransmissions =0xF014,
		ER_FILE_SendFileData_NotResponse =0xF015,

		ER_FILE_RequestUpgrade_FileNotExist =0xF020,
		ER_FILE_RequestUpgrade_FileDamage = 0xF021,
		ER_FILE_RequestUpgrade_Success = 0xF022,

		ER_FILE_UpgradeStatus_Erasing =0xF030,
		ER_FILE_UpgradeStatus_Upgrading =0xF031,
		ER_FILE_UpgradeStatus_Resetting =0xF032,
		ER_FILE_UpgradeStatus_Success =0xF033,
		ER_FILE_UpgradeStatus_Fail =0xF034,
		ER_FILE_UpgradeStatus_StatusNotReplied =0xF035,

		ER_FILE_Upgrade_AlreadyExistUpgrade =0xF040,
		ER_FILE_Upgrade_FileNameEmpty =0xF041,
		ER_FILE_Upgrade_FileOpenFail =0xF042,
		ER_FILE_Upgrade_IllegalSinglePackLength =0xF043,
		ER_FILE_Upgrade_ExternalCancel =0xF044,
		ER_FILE_Upgrade_TransmissionNotOver =0xF045,
		ER_FILE_Upgrade_IllegalFileData =0xF046,
		ER_FILE_Upgrade_RunTimeFileCreatFail =0xF047,
		ER_FILE_Upgrade_RequestUpgradeFail =0xF048,

	};
}
#endif // CVTE_H_LAPI_STRUCT_RESULT