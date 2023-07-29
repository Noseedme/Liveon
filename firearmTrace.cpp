
#include "firearmTrace.h"
#include "bulletTrace.h"
#include <QRandomGenerator>
FirearmTrace::FirearmTrace(Player *player, QGraphicsScene *scene, QObject *parent)
    : FirearmBase{player, scene, parent}
{
    pix = QPixmap(":/source/picture/firearms/arm/fa_trace.png");
    setPixmap(pix);
    setTransformOriginPoint(boundingRect().center());
    spread = 20;
    setScale(3.5);
}

void FirearmTrace::fire()
{
    if (!is_fire && fireCount >= (20.0 / fireRateBoost)) return;
    fireCount++;
    if (!is_fire) return;
    if (fireCount < (20.0 / (fireRateBoost + 0.35 * barrage * fb_player->getIs_still() + 0.3 * fb_player->getIs_inthewind()))) return;
    fireCount = 0;
    sef_fire->play();
    for (int i = 0; i < 1 + roundBoost; ++i) {
        BulletTrace *bullet = new BulletTrace(pos(), rotation(), 15 * speedBoost, 10 * damageBoost, penetration, fb_scene, parent());
        bullet->setRotation(bullet->rotation() + QRandomGenerator::global()->bounded((int)(-spread*10), (int)(spread*10)) * 0.1);
        bullet->setParentItem(parentItem());
        bullet->setScale(3);
        fb_scene->addItem(bullet);
    }
}
