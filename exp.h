
#ifndef EXP_H
#define EXP_H


#include <QObject>
#include <QGraphicsPathItem>
#include <QPointF>
#include <QGraphicsScene>
#include "player.h"

class EXP : public QObject ,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit EXP(Player *player,QPointF pos,QGraphicsScene *scene,int xp);

    void checkPickUp();
    static QTimer *e_timer;

signals:
private:
    Player *e_player;
    QGraphicsScene *e_scene;
    int e_xp;


};

#endif // EXP_H
