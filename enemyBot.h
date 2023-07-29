
#ifndef ENEMYBOT_H
#define ENEMYBOT_H


#include <QObject>
#include "enemyBase.h"

class EnemyBot : public EnemyBase

{
    Q_OBJECT
public:
    explicit EnemyBot(Player *player, QGraphicsScene *scene,QObject *parent = nullptr);

signals:
private:
    void load() override;
    QMovie *eb_movie;

};

#endif // ENEMYBOT_H
