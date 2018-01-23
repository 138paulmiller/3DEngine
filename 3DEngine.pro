TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lSDL2 -lSDL2main -lGL -lGLEW

SOURCES = $$files(src/*.cpp, true)

HEADERS = $$files(src/*.h, true) \
          $$files(src/*.hpp, true)

OTHER_FILES += Makefile

MAKEFILE = Makefile

OTHER_FILES += \
     $$files(res/*, true)

DISTFILES += $$files(glsl/*, true)
