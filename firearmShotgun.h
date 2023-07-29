
#ifndef FIREARMSHOTGUN_H
#define FIREARMSHOTGUN_H


#include <QObject>
#include "firearmBase.h"

class FirearmShotgun : public FirearmBase
{
    Q_OBJECT
public:
    explicit FirearmShotgun(Player *player, QGraphicsScene *scene,QObject *parent = nullptr);
    void fire() override;
signals:

};

#endif // FIREARMSHOTGUN_H
