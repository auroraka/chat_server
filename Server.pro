#-------------------------------------------------
#
# Project created by QtCreator 2015-09-07T10:07:31
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Server
TEMPLATE = app


SOURCES += main.cpp\
        server.cpp \
    tcp.cpp \
    environment.cpp \
    userinfo.cpp

HEADERS  += server.h \
    tcp.h \
    enviroment.h \
    userinfo.h

FORMS    += server.ui


CONFIG += c++11
