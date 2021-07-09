QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    _21_points.cpp \
    _21point_board.cpp \
    cardgame/game/card.cpp \
    cardgame/game/deck.cpp \
    cardgame/player_web/player.cpp \
    gameserver.cpp \
    main.cpp \
    mainwindow.cpp \
    selectnumplayer.cpp \
    uno_game.cpp \
    waitroom.cpp \
    waitserver.cpp

HEADERS += \
    _21_points.h \
    _21point_board.h \
    const.h \
    gameserver.h \
    include/card.h \
    include/game.h \
    include/player.h \
    mainwindow.h \
    selectnumplayer.h \
    uno_game.h \
    waitroom.h \
    waitserver.h

FORMS += \
    _21_points.ui \
    _21point_board.ui \
    mainwindow.ui \
    selectnumplayer.ui \
    uno_game.ui \
    waitroom.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    pics.qrc
