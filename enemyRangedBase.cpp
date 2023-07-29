
#include "enemyRangedBase.h"
#include <QRandomGenerator>//随机数

EnemyRangedBase::EnemyRangedBase(Player *player, QGraphicsScene *scene,QObject *parent)
    : EnemyBase {player, scene, parent}
{
    connect(e_timer, &QTimer::timeout, this, &EnemyRangedBase::angleChange);
    angle_change_max = 100;
    angle_change_count = 0;
}
void EnemyRangedBase::mobMove()
{
    if (!e_player) return;
    qreal dist = QLineF(pos(), e_player->pos()).length();
    QPointF newPos;
    qreal dx;
    qreal dy;
    if (dist > 400){//最大追踪距离 超过移动
        // 计算出 Enemy 到 Player 的方向
        QLineF line(pos(), e_player->pos());

        // 计算出移动的距离和方向
        dx = cos(line.angle() * M_PI / 180) * e_speed;
        dy = -sin(line.angle() * M_PI / 180) * e_speed;
        newPos = pos() + QPointF(dx, dy);
    } else {//否则调转方向
        dx = cos(angle * M_PI / 180) * e_speed;
        dy = -sin(angle * M_PI / 180) * e_speed;
        newPos = pos() + QPointF(dx, dy);
    }
    if (pillarBounds1.contains(newPos)
        || pillarBounds2.contains(newPos)
        || pillarBounds3.contains(newPos)
        || pillarBounds4.contains(newPos)
        || pillarBounds5.contains(newPos)) {
        if (dx > 0) { newPos = pos() + QPointF(e_speed, 0); }
        else { newPos = pos() + QPointF(-e_speed, 0); }
    }
    if (pillarBounds1.contains(newPos)
        || pillarBounds2.contains(newPos)
        || pillarBounds3.contains(newPos)
        || pillarBounds4.contains(newPos)
        || pillarBounds5.contains(newPos)) {
        if (dy > 0) { newPos = pos() + QPointF(0, e_speed); }
        else { newPos = pos() + QPointF(0, -e_speed); }
    }
    if (pillarBounds1.contains(newPos)
        || pillarBounds2.contains(newPos)
        || pillarBounds3.contains(newPos)
        || pillarBounds4.contains(newPos)
        || pillarBounds5.contains(newPos))
        newPos = pos() + QPointF(0, 0);
    // 移动 敌人
    setPos(newPos);
}

void EnemyRangedBase::angleChange()
{
    angle_change_count++;
    if (angle_change_count < angle_change_max) return;
    angle_change_count = 0;
    angle = QRandomGenerator::global()->bounded(360);
    angle_change_max = QRandomGenerator::global()->bounded(200) + 100;
}
