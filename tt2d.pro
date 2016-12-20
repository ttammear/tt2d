TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    renderer.cpp \
    linuxplatform.cpp \
    platform.cpp \
    engine.cpp \
    ttmath.cpp \
    texture2d.cpp \
    opengltexture2d.cpp \
    componentmanager.cpp \
    spriterendersystem.cpp \
    system.cpp \
    transformsystem.cpp

HEADERS += \
    platform.h \
    renderer.h \
    main.h \
    shared.h \
    linuxplatform.h \
    engine.h \
    ttmath.h \
    components.h \
    texture2d.h \
    opengltexture2d.h \
    componentmanager.h \
    spriterendersystem.h \
    system.h \
    transformsystem.h

LIBS += \
    -lGL \
    -lX11 \
    -lGLEW
