#-------------------------------------------------
#
# Project created by QtCreator 2017-02-11T11:25:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SmsSending
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
    src/smssending.cpp \
    src/logger/logger.cpp \
    src/forTest/ethreads.cpp \
    src/lib/serialport/commthread.cpp \
    src/lib/serialport/seriallistener.cpp \
    src/gts5260/gts5260smsentry.cpp \
    src/smsmodule/smsmodulemessageheadred.cpp \
    src/smsmodule/smsmodulemessagecommon.cpp \
    src/gts5260/gts5260smsmodule.cpp

HEADERS  += src/smssending.h \
    src/logger/logger.h \
    src/lib/singletone/call_once.h \
    src/lib/singletone/singleton.h \
    src/lib/logging/log.h \
    src/forTest/ethreads.h \
    src/lib/serialport/commthread.h \
    src/lib/serialport/seriallistener.h \
    src/gts5260/gts5260smsentry.h \
    src/smsmodule/smsmodulemessageheadred.h \
    src/smsmodule/ismsmodule.h \
    src/smsmodule/smsmodulemessagecommon.h \
    src/gts5260/gts5260smsmodule.h

FORMS    += src/smssending.ui
