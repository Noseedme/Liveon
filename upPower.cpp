
#include "upPower.h"

bool UpPower::u_vitality = false;
bool UpPower::u_giant = false;
bool UpPower::u_dodge = false;
bool UpPower::u_regeneration = false;

bool UpPower::u_hollowpoint = false;
bool UpPower::u_doubleshot = false;
bool UpPower::u_heavybarrel = false;
bool UpPower::u_reaper = false;

bool UpPower::u_fasthand = false;
bool UpPower::u_overload = false;
bool UpPower::u_lightbullet = false;
bool UpPower::u_barrage = false;

bool UpPower::u_streamline = false;
bool UpPower::u_sniper = false;
bool UpPower::u_takeaim = false;
bool UpPower::u_pierecinground = false;

bool UpPower::u_haste = false;
bool UpPower::u_overspeed = false;
bool UpPower::u_runngun = false;
bool UpPower::u_inthewind = false;


UpPower::UpPower(int s, int index, Player *player, FirearmBase *firearm, QGraphicsScene *scene, QObject *parent)
    : QObject{parent},u_sign(s),up_index(index),u_player(player),u_firearm(firearm),u_scene(scene)
{
    QFontDatabase::addApplicationFont(":/source/font/fusion-pixel-proportional.ttf");
    //注释
    u_desc = new QGraphicsTextItem();
    u_desc->setDefaultTextColor(Qt::white);
    u_desc->setFont(QFont("fusion pixel proportional", 16));
    setUpPower(up_index);
    u_scene->addItem(u_icon);
    connect(u_icon, &GraphicsButton::hoverEnter, this, &UpPower::hoverEnter);
    connect(u_icon, &GraphicsButton::hoverLeave, this, &UpPower::hoverLeave);
    connect(u_icon, &GraphicsButton::mouseClicked, this, &UpPower::mouseClicked);
}

UpPower::~UpPower()
{
    u_scene->removeItem(u_icon);
    u_scene->removeItem(u_desc);
    u_icon->deleteLater();
    delete u_desc;
}

void UpPower::resetAll()
{
    u_vitality = false;
    u_giant = false;
    u_dodge = false;
    u_regeneration = false;

    u_hollowpoint = false;
    u_doubleshot = false;
    u_heavybarrel = false;
    u_reaper = false;

    u_fasthand = false;
    u_overload = false;
    u_lightbullet = false;
    u_barrage = false;

    u_streamline = false;
    u_sniper = false;
    u_takeaim = false;
    u_pierecinground = false;

    u_haste = false;
    u_overspeed = false;
    u_runngun = false;
    u_inthewind = false;
}

bool UpPower::getU_vitality()
{
    return  u_vitality;
}

void UpPower::setU_vitality(bool newU_vitality)
{
    u_vitality = newU_vitality;
}

bool UpPower::getU_giant()
{
    return  u_giant;
}

void UpPower::setU_giant(bool newU_giant)
{
    u_giant = newU_giant;
}

bool UpPower::getU_dodge()
{
    return  u_dodge;
}

void UpPower::setU_dodge(bool newU_dodge)
{
    u_dodge = newU_dodge;
}

bool UpPower::getU_regeneration()
{
    return u_regeneration;
}

void UpPower::setU_regeneration(bool newU_regeneration)
{
    u_regeneration = newU_regeneration;
}

bool UpPower::getU_hollowpoint()
{
    return u_hollowpoint;
}

void UpPower::setU_hollowpoint(bool newU_hollowpoint)
{
    u_hollowpoint = newU_hollowpoint;
}

bool UpPower::getU_doubleshot()
{
    return u_doubleshot;
}

void UpPower::setU_doubleshot(bool newU_doubleshot)
{
    u_doubleshot = newU_doubleshot;
}

bool UpPower::getU_heavybarrel()
{
    return u_heavybarrel;
}

void UpPower::setU_heavybarrel(bool newU_heavybarrel)
{
    u_heavybarrel = newU_heavybarrel;
}

bool UpPower::getU_reaper()
{
    return u_reaper;
}

void UpPower::setU_reaper(bool newU_reaper)
{
    u_reaper = newU_reaper;
}

bool UpPower::getU_fasthand()
{
    return u_fasthand;
}

void UpPower::setU_fasthand(bool newU_fasthand)
{
    u_fasthand = newU_fasthand;
}

bool UpPower::getU_overload()
{
    return u_overload;
}

void UpPower::setU_overload(bool newU_overload)
{
    u_overload = newU_overload;
}

bool UpPower::getU_lightbullet()
{
    return u_lightbullet;
}

void UpPower::setU_lightbullet(bool newU_lightbullet)
{
    u_lightbullet = newU_lightbullet;
}

