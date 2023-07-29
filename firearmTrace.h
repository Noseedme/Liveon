
#ifndef FIREARMTRACE_H
#define FIREARMTRACE_H


#include <QObject>
#include "FirearmBase.h"

class FirearmTrace : public FirearmBase
{
    Q_OBJECT
public:
    explicit FirearmTrace(Player *player, QGraphicsScene *scene,QObject *parent = nullptr);
    void fire() override;
signals:

};

#endif // FIREARMTRACE_H
