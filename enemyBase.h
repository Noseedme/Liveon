
#ifndef ENEMYBASE_H
#define ENEMYBASE_H


#include <QObject>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QSoundEffect>
#include <QUrl>
#include "player.h"
#include "exp.h"

class EnemyBase : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit EnemyBase(Player *player, QGraphicsScene *scene, QObject *parent = nullptr);
    void hurt(qreal damage);
    static QTimer *e_timer;
    static QSoundEffect *sef_enemy_hurt;
signals:
     void enemyDeath();
protected:
    Player *e_player;
    qreal e_speed;
    qreal e_HP;
    int e_xp;
    QGraphicsScene *e_scene;
    QTimer hurt_timer;
    bool is_hurt;

    virtual void death();
    virtual void mobMove();//群移动
    void hitBoxCheck();//检查玩家受击
    virtual void load() = 0;//受到伤害效果
    void hurt_reload();


    static QRectF pillarBounds1;
    static QRectF pillarBounds2;
    static QRectF pillarBounds3;
    static QRectF pillarBounds4;
    static QRectF pillarBounds5;
};

#endif // ENEMYBASE_H
