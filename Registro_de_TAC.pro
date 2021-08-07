#-------------------------------------------------
#
# Project created by QtCreator 2016-01-22T18:48:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Registro_de_TAC
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    my_dicom_utils.cpp \
    include/dicomdatastructure.cpp \
    include/dicomreadheader.cpp \
    searchfunctions.cpp \
    include/patientrecord.cpp

HEADERS  += mainwindow.h \
    my_dicom_utils.h \
    include/dicomdatadict.h \
    include/dicomdatastructure.h \
    include/dicomreadheader.h \
    searchfunctions.h \
    include/patientrecord.h

FORMS    += mainwindow.ui \
    searchbar.ui

RESOURCES += \
    registro_de_tac_resources.qrc
