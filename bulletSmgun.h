
#ifndef BULLETSMGUN_H
#define BULLETSMGUN_H


#include <QObject>
#include "bulletBase.h"

class BulletSmgun : public BulletBase
{
    Q_OBJECT
public:
    explicit BulletSmgun(QPointF pos, qreal angle, qreal speed, qreal damage, int penetration, QGraphicsScene *scene,QObject *parent = nullptr);

signals:

};

#endif // BULLETSMGUN_H
