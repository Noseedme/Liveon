
#include "enemyRangedDrone.h"

#include "bulletEnemy.h"

EnemyRangedDrone::EnemyRangedDrone(Player *player, QGraphicsScene *scene, QObject *parent)
    : EnemyRangedBase{player, scene, parent}, attack_max(400)
{
    pix = QPixmap(":/source/picture/enemy/en_float.png");
    setPixmap(pix);
    setScale(5);
    setTransformOriginPoint(boundingRect().center());
    attack_count = 0;
    connect(e_timer, &QTimer::timeout, this, &EnemyRangedDrone::attack);

    e_HP = 30;
    e_xp = 1;
    e_speed = 0.5;
}

void EnemyRangedDrone::load()
{
    QImage img(pix.toImage());
    if (is_hurt) { //受击效果
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
    qreal angle = QLineF(pos(), e_player->pos()).angle();
    if ( (angle > 90 && angle < 270) || (angle < -90 && angle > -270)){
        img.mirror(true, false);//翻转
    }
    setPixmap(QPixmap::fromImage(img));
}

void EnemyRangedDrone::attack()
{
    attack_count++;
    qreal dist = QLineF(pos(), e_player->pos()).length();
    if (dist > 400) return;
    if (attack_count < attack_max) return;
    attack_count = 0;
    qreal angle = -QLineF(pos(), e_player->pos()).angle();
    // 3.1.0 速度 伤害 穿透
    BulletEnemy *bullet = new BulletEnemy(pos(), angle, 3, 1, 0, e_scene, e_player, e_scene);
    bullet->setScale(2);
    bullet->setParentItem(this->parentItem());
    e_scene->addItem(bullet);

}
