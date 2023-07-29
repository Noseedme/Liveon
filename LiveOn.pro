QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Archive.cpp \
    FirearmSelect.cpp \
    GraphicsButton.cpp \
    GraphicsSelectButton.cpp \
    bulletBase.cpp \
    bulletEnemy.cpp \
    bulletShotgun.cpp \
    bulletSmgun.cpp \
    bulletSniper.cpp \
    bulletTrace.cpp \
    enemyBase.cpp \
    enemyBot.cpp \
    enemyBotElite.cpp \
    enemyEexploBase.cpp \
    enemyExploBall.cpp \
    enemyRangedBase.cpp \
    enemyRangedDrone.cpp \
    enemyRangedDroneElite.cpp \
    exp.cpp \
    firearmBase.cpp \
    firearmShotgun.cpp \
    firearmSmgun.cpp \
    firearmSniper.cpp \
    firearmTrace.cpp \
    hpLabel.cpp \
    main.cpp \
    gameWidget.cpp \
    player.cpp \
    shop.cpp \
    startGame.cpp \
    startMenu.cpp \
    upPower.cpp

HEADERS += \
    Archive.h \
    FirearmSelect.h \
    GraphicsButton.h \
    GraphicsSelectButton.h \
    bulletBase.h \
    bulletEnemy.h \
    bulletShotgun.h \
    bulletSmgun.h \
    bulletSniper.h \
    bulletTrace.h \
    enemyBase.h \
    enemyBot.h \
    enemyBotElite.h \
    enemyExploBall.h \
    enemyExploBase.h \
    enemyRangedBase.h \
    enemyRangedDrone.h \
    enemyRangedDroneElite.h \
    exp.h \
    firearmBase.h \
    firearmShotgun.h \
    firearmSmgun.h \
    firearmSniper.h \
    firearmTrace.h \
    gameWidget.h \
    hpLabel.h \
    player.h \
    shop.h \
    startGame.h \
    startMenu.h \
    upPower.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    source.qrc

DISTFILES += \
