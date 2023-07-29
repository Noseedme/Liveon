
#include "player.h"
#include <QRandomGenerator>//随机数
Player::Player(QGraphicsView *view,QObject *parent)
    : QObject{parent} ,p_velocity(0,0),MaxHP(3),p_HP(3),
    speed(2.25), exp(0), pickup_range(100), speed_boost(1), dodge(0), is_invincible(false)
    ,invincible_time(1), m_view(view)
{
    //生成Player
    mv_idle = new QMovie(this);
    mv_idle->setFileName(":/source/player/mv_idle.gif");
    mv_idle->start();

    mv_run = new QMovie(this);
    mv_run->setFileName(":/source/player/mv_run.gif");
    mv_run->start();

    //模型设定
    load();//加载贴图
    setTransformOriginPoint(boundingRect().right() + 10,boundingRect().bottomRight().y() + 110);
    setPos(640 - boundingRect().width(), 360 - boundingRect().height());
    setScale(1.6);

    //无敌帧
    p_invincibleTimer = new QTimer(this);
    connect(p_invincibleTimer, &QTimer::timeout, this, &Player::resetInvincible);

    //地图边界

    // 地图边界
    mapBounds = QRectF(650, 565, 3500, 1430);
    pillarBounds1 = QRectF(880, 1022, 150, 40);
    pillarBounds2 = QRectF(880, 1810, 150, 40);
    pillarBounds3 = QRectF(2270, 1300, 300, 100);
    pillarBounds4 = QRectF(3770, 1020, 150, 40);
    pillarBounds5 = QRectF(3770, 1810, 150, 40);


    // 受伤音效初始化
    sef_hurt = new QSoundEffect(this);
    sef_hurt->setSource(QUrl(":/source/soundEffect/player_hurt.wav"));

}
void Player::addVelocity(int dx, int dy)//add速度
{
    // if 语句用来防止速度叠加
    if (p_velocity.x() != dx)
        p_velocity.setX(p_velocity.x() + dx);
    if (p_velocity.y() != dy)
        p_velocity.setY(p_velocity.y() + dy);

}
void Player::setVelocityX(int dx)//setX速度
{
    p_velocity.setX(dx);
}
void Player::setVelocityY(int dy)
{
    p_velocity.setY(dy);
}
void Player::updatePos()//更新位置
{
    qreal speed_reduce = 1;//减速
    if (p_velocity.length() != 0) speed_reduce = p_velocity.length();
    //计算方法 当前位置+(向量坐标x or y 乘 速度 乘 速度推进 乘 0.3 * 风行)/速度抑制
    QPointF newPos = this->pos() + QPointF(p_velocity.x() * speed * (speed_boost + 0.3 * is_inthewind) / speed_reduce, p_velocity.y() * speed * speed_boost / speed_reduce);
    if (!mapBounds.contains(newPos)//判断点是否在边界区域
        || pillarBounds1.contains(newPos)
        || pillarBounds2.contains(newPos)
        || pillarBounds3.contains(newPos)
        || pillarBounds4.contains(newPos)
        || pillarBounds5.contains(newPos))
        newPos = this->pos() + QPointF(p_velocity.x() * speed * (speed_boost + 0.3 * is_inthewind) / speed_reduce, 0);
    if (!mapBounds.contains(newPos)
        || pillarBounds1.contains(newPos)
        || pillarBounds2.contains(newPos)
        || pillarBounds3.contains(newPos)
        || pillarBounds4.contains(newPos)
        || pillarBounds5.contains(newPos))
        newPos = this->pos() + QPointF(0, p_velocity.y() * speed * (speed_boost + 0.3 * is_inthewind) / speed_reduce);
    if (!mapBounds.contains(newPos)
        || pillarBounds1.contains(newPos)
        || pillarBounds2.contains(newPos)
        || pillarBounds3.contains(newPos)
        || pillarBounds4.contains(newPos)
        || pillarBounds5.contains(newPos))
        newPos = this->pos() + QPointF(0, 0);
    setPos(newPos);
}
void Player::regen()//回复
{
    if (!is_regen || p_HP >= MaxHP) return;
    regen_count++;
    if (regen_count < 3000) return;
    regen_count = 0;
    p_HP++;
    emit playerRegen();
}

QPointF Player::posUpdate()
{
    qreal speed_reduce = 1;//减速
    if (p_velocity.length() != 0) speed_reduce = p_velocity.length();
    //计算方法 当前位置+(向量坐标x or y 乘 速度 乘 速度推进 乘 0.3 * 风行)/速度抑制
    QPointF newPos = this->pos() + QPointF(p_velocity.x() * speed * (speed_boost + 0.3 * is_inthewind) / speed_reduce, p_velocity.y() * speed * speed_boost / speed_reduce);
    if (!mapBounds.contains(newPos)//判断点是否在边界区域
        || pillarBounds1.contains(newPos)
        || pillarBounds2.contains(newPos)
        || pillarBounds3.contains(newPos)
        || pillarBounds4.contains(newPos)
        || pillarBounds5.contains(newPos))
        newPos = this->pos() + QPointF(p_velocity.x() * speed * (speed_boost + 0.3 * is_inthewind) / speed_reduce, 0);
    if (!mapBounds.contains(newPos)
        || pillarBounds1.contains(newPos)
        || pillarBounds2.contains(newPos)
        || pillarBounds3.contains(newPos)
        || pillarBounds4.contains(newPos)
        || pillarBounds5.contains(newPos))
        newPos = this->pos() + QPointF(0, p_velocity.y() * speed * (speed_boost + 0.3 * is_inthewind) / speed_reduce);
    if (!mapBounds.contains(newPos)
        || pillarBounds1.contains(newPos)
        || pillarBounds2.contains(newPos)
        || pillarBounds3.contains(newPos)
        || pillarBounds4.contains(newPos)
        || pillarBounds5.contains(newPos))
        newPos = this->pos() + QPointF(0, 0);
    return pos() - newPos;
}

