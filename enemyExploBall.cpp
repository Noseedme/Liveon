
#include "enemyExploBall.h"

EnemyExploBall::EnemyExploBall(Player *player, QGraphicsScene *scene, QObject *parent)
    : EnemyExploBase{player, scene, parent}
{
    exploRange = 32;
    exploDamage = 50;
    e_speed = 2;
    e_HP = 50;

    pix = QPixmap(":/source/picture/enemy/en_bullet.png");
    setPixmap(pix);
    setScale(4);
    setTransformOriginPoint(boundingRect().center());
    move_explosion = new QMovie(":/source/picture/enemy/explosion.gif");
    move_explosion->setParent(this);
}

void EnemyExploBall::load()//角色受到爆炸效果
{
    qreal angle = QLineF(pos(), e_player->pos()).angle();
    setRotation(-angle);//设置旋转
    QImage img(pix.toImage());
    if (is_hurt) {
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
    setPixmap(QPixmap::fromImage(img));
}

void EnemyExploBall::explode()//爆炸效果
{
    disconnect(e_timer, &QTimer::timeout, this, &EnemyExploBall::load);//disconnect 断开信号连接
    disconnect(e_timer, &QTimer::timeout, this, &EnemyExploBall::mobMove);
    connect(e_timer, &QTimer::timeout, this, &EnemyExploBall::enemyHitCheck);
    disconnect(this, &EnemyBase::enemyDeath, this, &EnemyExploBall::death);
    move_explosion->start();
    moveBy(-16, -16);
    setPixmap(move_explosion->currentPixmap());//设置爆炸的当前像素图。
    setTransformOriginPoint(boundingRect().center());
    connect(e_timer, &QTimer::timeout, this, [=]{
        disconnect(e_timer, &QTimer::timeout, this, &EnemyExploBall::hitBoxCheck);
        disconnect(e_timer, &QTimer::timeout, this, &EnemyExploBall::enemyHitCheck);
    });
    //函数在动画的每一帧改变时执行，用于更新图形项的像素图
    connect(move_explosion, &QMovie::frameChanged, this, [=](){
        setPixmap(move_explosion->currentPixmap());
    });
    //函数在动画播放完毕时执行，用于移除图形项并进行销毁
    connect(move_explosion, &QMovie::finished, this, [=](){
        e_scene->removeItem(this);
        deleteLater();
    });
}
