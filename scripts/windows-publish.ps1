#!/bin/pwsh
[CmdletBinding()]
param (
    [string] $QT_INSTALL_BINS, [string] $TARGET_BUILD_DIR, [string] $PRODUCT_NAME, [string] $APP_VERSION
)

$scriptDir = $PSScriptRoot
$currentDir = Get-Location
$APP_NAME = $PRODUCT_NAME + '.exe'
Write-Host "appname:" $APP_NAME
Write-Host "currentDir:" $currentDir
Write-Host "scriptDir:" $scriptDir

function Main() {

    #New-Item -ItemType Directory $TARGET_BUILD_DIR
    # 拷贝依赖
    cd $QT_INSTALL_BINS
    ./windeployqt --plugindir $TARGET_BUILD_DIR\plugins --compiler-runtime --no-system-d3d-compiler $TARGET_BUILD_DIR\$APP_NAME
    ./windeployqt --plugindir $TARGET_BUILD_DIR\plugins --no-translations --compiler-runtime --no-system-d3d-compiler $TARGET_BUILD_DIR\LBL_CommunicatEngine.dll
    # 删除不必要的文件
    $excludeList = @("*.qmlc", "*.ilk", "*.exp", "*.lib", "*.pdb")
    Remove-Item -Path $TARGET_BUILD_DIR -Include $excludeList -Recurse -Force
    # 拷贝vcRedist dll
    #$redistDll="{0}{1}\*.CRT\*.dll" -f $env:vcToolsRedistDir.Trim(),$env:msvcArch
    #Copy-Item $redistDll $TARGET_BUILD_DIR\
    # 拷贝WinSDK dll
    #$sdkDll="{0}Redist\{1}ucrt\DLLs\{2}\*.dll" -f $env:winSdkDir.Trim(),$env:winSdkVer.Trim(),$env:msvcArch
    #Copy-Item $sdkDll $TARGET_BUILD_DIR\
    # 打包zip
	$ParentPath = (get-item $TARGET_BUILD_DIR ).parent.FullName;
    Compress-Archive -Path $TARGET_BUILD_DIR\* $ParentPath\$PRODUCT_NAME$APP_VERSION'.zip' -Force
}

if ($null -eq $TARGET_BUILD_DIR -or $null -eq $PRODUCT_NAME) {
    Write-Host "args missing, TARGET_BUILD_DIR is" $TARGET_BUILD_DIR ", PRODUCT_NAME is" $PRODUCT_NAME
    return
}
Main



