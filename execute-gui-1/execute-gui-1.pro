#-------------------------------------------------
#
# Project created by QtCreator 2015-11-22T14:55:53
#
#-------------------------------------------------

QT  += core gui
QT  += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = execute-gui-1
TEMPLATE = app

INCLUDEPATH += inc \
    ../flexsea-comm/inc \
    ../flexsea-system/inc

SOURCES += src/main.cpp \
    src/mainwindow.cpp \
    src/qcustomplot.cpp \
    src/plan_serial.c \
    src/flexsea_stream_log.c \
    src/test.c \
    src/flexsea_console.c \
    src/shared.c \
    src/demo.c \
    src/user.c \
    src/iolib.c \
    src/mw_tab_config.cpp \
    src/mw_tab_plot_1.cpp \
    src/mw_tab_stream_1.cpp \
    src/mw_tab_exp.cpp \
    src/mw_usbserial.cpp \
    ../flexsea-comm/src/flexsea.c \
    ../flexsea-comm/src/flexsea_buffers.c \
    ../flexsea-comm/src/flexsea_comm.c \
    ../flexsea-comm/src/flexsea_payload.c \
    ../flexsea-system/src/flexsea_cmd_application.c \
    ../flexsea-system/src/flexsea_cmd_control.c \
    ../flexsea-system/src/flexsea_cmd_external.c \
    ../flexsea-system/src/flexsea_cmd_sensors.c \
    ../flexsea-system/src/flexsea_system.c \
    src/flexsea_board.c \
    ../flexsea-system/src/flexsea_cmd_data.c \
    src/mw_tab_ctrl.cpp \
    src/mw_tab_ext.cpp \
    tabwidget.cpp

HEADERS  += inc/mainwindow.h \
    inc/qcustomplot.h \
    inc/test.h \
    inc/flexsea_stream_log.h \
    inc/plan_serial.h \
    inc/main.h \
    inc/flexsea_console.h \
    inc/user.h \
    inc/iolib.h \
    inc/shared.h \
    inc/demo.h \ 
    ../flexsea-comm/inc/flexsea.h \
    ../flexsea-comm/inc/flexsea_buffers.h \
    ../flexsea-comm/inc/flexsea_comm.h \
    ../flexsea-comm/inc/flexsea_payload.h \
    ../flexsea-system/inc/flexsea_cmd_application.h \
    ../flexsea-system/inc/flexsea_cmd_control.h \
    ../flexsea-system/inc/flexsea_cmd_external.h \
    ../flexsea-system/inc/flexsea_cmd_sensors.h \
    ../flexsea-system/inc/flexsea_system.h \
    inc/flexsea_board.h \
    ../flexsea-system/inc/flexsea_cmd_data.h \
    tabwidget.h

CONFIG(debug, debug|release) {
    DESTDIR = build/debug
}
CONFIG(release, debug|release) {
    DESTDIR = build/release
}

OBJECTS_DIR = $$DESTDIR/.obj
MOC_DIR = $$DESTDIR/.moc
RCC_DIR = $$DESTDIR/.qrc
UI_DIR = $$DESTDIR/.u

#QMAKE_LFLAGS += -Xlinker -Bstatic

FORMS    += mainwindow.ui \
    tabwidget.ui
