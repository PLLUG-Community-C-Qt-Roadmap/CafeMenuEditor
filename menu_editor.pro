#-------------------------------------------------
#
# Project created by QtCreator 2015-04-28T18:21:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = menu_editor
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    consoleprintmenuvisitor.cpp \
    composite.cpp \
    menu.cpp \
    menuitem.cpp \
    menuiterator.cpp \
    texteditprintmenuvisitor.cpp \
    menucombobox.cpp \
    editordelegate.cpp \
    adddialog.cpp

HEADERS  += mainwindow.h \
    consoleprintmenuvisitor.h \
    composite.h \
    menu.h \
    menuitem.h \
    menuiterator.h \
    menuvisitor.h \
    texteditprintmenuvisitor.h \
    menucombobox.h \
    editordelegate.h \
    adddialog.h

FORMS    += mainwindow.ui \
    editordelegate.ui \
    adddialog.ui
