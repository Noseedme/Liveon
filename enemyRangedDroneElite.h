
#ifndef ENEMYRANGEDDRONEELITE_H
#define ENEMYRANGEDDRONEELITE_H


#include <QObject>
#include "enemyRangedBase.h"

class EnemyRangedDroneElite : public EnemyRangedBase
{
    Q_OBJECT
public:
    explicit EnemyRangedDroneElite(Player *player, QGraphicsScene *scene,QObject *parent = nullptr);

signals:
private:
    void load() override;
    void attack() override;
    int attack_count;
    const int attack_max;
    QPixmap pix;

};

#endif // ENEMYRANGEDDRONEELITE_H
