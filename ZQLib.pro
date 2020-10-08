TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    Exception.cpp \
    Object.cpp \
    MyString.cpp

HEADERS += \
    Exception.h \
    Object.h \
    List.h \
    Array.h \
    Pointer.h \
    Stack.h \
    Queue.h \
    MyString.h
