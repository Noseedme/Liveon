
#include "bulletEnemy.h"

BulletEnemy::BulletEnemy(QPointF pos, qreal angle, qreal speed, qreal damage, int penetration, QGraphicsScene *scene, Player *player, QObject *parent)
    : BulletBase{pos, angle, speed, damage,penetration, scene, parent}
{
    setPixmap(QPixmap(":/source/picture/enemy/en_bullet.png"));
    setTransformOriginPoint(boundingRect().center());
    be_player = player;
    disconnect(b_timer, &QTimer::timeout, this, &BulletEnemy::enemyHitCheck);
    connect(b_timer, &QTimer::timeout, this, &BulletEnemy::playerHitCheck);
    setZValue(114);
}

void BulletEnemy::playerHitCheck()//人物受击检测
{
    if (collidesWithItem(be_player)) {
        be_player->hurt();
        b_scene->removeItem(this);
        deleteLater();
    }
    if (x() < 0 || x() > 4800 || y() < 0 || y() > 2700) deleteLater();
}
