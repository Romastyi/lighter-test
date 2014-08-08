TARGET = light_test
TEMPLATE = app
QT -= gui
QT += testlib
CONFIG += console
CONFIG -= app_bundle

SOURCES += \
    main.cpp \
    ../client/parser.cpp

HEADERS += \
    ../client/parser.h

MOC_DIR = .moc
OBJECTS_DIR = .obj
