
#ifndef ENEMYRANGEDDRONE_H
#define ENEMYRANGEDDRONE_H


#include <QObject>
#include "enemyRangedBase.h"

class EnemyRangedDrone : public EnemyRangedBase
{
    Q_OBJECT
public:
    explicit EnemyRangedDrone(Player *player, QGraphicsScene *scene,QObject *parent = nullptr);

signals:
private:
    void load() override;
    void attack() override;
    int attack_count;
    const int attack_max;
    QPixmap pix;
};

#endif // ENEMYRANGEDDRONE_H
