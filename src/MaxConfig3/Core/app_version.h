#pragma once

namespace Core {
    namespace Constants {

    #define STRINGIFY_INTERNAL(x) #x
    #define STRINGIFY(x) STRINGIFY_INTERNAL(x)

    const char IDE_DISPLAY_NAME[] = "MaxConfig";
    const char IDE_ID[] = "maxconfig";
    const char IDE_CASED_ID[] = "MaxConfig";

    #define IDE_VERSION 3.0.8
    #define IDE_VERSION_STR STRINGIFY(IDE_VERSION)
    #define IDE_VERSION_DISPLAY_DEF 3.0.8
    #define IDE_VERSION_COMPAT_DEF 3.0.0

    #define IDE_VERSION_MAJOR 3
    #define IDE_VERSION_MINOR 0
    #define IDE_VERSION_RELEASE 8

    const char IDE_VERSION_LONG[]      = IDE_VERSION_STR;
    const char IDE_VERSION_DISPLAY[]   = STRINGIFY(IDE_VERSION_DISPLAY_DEF);
    const char IDE_VERSION_COMPAT[]    = STRINGIFY(IDE_VERSION_COMPAT_DEF);
    const char IDE_AUTHOR[]            = "The CVTE Company Ltd";
    const char IDE_YEAR[]              = "2021";

    #undef IDE_VERSION_COMPAT_DEF
    #undef IDE_VERSION_DISPLAY_DEF
    #undef IDE_VERSION
    #undef IDE_VERSION_STR
    #undef STRINGIFY
    #undef STRINGIFY_INTERNAL

    } // Constants
} // Core
