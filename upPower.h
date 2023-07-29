
#ifndef UPPOWER_H
#define UPPOWER_H


#include <QObject>
#include <QGraphicsPathItem>
#include <QGraphicsTextItem>
#include <QTimer>
#include <QFontDatabase>
#include <QGraphicsScene>
#include <QRandomGenerator>
#include "GraphicsButton.h"
#include "player.h"
#include "firearmBase.h"

class UpPower : public QObject
{
    Q_OBJECT
public:
    explicit UpPower(int s, int index, Player *player, FirearmBase *firearm, QGraphicsScene *scene,QObject *parent = nullptr);
    ~UpPower();


    static void resetAll();//重置all

    static bool getU_vitality();//活力提升 +2HP
    static void setU_vitality(bool newU_vitality);

    static bool getU_giant(); //咬自己一口! 巨人化 +4HP +25%体型
    static void setU_giant(bool newU_giant);

    static bool getU_dodge();//无影步  +30%闪避
    static void setU_dodge(bool newU_dodge);

    static bool getU_regeneration();//自我疗愈 60s/+1HP
    static void setU_regeneration(bool newU_regeneration);

    static bool getU_hollowpoint();//空尖子弹 +25%伤害
    static void setU_hollowpoint(bool newU_hollowpoint);

    static bool getU_doubleshot();//双射! +1子弹 -10%伤害
    static void setU_doubleshot(bool newU_doubleshot);

    static bool getU_heavybarrel();//重型枪管 +40%伤害 -20%射速
    static void setU_heavybarrel(bool newU_heavybarrel);

    static bool getU_reaper();//收割者 +15%伤害 +1穿透
    static void setU_reaper(bool newU_reaper);

    static bool getU_fasthand();//秒男? +15%射速
    static void setU_fasthand(bool newU_fasthand);

    static bool getU_overload();//超超超载 +20%射速 +30%扩散
    static void setU_overload(bool newU_overload);

    static bool getU_lightbullet();//轻型子弹 +20%射速  -10%伤害
    static void setU_lightbullet(bool newU_lightbullet);

    static bool getU_barrage();//坚守阵地 站立时+35%射速
    static void setU_barrage(bool newU_barrage);

    static bool getU_streamline();//流线构型  +30%弹道速度
    static void setU_streamline(bool newU_streamline);

    static bool getU_sniper();//我们都是神枪手 +15%弹道速度 -20%扩散
    static void setU_sniper(bool newU_sniper);

    static bool getU_takeaim();//我才是真的准勒 -50%扩散  -10%射速
    static void setU_takeaim(bool newU_takeaim);

    static bool getU_pierecinground();//穿甲弹 +2穿透
    static void setU_pierecinground(bool newU_pierecinground);

    static bool getU_haste();//疾行 +15%移速
    static void setU_haste(bool newU_haste);

    static bool getU_overspeed();//超超超射 +25%移速 +20%扩散
    static void setU_overspeed(bool newU_overspeed);

    static bool getU_runngun();//移动射击 +10%移速 +10%射速
    static void setU_runngun(bool newU_runngun);

    static bool getU_inthewind();//风行 30s内未受伤 +30%射速 +20%移速
    static void setU_inthewind(bool newU_inthewind);

signals:
    void upPowerSelected();

private:
    int u_sign;
    int up_index;
    Player *u_player;
    FirearmBase *u_firearm;

    QGraphicsScene *u_scene;

    GraphicsButton *u_icon;
    QGraphicsTextItem *u_desc;

    void hoverEnter();
    void hoverLeave();
    void mouseClicked();
    void setUpPower(int  u_index);

    void l_vitality();//活力提升 +2HP
    void l_giant();//咬自己一口! 巨人化 +4HP +25%体型
    void l_dodge();//无影步  +30%闪避
    void l_regeneration();//自我疗愈 60s/+1HP

    void l_hollowpoint();//空尖子弹 +25%伤害
    void l_doubleshot();//双射! +1子弹 -10%伤害
    void l_heavybarrel();//重型枪管 +40%伤害 -20%射速
    void l_reaper();//收割者 +15%伤害 +1穿透

    void l_fasthand();//秒男? +15%射速
    void l_overload();//超超超载 +20%射速 +30%扩散
    void l_lightbullet();//轻型子弹 +20%射速  -10%伤害
    void l_barrage();//坚守阵地 站立时+35%射速

    void l_streamline();//流线构型  +30%弹道速度
    void l_sniper();//我们都是神枪手 +15%弹道速度 -20%扩散
    void l_takeaim();//我才是真的准勒 -50%扩散  -10%射速
    void l_pierecinground();//穿甲弹 +2穿透

    void l_haste();//疾行 +15%移速
    void l_overspeed();//超超超射 +25%移速 +20%扩散
    void l_runngun();//移动射击 +10%移速 +10%射速
    void l_inthewind();//风行 30s内未受伤 +30%射速 +20%移速

    static bool u_vitality;
    static bool u_giant;
    static bool u_dodge;
    static bool u_regeneration;

    static bool u_hollowpoint;
    static bool u_doubleshot;
    static bool u_heavybarrel;
    static bool u_reaper;

    static bool u_fasthand;
    static bool u_overload;
    static bool u_lightbullet;
    static bool u_barrage;

    static bool u_streamline;
    static bool u_sniper;
    static bool u_takeaim;
    static bool u_pierecinground;

    static bool u_haste;
    static bool u_overspeed;
    static bool u_runngun;
    static bool u_inthewind;

};

#endif // UPGRADEMOD_H