bool UpPower::getU_barrage()
{
    return u_barrage;
}

void UpPower::setU_barrage(bool newU_barrage)
{
    u_barrage = newU_barrage;
}

bool UpPower::getU_streamline()
{
    return u_streamline;
}

void UpPower::setU_streamline(bool newU_streamline)
{
    u_streamline = newU_streamline;
}

bool UpPower::getU_sniper()
{
    return u_sniper;
}

void UpPower::setU_sniper(bool newU_sniper)
{
    u_sniper = newU_sniper;
}

bool UpPower::getU_takeaim()
{
    return u_takeaim;
}

void UpPower::setU_takeaim(bool newU_takeaim)
{
    u_takeaim = newU_takeaim;
}

bool UpPower::getU_pierecinground()
{
    return u_pierecinground;
}

void UpPower::setU_pierecinground(bool newU_pierecinground)
{
    u_pierecinground = newU_pierecinground;
}

bool UpPower::getU_haste()
{
    return u_haste;
}

void UpPower::setU_haste(bool newU_haste)
{
    u_haste = newU_haste;
}

bool UpPower::getU_overspeed()
{
    return u_overspeed;
}

void UpPower::setU_overspeed(bool newU_overspeed)
{
    u_overspeed = newU_overspeed;
}

bool UpPower::getU_runngun()
{
    return u_runngun;
}

void UpPower::setU_runngun(bool newU_runngun)
{
    u_runngun = newU_runngun;
}

bool UpPower::getU_inthewind()
{
    return u_inthewind;
}

void UpPower::setU_inthewind(bool newU_inthewind)
{
    u_inthewind = newU_inthewind;
}

void UpPower::hoverEnter()
{
    u_scene->addItem(u_desc);
}

void UpPower::hoverLeave()
{
    u_scene->removeItem(u_desc);
}

void UpPower::mouseClicked()
{
    emit upPowerSelected();
    deleteLater();
}

