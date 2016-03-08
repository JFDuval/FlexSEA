#-------------------------------------------------
#
# Project created by QtCreator 2015-11-22T14:55:53
#
#-------------------------------------------------

QT       += core gui
QT      += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = execute-gui-1
TEMPLATE = app

INCLUDEPATH += inc \
    ../common/inc

SOURCES += src/main.cpp \
    src/mainwindow.cpp \
    src/qcustomplot.cpp \
    src/plan_serial.c \
    src/flexsea_local.c \
    src/flexsea_stream_log.c \
    src/test.c \
    src/flexsea_console.c \
    src/shared.c \
    src/demo.c \
    src/user.c \
    src/iolib.c \
    ../common/src/flexsea_cmd_user.c \
    ../common/src/flexsea_comm.c \
    ../common/src/flexsea_payload.c \
    ../common/src/flexsea_cmd_control.c \
    ../common/src/flexsea_cmd_sensors.c \
    ../common/src/flexsea_tx_cmd.c \
    ../common/src/flexsea_cmd_data.c \
    ../common/src/flexsea_rx_cmd.c \
    ../common/src/flexsea_cmd_external.c \
    ../common/src/flexsea_buffers.c \
    ../common/src/flexsea_cmd_system.c \
    ../common/src/flexsea.c \
    ../common/src/flexsea_cmd_comm.c \
    src/mw_tab_config.cpp \
    src/mw_tab_plot_1.cpp \
    src/mw_tab_stream_1.cpp \
    src/mw_tab_exp.cpp \
    src/mw_usbserial.cpp

HEADERS  += inc/mainwindow.h \
    inc/qcustomplot.h \
    inc/flexsea_local.h \
    inc/test.h \
    inc/flexsea_stream_log.h \
    inc/plan_serial.h \
    inc/main.h \
    inc/flexsea_console.h \
    inc/user.h \
    inc/iolib.h \
    inc/shared.h \
    inc/demo.h \
    ../common/inc/flexsea_comm.h \
    ../common/inc/flexsea_cmd_user.h \
    ../common/inc/flexsea.h \
    ../common/inc/flexsea_cmd_sensors.h \
    ../common/inc/flexsea_rx_cmd.h \
    ../common/inc/flexsea_cmd_control.h \
    ../common/inc/flexsea_tx_cmd.h \
    ../common/inc/flexsea_cmd_data.h \
    ../common/inc/flexsea_cmd_external.h \
    ../common/inc/flexsea_buffers.h \
    ../common/inc/flexsea_payload.h \
    ../common/inc/flexsea_cmd_system.h \
    ../common/inc/flexsea_cmd_comm.h

DESTDIR = release
OBJECTS_DIR = release/.obj
MOC_DIR = release/.moc
RCC_DIR = release/.rcc
UI_DIR = release/.ui

FORMS    += mainwindow.ui
