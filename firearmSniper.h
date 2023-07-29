
#ifndef FIREARMSNIPER_H
#define FIREARMSNIPER_H


#include <QObject>

#include "firearmBase.h"

class FirearmSniper : public FirearmBase
{
    Q_OBJECT
public:
    explicit FirearmSniper(Player *player, QGraphicsScene *scene,QObject *parent = nullptr);
    void fire() override;
signals:

};

#endif // FIREARMSNIPER_H
