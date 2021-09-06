!isEmpty(MAXCONFIG_PRI_INCLUDED):error("MaxConfig.pri already included")
MAXCONFIG_PRI_INCLUDED = 1

include($$PWD/MaxConfig_branding.pri)
!isEmpty(IDE_BRANDING_PRI): include($$IDE_BRANDING_PRI)

#VERSION = $$MAXCONFIG_VERSION

CONFIG += c++14

# For lib TargetName Replace, (e.g. LBL_Cored/LBL_Core_debug)
defineReplace(qtLibraryTargetName) {
   unset(LIBRARY_NAME)
   LIBRARY_NAME = $$1
   CONFIG(debug, debug|release) {
      !debug_and_release|build_pass {
          mac:RET = $$member(LIBRARY_NAME, 0)_debug
              else:win32:RET = $$member(LIBRARY_NAME, 0)d
      }
   }
   isEmpty(RET):RET = $$LIBRARY_NAME
   return($$RET)
}

# For lib Name Replace, (e.g. LBL_Cored3)
defineReplace(qtLibraryName) {
   RET = $$qtLibraryTargetName($$1)
   win32 {
      VERSION_LIST = $$split(MAXCONFIG_VERSION, .)
      RET = $$RET$$first(VERSION_LIST)
   }
   return($$RET)
}

defineTest(minQtVersion) {
    maj = $$1
    min = $$2
    patch = $$3
    isEqual(QT_MAJOR_VERSION, $$maj) {
        isEqual(QT_MINOR_VERSION, $$min) {
            isEqual(QT_PATCH_VERSION, $$patch) {
                return(true)
            }
            greaterThan(QT_PATCH_VERSION, $$patch) {
                return(true)
            }
        }
        greaterThan(QT_MINOR_VERSION, $$min) {
            return(true)
        }
    }
    greaterThan(QT_MAJOR_VERSION, $$maj) {
        return(true)
    }
    return(false)
}

# For use in custom compilers which just copy files
defineReplace(stripSrcDir) {
    return($$relative_path($$absolute_path($$1, $$OUT_PWD), $$_PRO_FILE_PWD_))
}


isEmpty(PRO_LIBRARY_BASENAME) {
    PRO_LIBRARY_BASENAME = lib
}

PRO_SOURCE_TREE = $$PWD
isEmpty(PRO_BUILD_TREE) {
    sub_dir = $$_PRO_FILE_PWD_
    sub_dir ~= s,^$$re_escape($$PWD),,
    PRO_BUILD_TREE = $$clean_path($$OUT_PWD)
    PRO_BUILD_TREE ~= s,$$re_escape($$sub_dir)$,,
}

PRO_APP_PATH = $$PRO_BUILD_TREE/bin

osx{

}else{
    PRO_APP_TARGET   = $$PRO_ID
    # target output path if not set manually
    isEmpty(PRO_OUTPUT_PATH): PRO_OUTPUT_PATH = $$PRO_BUILD_TREE
	
    PRO_LIBRARY_PATH = $$PRO_OUTPUT_PATH/$$PRO_LIBRARY_BASENAME/$$PRO_APP_TARGET
    PRO_PLUGIN_PATH  = $$PRO_LIBRARY_PATH/plugins
    PRO_DATA_PATH    = $$PRO_OUTPUT_PATH/share/$$PRO_APP_TARGET
    PRO_DOC_PATH     = $$PRO_OUTPUT_PATH/share/doc/$$PRO_APP_TARGET
    PRO_BIN_PATH     = $$PRO_OUTPUT_PATH/bin

}

INCLUDEPATH += \
    $$PRO_BUILD_TREE/src \ # for <app/app_version.h> in case of actual build directory
    $$PRO_SOURCE_TREE/src \ # for <app/app_version.h> in case of binary package with dev package
    $$PRO_SOURCE_TREE/src/libs #for other files that are not plug-ins

LBUSINESSLIB_INCLUDE= $$PRO_SOURCE_TREE/include/LBusinessLib
INCLUDEPATH += $$LBUSINESSLIB_INCLUDE

exists($$PRO_LIBRARY_PATH): LIBS *= -L$$PRO_LIBRARY_PATH  # MaxConfig library path from output path

QTC_LIB_DIRS += $$PRO_SOURCE_TREE/src
#LBusiness library path
QTC_LIB_DIRS += $$PRO_SOURCE_TREE/src/LBusinessLib
QTC_LIB_DIRS += $$PRO_SOURCE_TREE/src/LBusinessLib/LBL_Control

# recursively resolve library deps
done_libs =
for(ever) {
    isEmpty(QTC_LIB_DEPENDS): \
        break()
    done_libs += $$QTC_LIB_DEPENDS
    for(dep, QTC_LIB_DEPENDS) {
        dependencies_file =
        for(dir, QTC_LIB_DIRS) {
            exists($$dir/$$dep/$${dep}_dependencies.pri) {
                dependencies_file = $$dir/$$dep/$${dep}_dependencies.pri
                break()
            }
        }
        isEmpty(dependencies_file): \
            error("Library dependency $$dep not found")
        include($$dependencies_file)
        LIBS += -l$$qtLibraryTargetName($$QTC_LIB_NAME)
    }
    QTC_LIB_DEPENDS = $$unique(QTC_LIB_DEPENDS)
    QTC_LIB_DEPENDS -= $$unique(done_libs)
}