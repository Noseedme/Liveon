
#ifndef BULLETBASE_H
#define BULLETBASE_H


#include <QObject>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QTimer>
#include <QList>

#include "enemyBase.h"

class BulletBase : public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit BulletBase(QPointF pos, qreal angle,qreal speed, qreal damage, int penetration, QGraphicsScene *scene,QObject *parent = nullptr);
    static QTimer *b_timer;
signals:
protected:
    void enemyHitCheck();//敌人受击检测
    void move();
    QGraphicsScene *b_scene;
    qreal b_speed;
    qreal b_damage;
    int b_penetration;
    QList<EnemyBase*> hurt_enemy_list;
    int hurt_count;
};

#endif // BULLETBASE_H
