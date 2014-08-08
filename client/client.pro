#-------------------------------------------------
#
# Project created by QtCreator 2014-08-07T11:29:27
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = light_client
TEMPLATE = app


SOURCES += main.cpp \
    settingsdialog.cpp \
    lightdialog.cpp \
    application.cpp \
    parser.cpp

HEADERS  += \
    settingsdialog.h \
    lightdialog.h \
    application.h \
    parser.h

FORMS    += \
    settingsdialog.ui \
    lightdialog.ui

MOC_DIR = .moc
OBJECTS_DIR = .obj
