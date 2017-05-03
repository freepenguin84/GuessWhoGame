#-------------------------------------------------
#
# Project created by QtCreator 2017-03-12T18:53:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GuessWho
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        guesswho.cpp \
    player.cpp \
    guess.cpp \
    pixelator.cpp \
    settingsdialog.cpp \
    configuration.cpp \
    imagespage.cpp \
    playerspage.cpp \
    game.cpp \
    guessdialog.cpp

HEADERS  += guesswho.h \
    player.h \
    guess.h \
    pixelator.h \
    settingsdialog.h \
    configuration.h \
    imagespage.h \
    playerspage.h \
    game.h \
    guessdialog.h

FORMS    += guesswho.ui \
    settingsdialog.ui \
    gamewizard.ui \
    imagespage.ui \
    playerrow.ui \
    playerspage.ui \
    guessdialog.ui
