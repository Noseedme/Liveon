
#include "enemyBase.h"


QRectF EnemyBase::pillarBounds1 = QRectF(880, 1022, 150, 40);
QRectF EnemyBase::pillarBounds2 = QRectF(880, 1810, 150, 40);
QRectF EnemyBase::pillarBounds3 = QRectF(2270, 1300, 300, 100);
QRectF EnemyBase::pillarBounds4 = QRectF(3770, 1020, 150, 40);
QRectF EnemyBase::pillarBounds5 = QRectF(3770, 1810, 150, 40);

QTimer* EnemyBase::e_timer = nullptr;
QSoundEffect *EnemyBase::sef_enemy_hurt = nullptr;

EnemyBase::EnemyBase(Player *player, QGraphicsScene *scene,QObject *parent)
    : QObject{parent}, e_player(player), e_scene(scene), is_hurt(false)
{
    //碰撞,移动,装载,计时器 死亡信号
    connect(e_timer,&QTimer::timeout,this,&EnemyBase::hitBoxCheck);
    connect(e_timer, &QTimer::timeout, this, &EnemyBase::mobMove);
    connect(e_timer, &QTimer::timeout, this, &EnemyBase::load);//收到伤害效果
    connect(&hurt_timer, &QTimer::timeout, this, &EnemyBase::hurt_reload);
    connect(this, &EnemyBase::enemyDeath, this, &EnemyBase::death);
    //受击音效
    sef_enemy_hurt = new QSoundEffect(this);
    sef_enemy_hurt->setSource(QUrl(":/source/bgm/single_shot.wav"));

}

void EnemyBase::mobMove()
{
    if (!e_player) {
        return;
    }
    // 计算出敌人到玩家的方向
    QLineF line(pos(), e_player->pos());

    // 计算出移动的距离和方向
    qreal dx = cos(line.angle() * M_PI / 180) * e_speed;
    qreal dy = -sin(line.angle() * M_PI / 180) * e_speed;
    QPointF newPos = pos() + QPointF(dx, dy);
    //边界是否包含这些点
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
        else { newPos = pos() + QPointF(0, e_speed); }
    }
    if (pillarBounds1.contains(newPos)
        || pillarBounds2.contains(newPos)
        || pillarBounds3.contains(newPos)
        || pillarBounds4.contains(newPos)
        || pillarBounds5.contains(newPos))
        newPos = pos() + QPointF(0, 0);
    // 移动
    setPos(newPos);
}
void EnemyBase::hurt(qreal damage)
{
    e_HP -= damage;
    sef_enemy_hurt->play();
    is_hurt = true;
    hurt_timer.start(100);
    if (e_HP <= 0) {
        emit enemyDeath();
    }
}

void EnemyBase::hitBoxCheck()
{
    if (collidesWithItem(e_player))//碰撞检测
        e_player->hurt();
}



void EnemyBase::death()
{
    EXP *exp = new EXP(e_player, pos(), e_scene, 1);
    exp->setParentItem(this->parentItem());
    e_scene->addItem(exp);
    e_scene->removeItem(this);
    deleteLater();
}

void EnemyBase::hurt_reload()
{
    is_hurt = false;
    hurt_timer.stop();
}
