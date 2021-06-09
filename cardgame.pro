QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    cardgame/game/card.cpp \
    cardgame/game/deck.cpp \
    cardgame/game/main.cpp \
    cardgame/player_web/player.cpp \
    cardgame/test_web/client.cpp \
    cardgame/test_web/server_multi.cpp \
    cardgame/test_web/server_single.cpp \
    cardgame/web/winsock.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    include/card.h \
    include/game.h \
    include/player.h \
    include/winsock.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
