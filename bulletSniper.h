
#ifndef BULLETSNIPER_H
#define BULLETSNIPER_H


#include <QObject>
#include <bulletBase.h>

class BulletSniper : public BulletBase
{
    Q_OBJECT
public:
    explicit BulletSniper(QPointF pos,qreal angle ,qreal speed, qreal damage, int penetration, QGraphicsScene *scene,QObject *parent = nullptr);

signals:

};

#endif // BULLETSNIPER_H
