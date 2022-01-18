#!/bin/pwsh
[CmdletBinding()]
param (
    [string] $TARGET_BUILD_DIR, [string] $PRODUCT_NAME, [string] $APP_VERSION
)
 
$ScriptDir = $PSScriptRoot
$PRODUCT_PATH = (get-item $ScriptDir ).parent.FullName;

$Package_Name = $PRODUCT_NAME + $APP_VERSION + '_Setup_offline.exe'

$QtIFWDir = $PRODUCT_PATH + '/packaging/windows/bin'
$Package_Config_Path = $PRODUCT_PATH + '/packaging/windows/config'
$Package_Packages_Path = $PRODUCT_PATH + '/packaging/windows/packages/org.qstech.maxconfig'

$Config_Xml = $Package_Config_Path + '/config.xml'
$Package_Xml = $Package_Packages_Path + '/meta/package.xml'

Write-Host "ScriptDir:" $ScriptDir
Write-Host "ProductDir:" $PRODUCT_PATH
Write-Host "PackageName" $Package_Name

function Main() {

	Write-Host "Setting Package MaxConfig..."
	Write-Host "Version" $APP_VERSION 
	
	Write-Host "Set QtIFW Bin Path..."
	Write-Host "QtIFWDir" $QtIFWDir
	$env:PATH=$QtIFWDir
	
	Write-Host "Copying App Data..."
	if([io.Directory]::Exists($Package_Packages_Path+ '/data')){
		Remove-Item $Package_Packages_Path/data -recurse
	}
	New-Item -ItemType Directory $Package_Packages_Path/data
	Copy-Item $TARGET_BUILD_DIR/* $Package_Packages_Path/data -recurse
	
	Write-Host "Update Version..."
	#using xml
	$xmlConfig = [xml](Get-Content $Config_Xml)
	$xmlConfigPath = Convert-Path $Config_Xml
	$xmlConfig.Installer.Version = $APP_VERSION
	$xmlConfig.Save($xmlConfigPath)
	
	$xmlPackage = [xml](Get-Content $Package_Xml)
	$xmlPackagePath = Convert-Path $Package_Xml
	$xmlPackage.Package.Version = $APP_VERSION
	$today = Get-Date
	$xmlPackage.Package.ReleaseDate = $today.ToString('yyyy-MM-dd')
	$xmlPackage.Save($xmlPackagePath)
	
	Write-Host "Build Setup Package..."
	$BuildParentPath = (get-item $TARGET_BUILD_DIR ).parent.FullName;
	binarycreator.exe --offline-only -c $Config_Xml -p $PRODUCT_PATH/packaging/windows/packages $BuildParentPath/$Package_Name -v
	Write-Host "Package Success..."
	
	Write-Host "Creat OnlineUpdate Repo..."
	if([io.Directory]::Exists($BuildParentPath + '/updateRepo')){
		Remove-Item $BuildParentPath/updateRepo -recurse
	}
	New-Item -ItemType Directory $BuildParentPath/updateRepo
	repogen.exe -p $PRODUCT_PATH/packaging/windows/packages $BuildParentPath/updateRepo
	Write-Host "Creat Repo Success..."
	
	Write-Host "Package:" $BuildParentPath/$Package_Name
	Write-Host "Repo:" $BuildParentPath/updateRepo
}

if ($null -eq $TARGET_BUILD_DIR -or $null -eq $PRODUCT_NAME) {
    Write-Host "args missing, TARGET_BUILD_DIR is" $TARGET_BUILD_DIR ", PRODUCT_NAME is" $PRODUCT_NAME
    return
}
Main

