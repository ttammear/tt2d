TEMPLATE = lib
CONFIG += staticlib c++11
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -Wall -fstack-protector

SOURCES += Source/componentmanager.cpp \
    Source/engine.cpp \
    Source/linuxplatform.cpp \
    Source/openglrenderer.cpp \
    Source/opengltexture2d.cpp \
    Source/platform.cpp \
    Source/renderer.cpp \
    Source/spriterendersystem.cpp \
    Source/textrendersystem.cpp \
    Source/texture2d.cpp \
    Source/transformsystem.cpp \
    Source/ttmath.cpp \
    Include/input.cpp \
    Source/physicssystem.cpp \
    Source/collisionsystem.cpp

HEADERS += \
    Include/componentmanager.h \
    Include/components.h \
    Include/engine.h \
    Include/linuxplatform.h \
    Include/openglrenderer.h \
    Include/opengltexture2d.h \
    Include/platform.h \
    Include/renderer.h \
    Include/shared.h \
    Include/spriterendersystem.h \
    Include/stb_image.h \
    Include/stb_truetype.h \
    Include/textrendersystem.h \
    Include/texture2d.h \
    Include/transformsystem.h \
    Include/ttmath.h \
    Include/input.h \
    Include/physicssystem.h \
    Include/collisionsystem.h

LIBS += \
    -lGL \
    -lX11 \
    -lGLEW \
    -lfreetype

INCLUDEPATH += \
    /usr/include/freetype2 \
    Include \
    lib
