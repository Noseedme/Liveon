
#include "enemyBotElite.h"

EnemyBotElite::EnemyBotElite(Player *player, QGraphicsScene *scene, QObject *parent)
    : EnemyBase{player, scene, parent}
{
    // 加载动画
    ebe_movie = new QMovie(":/source/picture/enemy/en_bot_elite.gif");
    ebe_movie->setParent(this);
    ebe_movie->setSpeed(50);
    ebe_movie->start();

    setScale(4.5);
    setTransformOriginPoint(8, 10);
    // 基本数据
    e_HP = 80;
    e_xp = 3;
    e_speed = 2;

}

void EnemyBotElite::load()
{
    QImage img(ebe_movie->currentImage());
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
    qreal angle = QLineF(pos(), e_player->pos()).angle();
    if ( (angle > 90 && angle < 270) || (angle < -90 && angle > -270)){
        img.mirror(true, false);
    }
    setPixmap(QPixmap::fromImage(img));
}
