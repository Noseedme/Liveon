
#include "bulletSmgun.h"

BulletSmgun::BulletSmgun(QPointF pos, qreal angle, qreal speed, qreal damage, int penetration, QGraphicsScene *scene,QObject *parent )
    : BulletBase{pos, angle, speed, damage , penetration, scene, parent}
{
    setPixmap(QPixmap(":/source/picture/firearms/arm/fa_smgun_bullet.png"));
}

