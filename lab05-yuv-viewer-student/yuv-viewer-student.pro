QT = core
QT += widgets
QT += gui

TARGET = yuv-viewer-student
TEMPLATE = app


SOURCES += \
  main.cpp \
  mainwindow.cpp \
  checkerimage.cpp \
  triangleimage.cpp \
  yuvimage.cpp

HEADERS  += \
  imageparams.h \
  mainwindow.h \
  checkerimage.h \
  triangleimage.h \
  yuvimage.h \
  util.h

QMAKE_CXXFLAGS += -std=c++20
