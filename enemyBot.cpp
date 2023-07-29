
#include "enemyBot.h"

EnemyBot::EnemyBot(Player *player, QGraphicsScene *scene,QObject *parent)
    : EnemyBase{player,scene,parent}
{
   //加载动画
    eb_movie = new QMovie(":/source/picture/enemy/en_bot.gif");
    eb_movie->setParent(this);
    eb_movie->setSpeed(50);
    eb_movie->start();
    setScale(3.5);
    setTransformOriginPoint(8, 10);
    //数据
    e_HP = 40;
    e_xp = 1;
    e_speed =1;
}

void EnemyBot::load()
{
    QImage img(eb_movie->currentImage());//获取图像
    if (is_hurt) {
        uchar *pixels = img.bits();
        int width = img.width();
        int height = img.height();
        int bytesPerLine = img.bytesPerLine();
        for (int y = 0; y < height; ++y) {
            uchar *line = pixels + y * bytesPerLine;//每行字节数
            for (int x = 0; x < width; ++x) {
                ////像素数据是以RGBA格式存储的，每个像素占用4个字节。设置颜色由三个数据确定
                uchar alpha = line[x * 4 + 3];
                if (alpha != 0) { //255.255.255  白色
                    line[x * 4] = 255;
                    line[x * 4 + 1] = 255;
                    line[x * 4 + 2] = 255;
                }
            }
        }
    }
    qreal angle = QLineF(pos(), e_player->pos()).angle();
    if ( (angle > 90 && angle < 270) || (angle < -90 && angle > -270)){
        img.mirror(true, false);//翻转图像
    }
    setPixmap(QPixmap::fromImage(img));
}
