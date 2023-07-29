
#ifndef FIREARMBASE_H
#define FIREARMBASE_H


#include <QObject>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QTimer>
#include <QSoundEffect>
#include <QUrl>

#include "player.h"
class FirearmBase : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit FirearmBase(Player *player, QGraphicsScene *scene,QObject *parent = nullptr);

    void updatePos();//更新位置
    void rotateToCursor(const QPointF& target);//旋转枪口的方向到光标
    void setFireRateBoost(qreal fire);//射速增加
    void setDamageBoost(qreal dmg);//伤害增加
    void setSpeedBoost(qreal sp);//速度增加

    virtual void fire() = 0;
    void load();//贴图
    void fire_on();
    void fire_off();

    // 数据接口
    qreal getFireRateBoost();
    qreal getDamageBoost();
    qreal getSpeedBoost();

    static QTimer *fb_timer;

    int getRoundBoost() const;//子弹数量
    void setRoundBoost(int newRoundBoost);

    qreal getSpread() const;//扩散
    void setSpread(qreal newSpread);

    int getPenetration() const;//get穿透
    void setPenetration(int newPenetration);

    bool getBarrage() const;//get 是否连续开火
    void setBarrage(bool newBarrage);
signals:
protected:
    QGraphicsScene *fb_scene;
    Player *fb_player;
    qreal fireRateBoost;
    qreal damageBoost;
    qreal speedBoost;
    int roundBoost;
    qreal spread;
    int penetration;
    bool barrage;

    QPixmap pix;
    int fireCount;
    bool is_fire;

    // 音效
    QSoundEffect *sef_fire;
};

#endif // FIREARMBASE_H
