
#ifndef ENEMYEXPLOBALL_H
#define ENEMYEXPLOBALL_H


#include <QObject>
#include "enemyExploBase.h"

class EnemyExploBall : public EnemyExploBase
{
    Q_OBJECT
public:
    explicit EnemyExploBall(Player *player, QGraphicsScene *scene,QObject *parent = nullptr);

signals:
private:
    void load() override;
    void explode() override;//使爆炸

    QPixmap pix;
    QMovie *move_explosion;
};

#endif // ENEMYEXPLOBALL_H
