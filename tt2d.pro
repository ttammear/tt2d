TEMPLATE = lib
CONFIG += static
CONFIG += staticlib
CONFIG += c++11

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
    Source/collisionsystem.cpp \
    Source/shader.cpp \
    Source/openglshader.cpp \
    Source/windowsplatform.cpp \
    Source/tt2d.cpp

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
    Include/collisionsystem.h \
    Include/shader.h \
    Include/openglshader.h \
    Include/windowsplatform.h \
    Include/wglext.h \
    Include/tt2d.h

INCLUDEPATH += \
    /usr/include/freetype2 \
    ../glew/include/ \
    ../freetype/include/ \
    ../freetype/include/freetype2/ \
    Include \
    lib

win32:LIBPATH += ../glew/lib/Debug/x64
win32:LIBPATH += ../freetype/objs/vc2010/x64
win32:LIBS += -lglew32d
win32:LIBS += OpenGL32.lib
win32:LIBS += freetype27d.lib

unix:LIBS += -lGL
unix:LIBS += -lGLEW
unix:LIBS += -lX11
unix:LIBS += -lfreetype
