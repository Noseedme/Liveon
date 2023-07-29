
#ifndef BULLETSHOTGUN_H
#define BULLETSHOTGUN_H


#include <QObject>
#include <bulletBase.h>

class BulletShotgun : public BulletBase
{
    Q_OBJECT
public:
    explicit BulletShotgun(QPointF pos, qreal angle, qreal speed, qreal damage, int penetration, QGraphicsScene *scene,QObject *parent = nullptr);

signals:

};

#endif // BULLETSHOTGUN_H
