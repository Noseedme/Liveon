
#include "exp.h"

#include <QTimer>

QTimer *EXP::e_timer = nullptr;

EXP::EXP(Player *player, QPointF pos, QGraphicsScene *scene, int xp)
    :e_player(player),e_scene(scene),e_xp(xp)
{
    setPos(pos);
    setPixmap(QPixmap(":/source/picture/startGame/xps.png"));
    setScale(1.5);
    e_scene->addItem(this);
    setParent(e_scene);
    connect(e_timer, &QTimer::timeout, this, &EXP::checkPickUp);

}

void EXP::checkPickUp()
{
    QLineF dist = QLineF(pos(),e_player->pos());
    if (dist.length() <= e_player->getPickupRange()){
        qreal radian = dist.angle() * M_PI / 180;//radin 弧度  = 线的角度 * Π / 180
        qreal dx = cos(radian) * 5;
        qreal dy = -sin(radian) * 5;
        setPos(pos() + QPointF(dx,dy));
    }
    if (collidesWithItem(e_player)){//碰撞检测 是返回true
        e_player->pickupExp(e_xp);
        e_scene->removeItem(this);
        delete this;
    }
}

