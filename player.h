
#ifndef PLAYER_H
#define PLAYER_H


#include <QObject>
#include <QVector2D>//向量
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QPointF>
#include <QFont>
#include <QPixmap>
#include <QTimer>
#include <QMovie>//用于显示没有声音的简单动画
#include <QSoundEffect>
#include <QUrl>

class Player : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
     Player(QGraphicsView *view, QObject *parent = nullptr);

    void addVelocity(int dx, int dy);//add速度
    void setVelocityX(int dx);//setX速度
    void setVelocityY(int dy);
    void updatePos();//更新位置
    void regen();//回复

    QPointF posUpdate();

    void hurt();
    void resetInvincible();//重置无敌

    // 数据接口
    int getHP();
    void setHP(int hp);
    double getPickupRange();//get 收集经验范围
    int getExp();
    void setExp(int xp);

    qreal getSpeed(); //qreal Windows double Linu float
    void setSpeed(qreal sp);

    void pickupExp(int xp);//收集经验
    void load(); // 加载贴图

    qreal getDodge() const;//回避
    void setDodge(qreal newDodge);

    int getMaxHP() const;
    void setMaxHP(int newMax_hp);

    void setIs_regen(bool newIs_regen);//是否回复

    qreal getInvincible_time() const;//重生时间
    void setInvincible_time(qreal newInvincible_time);

    qreal getSpeed_boost() const;//get速度增加数据
    void setSpeed_boost(qreal newSpeed_boost);

    bool getIs_still() const;//是否静止

    bool getU_inthewind() const;
    void setU_inthewind(bool newU_inthewind);

    void inTheWind();

    bool getIs_inthewind() const;

signals:
    void playerHurt();
    void playerDeath();
    void playerRegen();

private:
    QVector2D p_velocity;
    int MaxHP;
    int p_HP;
    const qreal speed;
    int exp;
    qreal pickup_range;
    qreal speed_boost;
    qreal dodge;
    bool is_regen = false;
    int regen_count = 0;


    bool is_invincible;
    QTimer *p_invincibleTimer;
    qreal invincible_time;

    bool u_inthewind = false;
    bool is_inthewind = false;
    int inthewind_count = 0;

    QGraphicsTextItem *m_healthBar;
    QGraphicsView *m_view;

    QMovie *mv_idle;
    QMovie *mv_run;

    QRectF mapBounds;
    QRectF pillarBounds1;
    QRectF pillarBounds2;
    QRectF pillarBounds3;
    QRectF pillarBounds4;
    QRectF pillarBounds5;

    QSoundEffect *sef_hurt;


};

#endif // PLAYER_H
