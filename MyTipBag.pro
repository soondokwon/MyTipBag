#-------------------------------------------------
#
# Project created by QtCreator 2015-10-20T11:30:13
#
#-------------------------------------------------
DEPLOYMENT.display_name=MyTipBag

VERSION=2015.10.20.1
QMAKE_TARGET_COMPANY=GreateStone
QMAKE_TARGET_PRODUCT=MyTipBag
QMAKE_TARGET_DESCRIPTION=Tip management program.
QMAKE_TARGET_COPYRIGHT=(c) copy right GreateStone

CONFIG += release_build

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyTipBag
TEMPLATE = app

QMAKE_CXXFLAGS_WARN_ON += -Wno-reorder

SOURCES += main.cpp\
        mainwindow.cpp \
    highlighter.cpp \
    codeeditor.cpp \
    categorydialog.cpp \
    addnewitemdialog.cpp

HEADERS  += mainwindow.h \
    highlighter.h \
    codeeditor.h \
    categorydialog.h \
    addnewitemdialog.h

FORMS    += mainwindow.ui \
    categorydialog.ui \
    addnewitemdialog.ui

RESOURCES += \
    resource.qrc

# setting exe icon
RC_ICONS=MyTipBag.ico

release_build {
    message( "===========release build...=============" )
    # Remove all Qt's checking code, and all Q_ASSERT().
    # *BUT* still do Q_CHECK_PTR !
    DEFINES += QT_NO_DEBUG QT_NO_CHECK QT_CHECK_NULL

    # when win32 build
    # gcc, g++
    win32 {
        QMAKE_LFLAGS     = -static -static-libgcc
        QMAKE_LFLAGS_DLL = -static
    }
}
