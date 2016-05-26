include(../../datepicker.pri)
include(source/datepicker.pri)

TEMPLATE = lib
VERSION = 0.1.0
TARGET = $$DATEPICKER_LIBRARY_NAME

CONFIG += static

CODECFORSRC = UTF-8

DEFINES += DATEPICKER_LIBRARY_ENABLE DATEPICKER_LIBRARY

target.path = $$INSTALL_PREFIX/lib
headers.path = $$INSTALL_PREFIX/include/$$DATEPICKER_LIBRARY_NAME
headers.files = \
    source/datepicker/datepicker_common.h \
    source/datepicker/datepicker.h \
    source/datepicker/datepickerabstractformater.h \
    source/datepicker/datepickerstandardformater.h \
    source/datepicker/datepickerhumanreadableformater.h

INSTALLS = target headers