void UpPower::setUpPower(int u_index)
{
    switch (u_index) {
    case 0:
        u_icon = new GraphicsButton(":/source/picture/power/u_void", QPointF(320 * u_sign + 280, 160), this);
        u_desc->setPlainText("???:坏了 空军");
        break;
    case 1:
        u_icon = new GraphicsButton(":/source/picture/power/u_vitality", QPointF(320 * u_sign + 280, 160), this);
        u_desc->setPlainText("活力提升: +2HP");
        connect(u_icon, &GraphicsButton::mouseClicked, this, &UpPower::l_vitality);
        break;
    case 2:
        u_icon = new GraphicsButton(":/source/picture/power/u_giant", QPointF(320 * u_sign + 280, 160), this);
        u_desc->setPlainText("咬自己一口!巨人化 +4HP +25%体型");
        connect(u_icon, &GraphicsButton::mouseClicked, this, &UpPower::l_giant);
        break;
    case 3:
        u_icon = new GraphicsButton(":/source/picture/power/u_dodge", QPointF(320 * u_sign + 280, 160), this);
        u_desc->setPlainText("无影步  +30%闪避");
        connect(u_icon, &GraphicsButton::mouseClicked, this, &UpPower::l_dodge);
        break;
    case 4:
        u_icon = new GraphicsButton(":/source/picture/power/u_regeneration", QPointF(320 * u_sign + 280, 160), this);
        u_desc->setPlainText("自我疗愈 60s/+1HP");
        connect(u_icon, &GraphicsButton::mouseClicked, this, &UpPower::l_regeneration);
        break;
    case 5:
        u_icon = new GraphicsButton(":/source/picture/power/u_hollowpoint", QPointF(320 * u_sign + 280, 160), this);
        u_desc->setPlainText("空尖子弹 +25%伤害");
        connect(u_icon, &GraphicsButton::mouseClicked, this, &UpPower::l_hollowpoint);
        break;
    case 6:
        u_icon = new GraphicsButton(":/source/picture/power/u_doubleshot", QPointF(320 * u_sign + 280, 160), this);
        u_desc->setPlainText("双射! +1子弹 -10%伤害");
        connect(u_icon, &GraphicsButton::mouseClicked, this, &UpPower::l_doubleshot);
        break;
    case 7:
        u_icon = new GraphicsButton(":/source/picture/power/u_heavybarrel", QPointF(320 * u_sign + 280, 160), this);
        u_desc->setPlainText("重型枪管 +40%伤害 -20%射速");
        connect(u_icon, &GraphicsButton::mouseClicked, this, &UpPower::l_heavybarrel);
        break;
    case 8:
        u_icon = new GraphicsButton(":/source/picture/power/u_reaper", QPointF(320 * u_sign + 280, 160), this);
        u_desc->setPlainText("收割者 +15%伤害 +1穿透");
        connect(u_icon, &GraphicsButton::mouseClicked, this, &UpPower::l_reaper);
        break;
    case 9:
        u_icon = new GraphicsButton(":/source/picture/power/u_fasthand", QPointF(320 * u_sign + 280, 160), this);
        u_desc->setPlainText("秒男? +15%射速");
        connect(u_icon, &GraphicsButton::mouseClicked, this, &UpPower::l_fasthand);
        break;
    case 10:
        u_icon = new GraphicsButton("::/source/picture/power/u_overload", QPointF(320 * u_sign + 280, 160), this);
        u_desc->setPlainText("超超超载 +20%射速 +30%扩散");
        connect(u_icon, &GraphicsButton::mouseClicked, this, &UpPower::l_overload);
        break;
    case 11:
        u_icon = new GraphicsButton(":/source/picture/power/u_lightbullet", QPointF(320 * u_sign + 280, 160), this);
        u_desc->setPlainText("轻型子弹 +20%射速  -10%伤害");
        connect(u_icon, &GraphicsButton::mouseClicked, this, &UpPower::l_lightbullet);
        break;
    case 12:
        u_icon = new GraphicsButton(":/source/picture/power/u_barrage", QPointF(320 * u_sign + 280, 160), this);
        u_desc->setPlainText("坚守阵地 站立时+35%射速");
        connect(u_icon, &GraphicsButton::mouseClicked, this, &UpPower::l_barrage);
        break;
    case 13:
        u_icon = new GraphicsButton(":/source/picture/power/u_streamline", QPointF(320 * u_sign + 280, 160), this);
        u_desc->setPlainText("流线构型  +30%弹道速度");
        connect(u_icon, &GraphicsButton::mouseClicked, this, &UpPower::l_streamline);
        break;
    case 14:
        u_icon = new GraphicsButton(":/source/picture/power/u_sniper", QPointF(320 * u_sign + 280, 160), this);
        u_desc->setPlainText("我们都是神枪手 +15%弹道速度 -20%扩散");
        connect(u_icon, &GraphicsButton::mouseClicked, this, &UpPower::l_sniper);
        break;
    case 15:
        u_icon = new GraphicsButton(":/source/picture/power/u_takeaim", QPointF(320 * u_sign + 280, 160), this);
        u_desc->setPlainText("我才是真的准勒 -50%扩散  -10%射速");
        connect(u_icon, &GraphicsButton::mouseClicked, this, &UpPower::l_takeaim);
        break;
    case 16:
        u_icon = new GraphicsButton(":/source/picture/power/u_pierecinground", QPointF(320 * u_sign + 280, 160), this);
        u_desc->setPlainText("穿甲弹 +2穿透");
        connect(u_icon, &GraphicsButton::mouseClicked, this, &UpPower::l_pierecinground);
        break;
    case 17:
        u_icon = new GraphicsButton(":/source/picture/power/u_haste", QPointF(320 * u_sign + 280, 160), this);
        u_desc->setPlainText("疾行 +15%移速");
        connect(u_icon, &GraphicsButton::mouseClicked, this, &UpPower::l_haste);
        break;
    case 18:
        u_icon = new GraphicsButton(":/source/picture/power/u_overspeed", QPointF(320 * u_sign + 280, 160), this);
        u_desc->setPlainText("超超超射 +25%移速 +20%扩散");
        connect(u_icon, &GraphicsButton::mouseClicked, this, &UpPower::l_overspeed);
        break;
    case 19:
        u_icon = new GraphicsButton(":/source/picture/power/u_runngun", QPointF(320 * u_sign + 280, 160), this);
        u_desc->setPlainText("移动射击 +10%移速 +10%射速");
        connect(u_icon, &GraphicsButton::mouseClicked, this, &UpPower::l_runngun);
        break;
    case 20:
        u_icon = new GraphicsButton(":/source/picture/power/u_inthewind", QPointF(320 * u_sign + 280, 160), this);
        u_desc->setPlainText("风行 30s内未受伤 +30%射速 +20%移速");
        connect(u_icon, &GraphicsButton::mouseClicked, this, &UpPower::l_inthewind);
        break;
    default:
        u_icon = new GraphicsButton(":/source/picture/power/u_void", QPointF(320 * u_sign + 280, 160), this);
        u_desc->setPlainText("???:坏了 空军");
        break;
    }
    u_desc->setPos(640 - u_desc->boundingRect().width() / 2, 400);
    u_icon->setScale(2.5);
}

void UpPower::l_vitality()//活力提升 +2HP
{
    u_player->setMaxHP(u_player->getMaxHP() + 2);
    u_player->setHP(u_player->getHP() + 2);
    setU_vitality(true);
}

