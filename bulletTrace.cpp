
#include "bulletTrace.h"

BulletTrace::BulletTrace(QPointF pos,qreal angle ,qreal speed, qreal damage, int penetration, QGraphicsScene *scene,QObject *parent )
    : BulletBase{pos,angle,speed,damage,penetration,scene,parent}
{
    setPixmap(QPixmap(":/source/picture/firearms/arm/fa_trace_bullet.png"));
    setScale(3);
    connect(b_timer,&QTimer::timeout,this,&BulletTrace::track);

}

void BulletTrace::track()
{
    QList<QGraphicsItem*> item_list = b_scene->items();
    QList<EnemyBase*> enemy_list;
    EnemyBase *target = nullptr;
    qreal min_dist = 0x3ffffff;//最小距离
    for (QGraphicsItem *item : item_list) {
        EnemyBase *enemy = dynamic_cast<EnemyBase*>(item);
        if (enemy) enemy_list.append(enemy);
    }
    for (EnemyBase *enemy : enemy_list) {
        bool flag = false;//避免重复受伤
        for (auto p : hurt_enemy_list) {
            if (p == enemy) {
                flag = true;
                break;
            }
        }
        if (flag) continue;
        qreal dist = QLineF(pos(), enemy->pos()).length();
        if (dist < min_dist) {
            target = enemy;
            min_dist = dist;
        }
    }
    if (target != nullptr){

        qreal targetAngle = QLineF(pos(), target->pos()).angle();   // 顺时针角度
        qreal bulletAngle = rotation();   //旋转一周                  // 逆时针角度

        qreal angle = targetAngle + bulletAngle;
        while (angle > 180) angle -= 360;     // 确保在-180到180度范围内
        while (angle < -180) angle += 360;
        if (angle > 4) {
            setRotation(rotation() - 4);//每次调转方向在 -4度至4度之间
        } else if (angle < -4){
            setRotation(rotation() + 4);
        } else {
            setRotation(rotation() - angle);
        }
    }
}

