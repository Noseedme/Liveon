
#include "enemyExploBase.h"

EnemyExploBase::EnemyExploBase(Player *player, QGraphicsScene *scene, QObject *parent)
    : EnemyBase{player, scene, parent}
{
    sef_explosion = new QSoundEffect(this);
    sef_explosion->setSource(QUrl(":/source/soundEffect/en_explode.wav"));
}

void EnemyExploBase::death()
{
    EXP *exp = new EXP(e_player, pos(), e_scene, 1);
    exp->setParentItem(this->parentItem());
    sef_explosion->play();
    explode();
}

void EnemyExploBase::enemyHitCheck()
{
    QList<QGraphicsItem*> list = collidingItems();
    for (QGraphicsItem *item : list) {
        EnemyBase* enemy = dynamic_cast<EnemyBase*>(item);
        if (enemy) {
            enemy->hurt(exploDamage);
        }
    }
}
