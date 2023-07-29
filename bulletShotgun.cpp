
#include "bulletShotgun.h"

BulletShotgun::BulletShotgun(QPointF pos, qreal angle, qreal speed, qreal damage, int penetration, QGraphicsScene *scene,QObject *parent )
    : BulletBase{pos, angle, speed, damage , penetration, scene, parent}
{
    setPixmap(QPixmap(":/source/picture/firearms/arm/fa_shotgun_bullet.png"));
}

