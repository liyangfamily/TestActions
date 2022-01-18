#!/bin/bash
#判断参数个数
if [ $# != 2 ]; then
echo "Usage: $0 TARGET_BUILD_DIR PRODUCT_NAME"
echo "Usage: $0 ../bin MaxConfig"
exit
fi
echo "start $0"

TARGET_BUILD_DIR=$1
echo "TARGET_BUILD_DIR:$1"
PRODUCT_NAME=$2
echo "PRODUCT_NAME:$2"

UNIX_TARGET=$TARGET_BUILD_DIR/$PRODUCT_NAME.app/Contents/MacOS/$PRODUCT_NAME
LIB_TARGET=$TARGET_BUILD_DIR/$PRODUCT_NAME.app/Contents/Frameworks
#改变dylib的引用地址，防止library/framewokr not found
otool -L $UNIX_TARGET
#MaxConfig依赖
install_name_tool -change "libLAPI_Control.1.dylib" "@rpath/libLAPI_Control.1.dylib" "$UNIX_TARGET"
install_name_tool -change "libLBL_CommunicatEngine.1.dylib" "@rpath/libLBL_CommunicatEngine.1.dylib" "$UNIX_TARGET"
install_name_tool -change "libLBL_SenderCardItem.1.dylib" "@rpath/libLBL_SenderCardItem.1.dylib" "$UNIX_TARGET"
install_name_tool -change "libLBL_Core.1.dylib" "@rpath/libLBL_Core.1.dylib" "$UNIX_TARGET"
install_name_tool -change "libLBL_Android.1.dylib" "@rpath/libLBL_Android.1.dylib" "$UNIX_TARGET"
install_name_tool -change "libLBL_ReceiveCard.1.dylib" "@rpath/libLBL_ReceiveCard.1.dylib" "$UNIX_TARGET"
install_name_tool -change "libLBL_SenderCard.1.dylib" "@rpath/libLBL_SenderCard.1.dylib" "$UNIX_TARGET"
install_name_tool -change "libLBL_HDMIChip.1.dylib" "@rpath/libLBL_HDMIChip.1.dylib" "$UNIX_TARGET"
install_name_tool -change "libLBL_FileTransfer.1.dylib" "@rpath/libLBL_FileTransfer.1.dylib" "$UNIX_TARGET"
install_name_tool -change "libAdvancedsetting.1.dylib" "@rpath/libAdvancedsetting.1.dylib" "$UNIX_TARGET"

#LAPI_Control依赖
install_name_tool -change "libLAPI_Control.1.dylib" "@rpath/libLAPI_Control.1.dylib" "$LIB_TARGET/libLAPI_Control.1.0.0.dylib"
install_name_tool -change "libLBL_CommunicatEngine.1.dylib" "@rpath/libLBL_CommunicatEngine.1.dylib" "$LIB_TARGET/libLAPI_Control.1.0.0.dylib"
install_name_tool -change "libLBL_SenderCardItem.1.dylib" "@rpath/libLBL_SenderCardItem.1.dylib" "$LIB_TARGET/libLAPI_Control.1.0.0.dylib"
install_name_tool -change "libLBL_Core.1.dylib" "@rpath/libLBL_Core.1.dylib" "$LIB_TARGET/libLAPI_Control.1.0.0.dylib"
install_name_tool -change "libLBL_Android.1.dylib" "@rpath/libLBL_Android.1.dylib" "$LIB_TARGET/libLAPI_Control.1.0.0.dylib"
install_name_tool -change "libLBL_ReceiveCard.1.dylib" "@rpath/libLBL_ReceiveCard.1.dylib" "$LIB_TARGET/libLAPI_Control.1.0.0.dylib"
install_name_tool -change "libLBL_SenderCard.1.dylib" "@rpath/libLBL_SenderCard.1.dylib" "$LIB_TARGET/libLAPI_Control.1.0.0.dylib"
install_name_tool -change "libLBL_HDMIChip.1.dylib" "@rpath/libLBL_HDMIChip.1.dylib" "$LIB_TARGET/libLAPI_Control.1.0.0.dylib"
install_name_tool -change "libLBL_FileTransfer.1.dylib" "@rpath/libLBL_FileTransfer.1.dylib" "$LIB_TARGET/libLAPI_Control.1.0.0.dylib"

#LBL_SenderCardItem依赖
install_name_tool -change "libLBL_CommunicatEngine.1.dylib" "@rpath/libLBL_CommunicatEngine.1.dylib" "$LIB_TARGET/libLBL_SenderCardItem.1.0.0.dylib"
install_name_tool -change "libLBL_SenderCardItem.1.dylib" "@rpath/libLBL_SenderCardItem.1.dylib" "$LIB_TARGET/libLBL_SenderCardItem.1.0.0.dylib"
install_name_tool -change "libLBL_Core.1.dylib" "@rpath/libLBL_Core.1.dylib" "$LIB_TARGET/libLBL_SenderCardItem.1.0.0.dylib"
install_name_tool -change "libLBL_Android.1.dylib" "@rpath/libLBL_Android.1.dylib" "$LIB_TARGET/libLBL_SenderCardItem.1.0.0.dylib"
install_name_tool -change "libLBL_ReceiveCard.1.dylib" "@rpath/libLBL_ReceiveCard.1.dylib" "$LIB_TARGET/libLBL_SenderCardItem.1.0.0.dylib"
install_name_tool -change "libLBL_SenderCard.1.dylib" "@rpath/libLBL_SenderCard.1.dylib" "$LIB_TARGET/libLBL_SenderCardItem.1.0.0.dylib"
install_name_tool -change "libLBL_HDMIChip.1.dylib" "@rpath/libLBL_HDMIChip.1.dylib" "$LIB_TARGET/libLBL_SenderCardItem.1.0.0.dylib"
install_name_tool -change "libLBL_FileTransfer.1.dylib" "@rpath/libLBL_FileTransfer.1.dylib" "$LIB_TARGET/libLBL_SenderCardItem.1.0.0.dylib"

#LBL_CommunicatEngine依赖
install_name_tool -change "libLBL_CommunicatEngine.1.dylib" "@rpath/libLBL_CommunicatEngine.1.dylib" "$LIB_TARGET/libLBL_CommunicatEngine.1.0.0.dylib"
install_name_tool -change "libLBL_Core.1.dylib" "@rpath/libLBL_Core.1.dylib" "$LIB_TARGET/libLBL_CommunicatEngine.1.0.0.dylib"

#LBL_Android依赖
install_name_tool -change "libLBL_CommunicatEngine.1.dylib" "@rpath/libLBL_CommunicatEngine.1.dylib" "$LIB_TARGET/libLBL_Android.1.0.0.dylib"
install_name_tool -change "libLBL_Android.1.dylib" "@rpath/libLBL_Android.1.dylib" "$LIB_TARGET/libLBL_Android.1.0.0.dylib"
install_name_tool -change "libLBL_Core.1.dylib" "@rpath/libLBL_Core.1.dylib" "$LIB_TARGET/libLBL_Android.1.0.0.dylib"

#LBL_SenderCard依赖
install_name_tool -change "libLBL_CommunicatEngine.1.dylib" "@rpath/libLBL_CommunicatEngine.1.dylib" "$LIB_TARGET/libLBL_SenderCard.1.0.0.dylib"
install_name_tool -change "libLBL_SenderCard.1.dylib" "@rpath/libLBL_SenderCard.1.dylib" "$LIB_TARGET/libLBL_SenderCard.1.0.0.dylib"
install_name_tool -change "libLBL_Core.1.dylib" "@rpath/libLBL_Core.1.dylib" "$LIB_TARGET/libLBL_SenderCard.1.0.0.dylib"

#LBL_ReceiveCard依赖
install_name_tool -change "libLBL_CommunicatEngine.1.dylib" "@rpath/libLBL_CommunicatEngine.1.dylib" "$LIB_TARGET/libLBL_ReceiveCard.1.0.0.dylib"
install_name_tool -change "libLBL_ReceiveCard.1.dylib" "@rpath/libLBL_ReceiveCard.1.dylib" "$LIB_TARGET/libLBL_ReceiveCard.1.0.0.dylib"
install_name_tool -change "libLBL_Core.1.dylib" "@rpath/libLBL_Core.1.dylib" "$LIB_TARGET/libLBL_ReceiveCard.1.0.0.dylib"

#LBL_HDMIChip依赖
install_name_tool -change "libLBL_CommunicatEngine.1.dylib" "@rpath/libLBL_CommunicatEngine.1.dylib" "$LIB_TARGET/libLBL_HDMIChip.1.0.0.dylib"
install_name_tool -change "libLBL_HDMIChip.1.dylib" "@rpath/libLBL_HDMIChip.1.dylib" "$LIB_TARGET/libLBL_HDMIChip.1.0.0.dylib"
install_name_tool -change "libLBL_Core.1.dylib" "@rpath/libLBL_Core.1.dylib" "$LIB_TARGET/libLBL_HDMIChip.1.0.0.dylib"

#LBL_FileTransfer依赖
install_name_tool -change "libLBL_CommunicatEngine.1.dylib" "@rpath/libLBL_CommunicatEngine.1.dylib" "$LIB_TARGET/libLBL_FileTransfer.1.0.0.dylib"
install_name_tool -change "libLBL_FileTransfer.1.dylib" "@rpath/libLBL_FileTransfer.1.dylib" "$LIB_TARGET/libLBL_FileTransfer.1.0.0.dylib"
install_name_tool -change "libLBL_Core.1.dylib" "@rpath/libLBL_Core.1.dylib" "$LIB_TARGET/libLBL_FileTransfer.1.0.0.dylib"

#Advancesettings依赖
install_name_tool -change "libLAPI_Control.1.dylib" "@rpath/libLAPI_Control.1.dylib" "$LIB_TARGET/libAdvancedsetting.1.0.0.dylib"
install_name_tool -change "libLBL_CommunicatEngine.1.dylib" "@rpath/libLBL_CommunicatEngine.1.dylib" "$LIB_TARGET/libAdvancedsetting.1.0.0.dylib"
install_name_tool -change "libLBL_SenderCardItem.1.dylib" "@rpath/libLBL_SenderCardItem.1.dylib" "$LIB_TARGET/libAdvancedsetting.1.0.0.dylib"
install_name_tool -change "libLBL_Core.1.dylib" "@rpath/libLBL_Core.1.dylib" "$LIB_TARGET/libAdvancedsetting.1.0.0.dylib"
install_name_tool -change "libLBL_Android.1.dylib" "@rpath/libLBL_Android.1.dylib" "$LIB_TARGET/libAdvancedsetting.1.0.0.dylib"
install_name_tool -change "libLBL_ReceiveCard.1.dylib" "@rpath/libLBL_ReceiveCard.1.dylib" "$LIB_TARGET/libAdvancedsetting.1.0.0.dylib"
install_name_tool -change "libLBL_SenderCard.1.dylib" "@rpath/libLBL_SenderCard.1.dylib" "$LIB_TARGET/libAdvancedsetting.1.0.0.dylib"
install_name_tool -change "libLBL_HDMIChip.1.dylib" "@rpath/libLBL_HDMIChip.1.dylib" "$LIB_TARGET/libAdvancedsetting.1.0.0.dylib"
install_name_tool -change "libLBL_FileTransfer.1.dylib" "@rpath/libLBL_FileTransfer.1.dylib" "$LIB_TARGET/libAdvancedsetting.1.0.0.dylib"

macdeployqt $TARGET_BUILD_DIR/MaxConfig.app
echo "finish install_name_tool target $UNIX_TARGET"
echo "finish $0"