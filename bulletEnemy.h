
#ifndef BULLETENEMY_H
#define BULLETENEMY_H


#include <QObject>
#include "bulletBase.h"
#include "player.h"

class BulletEnemy : public BulletBase
{
    Q_OBJECT
public:
    explicit BulletEnemy(QPointF pos, qreal angle, qreal speed, qreal damage, int penetration,QGraphicsScene *scene, Player *player,QObject *parent = nullptr);

signals:
private:
    void playerHitCheck();
    Player *be_player;
};

#endif // BULLETENEMY_H
