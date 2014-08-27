#-------------------------------------------------
#
# Project created by QtCreator 2014-08-07T11:32:33
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = light_server
TEMPLATE = app


SOURCES += main.cpp \
    senddialog.cpp \
    server.cpp

HEADERS  += \
    senddialog.h \
    server.h

FORMS    += \
    senddialog.ui

MOC_DIR = .moc
OBJECTS_DIR = .obj
