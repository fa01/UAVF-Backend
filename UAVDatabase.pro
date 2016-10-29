QT += sql # this is important !

QT += core
QT -= gui

CONFIG += c++11

TARGET = UAVDatabase
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    dbmanager.cpp

HEADERS += \
    dbmanager.h
