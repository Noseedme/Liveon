
#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "startMenu.h"
#include "startGame.h"

class GameWidget : public QWidget

{
    Q_OBJECT

public:
    GameWidget(QWidget *parent = nullptr);
private:
    StartMenu *g_startMenu;
    StartGame *g_startGame;
    QString g_firearm;
    QString g_archive = "none";

    void init_startMenu();
    void init_startGame();
    void start_game();
    void end_game();
};

#endif // GAMEWIDGET_H
