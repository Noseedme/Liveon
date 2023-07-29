
#ifndef FIREARMSMGUN_H
#define FIREARMSMGUN_H


#include <QObject>
#include <firearmBase.h>

class FirearmSmgun :  public FirearmBase
{
    Q_OBJECT
public:
    explicit FirearmSmgun(Player *player, QGraphicsScene *scene,QObject *parent = nullptr);
    void fire() override;
signals:

};

#endif // FIREARMSMGUN_H
