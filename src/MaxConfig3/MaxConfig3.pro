include($$replace(_PRO_FILE_PWD_, ([^/]+$), \\1/\\1_dependencies.pri))
include(../../MaxConfig.pri)
include(MaxConfig3.pri)

QT += core gui serialport network opengl openglextensions printsupport
QT += concurrent
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TEMPLATE = app
CONFIG += c++11
RC_ICONS = Resources/Normal/MaxConfig.ico
TARGET = $$PRO_APP_TARGET
DESTDIR = $$PRO_APP_PATH

INCLUDEPATH += $$nativePath($$LBUSINESSLIB_INCLUDE/LAPI_Control)
INCLUDEPATH += $$nativePath($$LBUSINESSLIB_INCLUDE/LBL_SenderCardItem)
INCLUDEPATH += $$nativePath($$LBUSINESSLIB_INCLUDE/LBL_CommunicatEngine)
INCLUDEPATH += $$nativePath($$LBUSINESSLIB_INCLUDE/LBL_Control)
INCLUDEPATH += $$nativePath($$LBUSINESSLIB_INCLUDE/LBL_Core)
INCLUDEPATH += $$nativePath($$LBUSINESSLIB_INCLUDE/LBL_Advanced)

exists (../../.git) {
    GIT_BRANCH   = $$system(git rev-parse --abbrev-ref HEAD)
    GIT_SHA      = $$system(git rev-parse --short=8 HEAD)
    GIT_TIME     = $$system(git log --pretty=format:\"%cd\" --date=format:\"%Y%m%d-%H%M%S\" -1 HEAD)

    GIT_BUILD_INFO = "$${GIT_SHA}-$${GIT_TIME}"
} else {
    GIT_BRANCH         = --
    GIT_SHA            = --
    GIT_TIME           = --
    GIT_BUILD_INFO     = --
}
#message(git branch = $$GIT_BRANCH)
message(git time = $$GIT_TIME)
#message(git build info = $$GIT_BUILD_INFO)
message(git sha = $$GIT_SHA)

DEFINES += GIT_BUILD_SHA=\"\\\"$$GIT_SHA\\\"\"
DEFINES += GIT_BUILD_TIME=\"\\\"$$GIT_TIME\\\"\"


#Param Path Copy
include(../../shard/function.prf)
PRO_SOURCE_SHARD = $$PRO_SOURCE_TREE/shard

ParamSrcFilePath += \
    $$PRO_SOURCE_SHARD/Parameter

for(path, ParamSrcFilePath) {
        sub_dir = $$path
        sub_dir ~= s,^$$re_escape($$PRO_SOURCE_SHARD),,
        paramSrcDir  = $$path/*
        paramDestDir = $$clean_path($$PRO_BIN_PATH$$sub_dir)
        copyDir($$nativePath($$paramSrcDir), $$nativePath($$paramDestDir))
        message(src = $$nativePath($$paramSrcDir))
        message(dest = $$nativePath($$paramDestDir))
}

#sfSrcFile = $$PRO_SOURCE_TREE/shard/Parameter/*
#sfSrcFile = $$replace(sfSrcFile, /, \\)

#sfDestDir = $$PRO_BIN_PATH/Parameter
#sfDestDir = $$replace(sfDestDir, /, \\)
#QMAKE_PRE_LINK += echo d | xcopy /y $$sfSrcFile $$sfDestDir # 拷贝shard/Parameter下的所有文件到目标文件目录


## get-version-from-git.pri
## 版本号构成 MAJAR_NUMBER.MINOR_NUMBER.CHANGE_NUMBER.BUILD_NUMBER
#message(/**************[START] reading app version**************/)

#MAJAR_NUMBER = 0
#MINOR_NUMBER = 0
#CHANGE_NUMBER = 0
#BUILD_NUMBER = 0

## 从git分支名中，读取 大、中、小版本。若当前分支不是发布分支，将尝试从最近git标签中读取。
#exists(../../../.git) {

##git提交数作为构建版本号。
#    BUILD_NUMBER = $$system(git rev-list HEAD --count)

##git分支名称
#    #GIT_BRANCH = $$system(git symbolic-ref --short -q HEAD)
#    GIT_BRANCH="release/v3.0.8"
#    message(git branch = $$GIT_BRANCH)
#    GIT_BRANCH_PREFIX = $$str_member($$GIT_BRANCH,0,7)
#    message(git branch = $$GIT_BRANCH_PREFIX)
#    equals(GIT_BRANCH_PREFIX,"release/"){
#        VERSION_NUMBER_STRING = $$replace(GIT_BRANCH,[^0-9+|\.],"")
#        VERSION_NUMBER_LIST = $$split(VERSION_NUMBER_STRING,".")
#        VERSION_NUMBER_LIST_SIZE = $$size(VERSION_NUMBER_LIST)
#    }else{
#        message("current git branch is not release branch, release branch name should start withs 'release/'.")
#    }

#    lessThan(VERSION_NUMBER_LIST_SIZE,3){
#        message("can not read version from git branch name, try to read version from nearest git tag.")
#        GIT_NEAREST_TAG = $$system(git describe --tags)
#        message(git nearest number = $$GIT_NEAREST_TAG)
#        VERSION_NUMBER_STRING = $$replace(GIT_NEAREST_TAG,[^0-9+|\.],"")
#        VERSION_NUMBER_LIST = $$split(VERSION_NUMBER_STRING,".")
#        VERSION_NUMBER_LIST_SIZE = $$size(VERSION_NUMBER_LIST)
#    }
#    greaterThan(VERSION_NUMBER_LIST_SIZE,2){
#        MAJAR_NUMBER = $$member(VERSION_NUMBER_LIST,0)
#        MINOR_NUMBER = $$member(VERSION_NUMBER_LIST,1)
#        CHANGE_NUMBER = $$member(VERSION_NUMBER_LIST,2)
#        VERSION = $$MAJAR_NUMBER"."$$MINOR_NUMBER"."$$CHANGE_NUMBER"."$$BUILD_NUMBER
#        system(echo "VERSION=$$VERSION">../../MaxConfig_branding.pri)
#    }else{
#        include(version.pri)
#        message("can not read version from git! using version.pri")
#    }
#} else {
#    include(version.pri)
#    message("can not read version from git! using version.pri")
#}
#message(majar number = $$MAJAR_NUMBER)
#message(minor number = $$MINOR_NUMBER)
#message(change number = $$CHANGE_NUMBER)
#message(build number = $$BUILD_NUMBER)
#message(app version = $$VERSION)
#message(/***************[END] reading app version***************/)
