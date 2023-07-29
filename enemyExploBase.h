
#ifndef ENEMYEXPLOBASE_H
#define ENEMYEXPLOBASE_H


#include <QObject>
#include "enemyBase.h"

class EnemyExploBase :  public EnemyBase
{
    Q_OBJECT
public:
    explicit EnemyExploBase(Player *player, QGraphicsScene *scene,QObject *parent = nullptr);
signals:
protected:
    qreal exploRange;
    qreal exploDamage;
    virtual void explode() = 0;
    void death() override;
    void enemyHitCheck();//与敌人碰撞检查
    QSoundEffect *sef_explosion;
};

#endif // ENEMYEXPLOBASE_H