void UpPower::l_giant()//咬自己一口! 巨人化 +4HP +25%体型
{
    u_player->setMaxHP(u_player->getMaxHP() + 4);
    u_player->setHP(u_player->getHP() + 4);
    u_player->setScale(u_player->scale() * 1.25);
}

void UpPower::l_dodge()//无影步  +30%闪避
{
    u_player->setDodge(u_player->getDodge() + 30);
    setU_giant(true);
}

void UpPower::l_regeneration()//自我疗愈 60s/+1HP
{
    u_player->setIs_regen(true);
    setU_regeneration(true);
}

void UpPower::l_hollowpoint()//空尖子弹 +25%伤害
{
   u_firearm->setDamageBoost(u_firearm->getDamageBoost() * 1.25);
    setU_hollowpoint(true);
}

void UpPower::l_doubleshot()//双射! +1子弹 -10%伤害
{
    u_firearm->setRoundBoost(u_firearm->getRoundBoost() + 1);
    u_firearm->setDamageBoost(u_firearm->getDamageBoost() * 0.9);
    setU_doubleshot(true);
}

void UpPower::l_heavybarrel()//重型枪管 +40%伤害 -20%射速
{
    u_firearm->setDamageBoost(u_firearm->getDamageBoost() * 1.40);
    u_firearm->setFireRateBoost(u_firearm->getFireRateBoost() * 0.8);
    setU_heavybarrel(true);
}

void UpPower::l_reaper()//收割者 +15%伤害 +1穿透
{
    u_firearm->setDamageBoost(u_firearm->getDamageBoost() * 0.15);
    u_firearm->setPenetration(u_firearm->getPenetration() + 1);
    setU_pierecinground(true);
}

void UpPower::l_fasthand()//秒男? +15%射速
{
    u_firearm->setFireRateBoost(u_firearm->getFireRateBoost() * 1.15);
    setU_fasthand(true);
}

void UpPower::l_overload()//超超超载 +20%射速 +30%扩散
{
    u_firearm->setFireRateBoost(u_firearm->getFireRateBoost() * 1.2);
    u_firearm->setSpread(u_firearm->getSpread() * 1.3);
    setU_overload(true);
}

void UpPower::l_lightbullet()//轻型子弹 +20%射速  -10%伤害
{
    u_firearm->setFireRateBoost(u_firearm->getFireRateBoost() * 1.2);
    u_firearm->setDamageBoost(u_firearm->getDamageBoost() * 0.9);
    setU_lightbullet(true);
}

void UpPower::l_barrage()//坚守阵地 站立时+35%射速
{
    u_firearm->setBarrage(true);//相应枪类里有计算公式
    setU_barrage(true);
}

void UpPower::l_streamline()//流线构型  +30%弹道速度
{
    u_firearm->setSpeedBoost(u_firearm->getSpeedBoost() * 0.3);
    setU_streamline(true);
}

void UpPower::l_sniper()//我们都是神枪手 +15%弹道速度 -20%扩散
{
    u_firearm->setSpeedBoost(u_firearm->getSpeedBoost() * 1.15);
    u_firearm->setSpread(u_firearm->getSpread() * 0.8);
    setU_sniper(true);
}

void UpPower::l_takeaim()//我才是真的准勒 -50%扩散  -10%射速
{
    u_firearm->setSpread(u_firearm->getSpread() * 0.5);
    u_firearm->setFireRateBoost(u_firearm->getFireRateBoost() * 0.9);
    setU_takeaim(true);
}

void UpPower::l_pierecinground()//穿甲弹 +2穿透
{
    u_firearm->setPenetration(u_firearm->getPenetration() + 2);
    setU_pierecinground(true);
}

void UpPower::l_haste()//疾行 +15%移速
{
    u_player->setSpeed_boost(u_player->getSpeed_boost() * 1.15);
    setU_haste(true);
}

void UpPower::l_overspeed()//超超超射 +25%移速 +20%扩散
{
    u_player->setSpeed_boost(u_player->getSpeed_boost() * 1.25);
    u_firearm->setSpread(u_firearm->getSpread() * 1.2);
    setU_overspeed(true);
}

void UpPower::l_runngun()//移动射击 +10%移速 +10%射速
{
    u_player->setSpeed_boost(u_player->getSpeed_boost() * 1.10);
    u_firearm->setFireRateBoost(u_firearm->getFireRateBoost() * 1.1);
    setU_runngun(true);
}

void UpPower::l_inthewind()//风行 30s内未受伤 +30%射速 +20%移速
{
    u_player->setU_inthewind(true);//相应枪类里有计算公式
    setU_inthewind(true);
}
