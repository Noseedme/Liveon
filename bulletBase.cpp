
#include "bulletBase.h"
QTimer *BulletBase::b_timer = nullptr;
BulletBase::BulletBase(QPointF pos, qreal angle,qreal speed, qreal damage, int penetration, QGraphicsScene *scene,QObject *parent)
    : QObject{parent},b_scene(scene), b_speed(speed), b_damage(damage), b_penetration(penetration)//穿透

{
    // 设置子弹初始位置和角度
    setPos(pos);
    setRotation(angle);

    // 计时器绑定
    connect(b_timer, &QTimer::timeout, this, &BulletBase::enemyHitCheck);
    connect(b_timer, &QTimer::timeout, this, &BulletBase::move);
    b_scene->addItem(this);
    hurt_count = 0;
}


void BulletBase::enemyHitCheck()
{
    QList<QGraphicsItem*> coItems = this->collidingItems();//获取与子弹发生碰撞的敌人，并将它们存储在List
    for (QGraphicsItem* item : coItems) {
        EnemyBase* enemy = dynamic_cast<EnemyBase*>(item);//强制类型转换
        if (enemy) {

            //防止多次伤害
            bool flag = false;
            for (auto p : hurt_enemy_list) {
                if (p == enemy) flag = true;
            }
            //受到一次伤害后直接返回
            if (flag) return;
            enemy->hurt(b_damage);
            hurt_enemy_list.append(enemy);
            hurt_count++;//穿透计数
            if (hurt_count > b_penetration){
                b_scene->removeItem(this);
                deleteLater();
            }
            return;
        }
    }
    //超过边界直接销毁
    if (x() < 0 || x() > 4800 || y() < 0 || y() > 2700) deleteLater();
}

void BulletBase::move()
{
    // 获取当前朝向角度
    qreal angle = rotation();
    // 将角度转换为弧度
    qreal radian = qDegreesToRadians(angle);
    // 计算出当前移动的距离
    qreal distance = b_speed;
    // 计算出下一个位置
    qreal dy = distance * qSin(radian);
    qreal dx = distance * qCos(radian);
    // 移动到下一个位置
    moveBy(dx, dy);
}
