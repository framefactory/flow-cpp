QMAKE_CXX = clang++
QMAKE_CC = clang
CONFIG += c++11
#QMAKE_CXXFLAGS += -std=c++0x
#QMAKE_CXXFLAGS += --gcc-toolchain=/usr/lib/gcc/x86_64-linux-gnu/4.8

DESTDIR = bin
OBJECTS_DIR = obj

TARGET = FlowCore
TEMPLATE = lib
DESTDIR = bin
CONFIG += staticlib
CONFIG += release
VERSION = 0.0.1

QT += core

HEADERS += src/FlowCore/*.h
SOURCES += src/FlowCore/*.cpp

INCLUDEPATH += src
