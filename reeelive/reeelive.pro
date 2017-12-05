#-------------------------------------------------
#
# Project created by QtCreator 2016-08-05T18:10:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = reeelive
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    videoinitialize.cpp \
    inputfile.cpp \
    rsvideoasset.cpp \
    packagequeue.cpp \
    demux.cpp

HEADERS  += mainwindow.h \
    ffmpeg_const.h \
    videoinitialize.h \
    inputfile.h \
    rsvideoasset.h \
    packagequeue.h \
    demux.h

FORMS    += mainwindow.ui


INCLUDEPATH +=  -framework CoreFoundation
INCLUDEPATH +=/Users/guanweidong/qtworkspace/qtTest/thrid/libffmpeg/include
INCLUDEPATH +=/Users/guanweidong/qtworkspace/qtTest/thrid/libfaac/include
INCLUDEPATH +=/Users/guanweidong/qtworkspace/qtTest/thrid/libx264/include
LIBS += -L/Users/guanweidong/qtworkspace/qtTest/thrid/libffmpeg/lib/ -lavcodec \
        -L/Users/guanweidong/qtworkspace/qtTest/thrid/libffmpeg/lib/ -lavformat \
        -L/Users/guanweidong/qtworkspace/qtTest/thrid/libffmpeg/lib/ -lavdevice \
        -L/Users/guanweidong/qtworkspace/qtTest/thrid/libffmpeg/lib/ -lavfilter \
        -L/Users/guanweidong/qtworkspace/qtTest/thrid/libffmpeg/lib/ -lavutil \
        -L/Users/guanweidong/qtworkspace/qtTest/thrid/libffmpeg/lib/ -lswscale \
        -L/Users/guanweidong/qtworkspace/qtTest/thrid/libffmpeg/lib/ -lswresample \
        -L/Users/guanweidong/qtworkspace/qtTest/thrid/libfaac/lib/ -lfaac \
        -L/Users/guanweidong/qtworkspace/qtTest/thrid/libx264/lib/ -lx264 \
        -lz -lbz2 -lobjc -llzma -liconv  \
        -framework CoreFoundation \
        -framework QuartzCore \
        -framework CoreMedia \
        -framework CoreVideo \
        -framework VideoToolbox \
        -framework VideoDecodeAcceleration \
        -framework Security
