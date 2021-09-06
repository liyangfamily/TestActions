TEMPLATE = subdirs

CONFIG += ordered

SUBDIRS += \
    LBL_Core \
    LBL_CommunicatEngine \
    LBL_Control/LBL_Android \
    LBL_Control/LBL_ReceiveCard \
    LBL_Control/LBL_SenderCard \
    LBL_Control/LBL_HDMIChip \
    LBL_Control/LBL_FileTransfer \
    LBL_SenderCardItem \
    LAPI_Control

QMAKE_EXTRA_TARGETS += deployqt # dummy
