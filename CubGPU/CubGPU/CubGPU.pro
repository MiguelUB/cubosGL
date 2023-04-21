#-------------------------------------------------
#
# Project created by QtCreator 2021-02-07T16:04:09
#
#-------------------------------------------------

QT       += core gui opengl

TARGET = CubGPU
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

HEADERS  += mainwindow.h \
    vec.h \
    mat.h \
    glwidget.h \
    cub.h \
    Common.h

FORMS    += mainwindow.ui

OTHER_FILES += \
    vshader1.glsl \
    fshader1.glsl

RESOURCES += \
    resources.qrc







