
#ifndef BULLETTRACE_H
#define BULLETTRACE_H


#include <QObject>
#include "bulletBase.h"
#include "enemyBase.h"

class BulletTrace :  public BulletBase
{
    Q_OBJECT
public:
    explicit BulletTrace(QPointF pos,qreal angle ,qreal speed, qreal damage, int penetration, QGraphicsScene *scene,QObject *parent = nullptr);

signals:
private:
    void track();
};

#endif // BULLETTRACE_H
