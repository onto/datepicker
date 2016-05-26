
QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS += \
    $$PWD/datepicker/datepicker_common.h \
    $$PWD/datepicker/datepicker.h \
    $$PWD/datepicker/datepickerpopupfooter.h \
    $$PWD/datepicker/datepickerpopup.h \
    $$PWD/datepicker/datepickercalendar.h \
    $$PWD/datepicker/datepickercalendarnavigator.h \
    $$PWD/datepicker/datepickercalendarmonthview.h \
    $$PWD/datepicker/datepickercalendaryearview.h \
    $$PWD/datepicker/datepickercalendardecadeview.h \
    $$PWD/datepicker/datepickerabstractformater.h \
    $$PWD/datepicker/datepickerstandardformater.h \
    $$PWD/datepicker/datepickerhumanreadableformater.h \
    $$PWD/datepicker/datepickertimeedit.h

SOURCES += \
    $$PWD/datepicker_common.cpp \
    $$PWD/datepicker.cpp \
    $$PWD/datepickerpopupfooter.cpp \
    $$PWD/datepickerpopup.cpp \
    $$PWD/datepickercalendar.cpp \
    $$PWD/datepickercalendarnavigator.cpp \
    $$PWD/datepickercalendarmonthview.cpp \
    $$PWD/datepickercalendaryearview.cpp \
    $$PWD/datepickercalendardecadeview.cpp \
    $$PWD/datepickerabstractformater.cpp \
    $$PWD/datepickerstandardformater.cpp \
    $$PWD/datepickerhumanreadableformater.cpp \
    $$PWD/datepickertimeedit.cpp


