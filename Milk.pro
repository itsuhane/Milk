#-------------------------------------------------
#
# Project created by QtCreator 2012-06-11T15:32:18
#
#-------------------------------------------------

QT += core gui opengl script

TARGET = Milk
TEMPLATE = app

RC_FILE = milk.rc

INCLUDEPATH += ../libmmd/include

SOURCES += main.cpp\
        milkmainwindow.cpp \
    glwidget.cpp \
    timelinewidget.cpp \
    timelinetree/timelinetreeview.cpp \
    timelinetree/timelinetreeruler.cpp \
    timelinetree/timelinetreemodel.cpp \
    timelinetree/timelinetreeitem.cpp \
    timelinetree/timelinetreedelegate.cpp \
    timelinetree/timeline.cpp \
    milkprojectmodel/milkprojectmodel.cpp \
    milkprojectmodel/milkcamera.cpp

HEADERS  += milkmainwindow.h \
    glwidget.h \
    timelinewidget.h \
    timelinetree/timelinetreeview.h \
    timelinetree/timelinetreeruler.h \
    timelinetree/timelinetreemodel.h \
    timelinetree/timelinetreeitem.h \
    timelinetree/timelinetreedelegate.h \
    timelinetree/timelinetreeconfig.h \
    timelinetree/timeline.h \
    milkprojectmodel/milkprojectmodel.h \
    milkprojectmodel/milkcamera.h

RESOURCES += \
    MilkResources.qrc

OTHER_FILES += \
    ui/style.qss \
    milk.rc
