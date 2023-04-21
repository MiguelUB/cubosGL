#-------------------------------------------------
#
# Project created by QtCreator 2021-02-06T11:51:14
#
#-------------------------------------------------

QT       += core gui

TARGET = CubGL
TEMPLATE = app

contains(QT_ARCH, i386) {
    INCLUDEPATH += "./IncludeWin32/"
    LIBS += -L"$$_PRO_FILE_PWD_/libWin32/" -lglut32
}

SOURCES += main.cpp\
    mainwindow.cpp \
    glwidget.cpp \
    cub.cpp \
    Common.cpp

HEADERS  += \
    mainwindow.h \
    glwidget.h \
    cub.h \
    Common.h \
    vec.h \
    mat.h

QT           += opengl
QT           += widgets
# install

sources.files = $$SOURCES $$HEADERS $$RESOURCES $$FORMS CubGL.pro
INSTALLS +=  sources

OTHER_FILES += \
    README.txt





























