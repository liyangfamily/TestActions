#ifndef LAPIDEFUI_H
#define LAPIDEFUI_H
#pragma once
/*********************************************************************************************************
**通信库中所有关于界面选项的统一定义
**不同的通信对象可能对同一项功能有不同的值，此处对所有选项值进行统一定义，转换在各自的通信对象中完成。                                                                 
*********************************************************************************************************/
namespace LAPI
{
	namespace UI
	{
		/*输入源*/
		enum EInputSource
		{
			EIS_Android = 0x00,
			EIS_PC = 0x01,
			EIS_HDMI1 = 0x02,
			EIS_HDMI2 = 0x03,
			EIS_HDMI3 = 0x04,
			EIS_DP = 0x05,
		};

        /*输出源*/
        enum EOutputSource
        {
            EOS_Android = 0x00,
            EOS_PC = 0x01,
            EOS_HDMI1 = 0x02,
            EOS_HDMI2 = 0x03,
            EOS_HDMI3 = 0x04,
            EOS_DP = 0x05,
            EOS_SameScreen = 0x06,
        };

		/*色温*/
		enum EColorTemperature
		{
			ECT_Standard = 0x01,
			ECT_Warm = 0x02,
			ECT_Cool = 0x03,
			ECT_User = 0x04,
		};

		/*HDMI通道*/
		enum EHDMIChannel
		{
			EHC_All = 0x00,
			EHC_1 = 0x01,
			EHC_2 = 0x02,
			EHC_3 = 0x03,
			EHC_4 = 0x04,
		};

		/*情景模式*/
		enum ESceneMode
		{
			ESM_MeetingMode = 0x00, //会议模式
			ESM_DemoMode = 0x01, //演示模式
			ESM_ECOMode = 0x02, //节能模式
			ESM_UserMode = 0x03, //用户模式
		};

		/*分屏模式*/
		enum EMultiScreenMode
		{
			EMSM_None = 0x00, //无分屏
			EMSM_1Window = 0x01, //1个窗口
			EMSM_2Window = 0x02, //2个窗口、
			EMSM_SideBySide=0x03, //左右平分
			EMSM_3Divison1=0x04, //3个窗口,左大，右上下平分
			EMSM_3Division2 = 0x05, //3个窗口,中16:9，左右
			EMSM_4Window = 0x06, //4个窗口
			EMSM_UserMode = 0x07, //自定义模式
		};

        /*显示比例*/
        enum EImageRatio
        {
            EIR_Full=0x00,
            EIR_Original=0x01,
            EIR_4_3=0x02,
            EIR_16_9=0x03,
            EIR_1_1=0x04,
            EIR_SmartView
        };

		/*双拼分屏模式*/
		enum ESplitDouScreenMode
		{
			ESDS_FullScreenMode = 0x00, //全屏模式
			ESDS_CenteredMode = 0x01, //居中模式
			ESDS_DualScreenMode = 0x02, //双屏模式
			ESDS_CustomMode = 0x03, //自定义模式
		};

		/*测试模式*/
		enum EPictureTestMode
		{
			EPTM_Red = 0xC2,//红色
			EPTM_Green = 0xC1,//绿色
			EPTM_Blue = 0xC0,//蓝色
			EPTM_White = 0xC3,//白色
			EPTM_Yellow = 0xC4,//黄色
			EPTM_Purple = 0xC5,//紫色
			EPTM_Cyan = 0xC6,//青色
			EPTM_Black = 0xC7,//黑色
			EPTM_LeftSlash = 0xCC,//左斜线
			EPTM_RightSlash = 0xCE,//右斜线
			EPTM_HorizontalSlash = 0xCA,//水平线
			EPTM_VerticalSlash = 0xC8,//垂直线
			EPTM_GradientRed = 0xD6,//渐变红
			EPTM_GradientGreen = 0xD4,//渐变绿
			EPTM_GradientBlue = 0xD2,//渐变蓝
			EPTM_GradientWhite = 0xD0,//渐变白
			EPTM_Normal=0xFF,//测试模式关闭，其他的测试模式打开
		};
		/*测试模式*/
		enum EPictureTestModeSpeed
		{
			EPTS_Fastest = 0x00,
			EPTS_VeryFast = 0x01,
			EPTS_Faster = 0x02,
			EPTS_Fast = 0x03,
			EPTS_NormalSpeed = 0x04,
			EPTS_Slow = 0x05,
			EPTS_VerySlow= 0x06,
			EPTS_Slowest = 0x07,
			EPTS_Stop = 0xFF,//测试模式暂停，其他的测试模式动态
		};
	}
}

#endif // LAPIDEFUI_H
