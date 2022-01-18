#pragma once

namespace Core {
    namespace Constants {

    #define STRINGIFY_INTERNAL(x) #x
    #define STRINGIFY(x) STRINGIFY_INTERNAL(x)

    const char IDE_DISPLAY_NAME[] = "MaxConfig";
    const char IDE_ID[] = "maxconfig";
    const char IDE_CASED_ID[] = "MaxConfig";

    #define IDE_VERSION DEF_MAXCONFIG_VERSION
    #define IDE_VERSION_DISPLAY_DEF DEF_MAXCONFIG_DISPLAY_VERSION
    #define IDE_VERSION_COMPAT_DEF DEF_MAXCONFIG_COMPAT_VERSIO
    #define IDE_VERSION_COPYRIGHT_YEAR DEF_MAXCONFIG_COPYRIGHT_YEAR

    #define IDE_VERSION_MAJOR STRINGIFY(DEF_MAXCONFIG_VERSION_MAJOR)
    #define IDE_VERSION_MINOR STRINGIFY(DEF_MAXCONFIG_VERSION_MINOR)
    #define IDE_VERSION_RELEASE STRINGIFY(DEF_MAXCONFIG_VERSION_RELEASE)

    const char IDE_VERSION_LONG[]      = IDE_VERSION;
    const char IDE_VERSION_DISPLAY[]   = IDE_VERSION_DISPLAY_DEF;
    const char IDE_VERSION_COMPAT[]    = IDE_VERSION_COMPAT_DEF;
    const char IDE_AUTHOR[]            = "The CVTE Company Ltd";
    const char IDE_YEAR[]              = IDE_VERSION_COPYRIGHT_YEAR;

    #undef IDE_VERSION_COMPAT_DEF
    #undef IDE_VERSION_DISPLAY_DEF
    #undef IDE_VERSION
    #undef IDE_VERSION_STR
    #undef STRINGIFY
    #undef STRINGIFY_INTERNAL

    } // Constants
} // Core
