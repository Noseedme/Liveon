
#include "firearmSmgun.h"
#include "bulletSmgun.h"
#include <QRandomGenerator>//随机数

FirearmSmgun::FirearmSmgun(Player *player, QGraphicsScene *scene, QObject *parent)
    : FirearmBase{player, scene, parent}
{
    pix = QPixmap(":/source/picture/firearms/arm/fa_smgun.png");
    setPixmap(pix);
    setTransformOriginPoint(boundingRect().center());
    spread = 15;//扩散
    setScale(3.5);
}

void FirearmSmgun::fire()
{
    //100.0 / fireRateBoost 计算出每秒可以进行的最大射击次数
    if (!is_fire && fireCount >= (10.0 / fireRateBoost)) return;
    fireCount++;
    if (!is_fire) return;
    // 计算出实际的射击速率                             连续射击           是否站立                        是否在风行中
    if (fireCount < (10.0 / (fireRateBoost + 0.35 * barrage * fb_player->getIs_still() + 0.3 * fb_player->getIs_inthewind()))) return;
    fireCount = 0;
    sef_fire->play();
    //创建射击的子弹
    for (int i = 0; i < 1 + roundBoost; ++i) {
        BulletSmgun *bullet = new BulletSmgun(pos(), rotation(), 20 * speedBoost, 8 * damageBoost, penetration, fb_scene, parent());
        //通过随机数调整子弹的旋转角度，使射击有一定的散开效果。
        bullet->setRotation(bullet->rotation() + QRandomGenerator::global()->bounded((int)(-spread*10), (int)(spread*10)) * 0.1);
        bullet->setParentItem(parentItem());
        bullet->setScale(3);
        fb_scene->addItem(bullet);
    }
}
