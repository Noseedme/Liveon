
#include "firearmBase.h"

QTimer *fb_timer = nullptr;


FirearmBase::FirearmBase(Player *player, QGraphicsScene *scene, QObject *parent)
    : QObject{parent}, fb_scene(scene), fb_player(player)
{
    //数据初始化
    fireRateBoost = 1;
    damageBoost = 1;
    speedBoost = 1;
    fireCount = 0;
    is_fire = 0;
    roundBoost = 0;
    penetration = 0;//穿透
    barrage = false;
    //音效
    sef_fire = new QSoundEffect(this);
    sef_fire->setVolume(0.5);
    sef_fire->setSource(QUrl::fromLocalFile(":/source/bgm/single_shot.wav"));

}

void FirearmBase::updatePos()
{
    setPos(fb_player->x(),fb_player->y());//枪的位置跟角色的位置是一样的
}

void FirearmBase::rotateToCursor(const QPointF &target)//旋转枪口的方向到光标
{
    QPointF firearmPos = mapToScene(transformOriginPoint());//maptoscene 将之前（父widget）的坐标转换到目前的坐标系中去
    double dx = target.x() - firearmPos.x();
    double dy = target.y() - firearmPos.y();
    //设置转向: 将弧度转换为角度 将角度取负值，并加上90度，是为了将角度转换为逆时针方向的旋转角度
    setRotation(-qRadiansToDegrees(qAtan2(dx, dy))+90);
}

void FirearmBase::setFireRateBoost(qreal fire)
{
    fireRateBoost = fire;
}

void FirearmBase::setDamageBoost(qreal dmg)
{
    damageBoost = dmg;
}

void FirearmBase::setSpeedBoost(qreal sp)
{
    speedBoost = sp;
}

void FirearmBase::load()
{
    QImage img(pix.toImage());
    //如果旋转的角度过大就直接翻转
    if((rotation() > 90 && rotation() < 270) || (rotation() < -90 && rotation() > -270)){
        img.mirror(false, true);
    }
      setPixmap(QPixmap::fromImage(img));
}

void FirearmBase::fire_on()
{
    is_fire = true;
}

void FirearmBase::fire_off()
{
    is_fire = false;
}

qreal FirearmBase::getFireRateBoost()
{
    return fireRateBoost;
}

qreal FirearmBase::getDamageBoost()
{
    return damageBoost;
}

qreal FirearmBase::getSpeedBoost()
{
    return speedBoost;
}

int FirearmBase::getRoundBoost() const
{
    return roundBoost;
}

void FirearmBase::setRoundBoost(int newRoundBoost)
{
    roundBoost = newRoundBoost;
}

qreal FirearmBase::getSpread() const
{
    return spread;
}

void FirearmBase::setSpread(qreal newSpread)
{
    spread = newSpread;
}

int FirearmBase::getPenetration() const
{
    return penetration;
}

void FirearmBase::setPenetration(int newPenetration)
{
     penetration = newPenetration;
}

bool FirearmBase::getBarrage() const
{
    return barrage;
}

void FirearmBase::setBarrage(bool newBarrage)
{
    barrage = newBarrage;
}
