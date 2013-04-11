#-------------------------------------------------
#
# Project created by QtCreator 2012-05-11T20:32:54
#
#-------------------------------------------------

QT       += network xml

TARGET = messy
TEMPLATE = lib

DEFINES += LIBMESSY_LIBRARY

SOURCES += libmessy.cpp \
    messy.cpp \
    ordershandler.cpp \
    orderhandler.cpp \
    order.cpp \
    orderresponsehandler.cpp

HEADERS += libmessy.h\
        libmessy_global.h \
    messy.h \
    ordershandler.h \
    orderhandler.h \
    order.h \
    orderresponsehandler.h

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE752BFEB
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = libmessy.dll
    addFiles.path = !:/sys/bin
    DEPLOYMENT += addFiles
}

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
