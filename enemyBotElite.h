
#ifndef ENEMYBOTELITE_H
#define ENEMYBOTELITE_H


#include <QObject>
#include "enemyBase.h"

class EnemyBotElite : public EnemyBase
{
    Q_OBJECT
public:
    explicit EnemyBotElite(Player *player, QGraphicsScene *scene,QObject *parent = nullptr);

signals:
private:
    void load() override;
    QMovie *ebe_movie;
};

#endif // ENEMYBOTELITE_H