void Player::hurt()
{
    if (is_invincible){//是否无敌
        return;
    }
    sef_hurt->play();//播放受伤音效
    //闪避几率
    int dodge_chance = QRandomGenerator::global()->bounded(0, 100);//0~100随机数
    if (dodge_chance > dodge) {
        inthewind_count = 0;
        p_HP--;
        emit playerHurt();
    }
    is_invincible = true;
    p_invincibleTimer->start(1000 * invincible_time);
    if (p_HP <= 0){
        emit playerDeath();
    }
}
void Player::resetInvincible()//重置无敌
{
    is_invincible = false;
    p_invincibleTimer->stop();
}

// 数据接口
int Player::getHP()
{
    return p_HP;
}
void Player::setHP(int hp)
{
    p_HP = hp;
}
double Player::getPickupRange()//get 收集经验范围
{
    return pickup_range;
}
int Player::getExp()
{
    return exp;
}
void Player::setExp(int xp)
{
    exp = xp;
}

qreal Player::getSpeed()
{
    return speed_boost;
}
void Player::setSpeed(qreal sp){
    speed_boost = sp;
}

void Player::pickupExp(int xp)//收集经验
{
    exp += xp;
}
void Player::load() // 加载贴图
{
    if (p_velocity.x() == 0 && p_velocity.y() == 0){
        QImage img(mv_idle->currentPixmap().toImage());
        if (m_view->mapFromGlobal(QCursor::pos()).x() < 640){
            img.mirror(true, false);//翻转
        }
        if (is_invincible) { //将人物贴图置为白色
            uchar *pixels = img.bits();
            int width = img.width();
            int height = img.height();
            int bytesPerLine = img.bytesPerLine();//每行字节数
            for (int y = 0; y < height; ++y) {
                uchar *line = pixels + y * bytesPerLine;
                for (int x = 0; x < width; ++x) {
                    uchar alpha = line[x * 4 + 3];//像素数据是以RGBA格式存储的，每个像素占用4个字节。设置颜色由三个数据确定
                    if (alpha != 0) {
                        line[x * 4] = 255;
                        line[x * 4 + 1] = 255;
                        line[x * 4 + 2] = 255;
                    }
                }
            }
        }
        QPixmap pix(QPixmap::fromImage(img));
        setPixmap(pix);
    } else {
        QImage img(mv_run->currentPixmap().toImage());
        if (p_velocity.x() < 0){
            img.mirror(true, false);
        }
        if (is_invincible) {
            uchar *pixels = img.bits();
            int width = img.width();
            int height = img.height();
            int bytesPerLine = img.bytesPerLine();
            for (int y = 0; y < height; ++y) {
                uchar *line = pixels + y * bytesPerLine;
                for (int x = 0; x < width; ++x) {
                    uchar alpha = line[x * 4 + 3];
                    if (alpha != 0) {
                        line[x * 4] = 255;
                        line[x * 4 + 1] = 255;
                        line[x * 4 + 2] = 255;
                    }
                }
            }
        }
        QPixmap pix(QPixmap::fromImage(img));
        setPixmap(pix);
    }
}

qreal Player::getDodge() const//回避
{
    return dodge;
}
void Player::setDodge(qreal newDodge)
{
     dodge = newDodge;
}

int Player::getMaxHP() const
{
    return MaxHP;
}
void Player::setMaxHP(int newMaxHP)
{
    MaxHP = newMaxHP;
}

void Player::setIs_regen(bool newIs_regen)//是否回复
{
    is_regen = newIs_regen;
}

qreal Player::getInvincible_time() const//get无敌时间
{
    return invincible_time;
}
void Player::setInvincible_time(qreal newInvincible_time)
{
    invincible_time = newInvincible_time;
}

qreal Player::getSpeed_boost() const//增速
{
    return speed_boost;
}
void Player::setSpeed_boost(qreal newSpeed_boost)
{
    speed_boost = newSpeed_boost;
}

bool Player::getIs_still() const//是否静止
{
    if (p_velocity.x() == 0 && p_velocity.y() == 0) return true;
    else return false;
}

bool Player::getU_inthewind() const
{
    return u_inthewind;
}
void Player::setU_inthewind(bool newU_inthewind)
{
    u_inthewind = newU_inthewind;
}

void Player::inTheWind()//风行技能
{
    if (u_inthewind == false) return;
    if (inthewind_count < 1500) {
        is_inthewind = false;
        inthewind_count++;
        return;
    } else {
        is_inthewind = true;
        return;
    }
}

bool Player::getIs_inthewind() const
{
    return is_inthewind;
}
