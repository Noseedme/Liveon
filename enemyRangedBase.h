
#ifndef ENEMYRANGEDBASE_H
#define ENEMYRANGEDBASE_H


#include <QObject>
#include "enemyBase.h"
#include <QTimer>

class EnemyRangedBase : public EnemyBase
{
    Q_OBJECT
public:
    explicit EnemyRangedBase(Player *player, QGraphicsScene *scene,QObject *parent = nullptr);

signals:
protected:
    void mobMove() override;
    virtual void attack() = 0;
    qreal angle;
    void angleChange();
    int angle_change_count;
    int angle_change_max;//最大角度
};

#endif // ENEMYRANGEDBASE_H
