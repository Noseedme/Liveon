
#include "gameWidget.h"
#include <QDebug>

GameWidget::GameWidget(QWidget *parent)
    : QWidget(parent)
{
    setMouseTracking(true);
    setFixedSize(1280, 720);
    setWindowIcon(QIcon(":/source/picture/stratMenu/bz.png"));
    setWindowTitle("Live On");
    g_firearm = "smGun";
    init_startMenu();
    g_startMenu->show();
    QPixmap cursor_pic(":/source/picture/stratMenu/mouse.png");
    QCursor cursor(cursor_pic, -cursor_pic.width()/2, -cursor_pic.height()/2);
    setCursor(cursor);
}

void GameWidget::init_startMenu(){
    g_startMenu = new StartMenu();
    g_startMenu->setParent(this);
    connect(g_startMenu, &StartMenu::firearmSelect, this, [=](QString fs){
        g_firearm = fs;
    });
    connect(g_startMenu, &StartMenu::loadArchive, this, [=](QString arc){
        g_archive = arc;
    });
    connect(g_startMenu, &StartMenu::startGame, this,&GameWidget::start_game);
}

void GameWidget::init_startGame()
{
    g_startGame = new StartGame(g_firearm,g_archive);
    qInfo() <<g_archive;
    g_startGame->setParent(this);
    g_firearm = "smGun";
    connect(g_startGame,&StartGame::EndGame,this,&GameWidget::end_game);
}

void GameWidget::start_game()
{
    g_startMenu->hide();
    init_startGame();
    g_startGame->show();
    g_startGame->setFocus();//设置焦点
}
void GameWidget::end_game(){
    g_startGame->hide();
    disconnect(g_startGame, &StartGame::EndGame, this, &GameWidget::end_game);
    init_startMenu();
    g_startMenu->show();
    g_startMenu->setFocus();
};

