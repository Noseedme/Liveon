
#ifndef STARTGAME_H
#define STARTGAME_H


#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QFontDatabase>
#include <QGraphicsPixmapItem>
#include <QPushButton>
#include <QKeyEvent>
#include <QRandomGenerator>
#include <QTimer>
#include <QList>
#include <QLabel>
#include <QMouseEvent>
#include <QSettings>
#include <QApplication>
#include <QSoundEffect>

#include "player.h"
#include "archive.h"
#include "hpLabel.h"
#include "firearmBase.h"

class StartGame : public QGraphicsView
{
    Q_OBJECT
public:
    StartGame(const QString &firearm,const QString &load_archive = "none");
    void gamePause();
    void gameContinue();


signals:

    void EndGame();
    void Restart();
protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
private:
    //定时器
    QTimer *main_timer;
    QTimer *phase_timer;
    //场景
    void updateBackground();
    QGraphicsScene *m_scene;
    QGraphicsPixmapItem *m_background;

    //武器
    FirearmBase *m_firearm;
    QString firearm_type;
    //玩家
    Player *m_player;
    QList<HPLabel*> hp_list;
    void setHPBar();
    //敌人生成
    void enemyGenerator();

    //游戏阶段
    QPushButton *pause_btn;
    void phaseUp();//随游戏进行难度升高
    int phase;
    int phase_count;

    int enemy_gen_count; // 敌人生成辅助计数器
    int bullet_gen_count; // 子弹生成辅助计数器
    qreal enemy_generate_rate;//敌人产生速率
    qreal melee_enemy_rate;//近战敌人比率
    qreal ranged_enemy_rate;//远程敌人比率
    qreal charge_enemy_rate;// 改变敌人生成比率
    qreal explosive_enemy_rate;//爆炸
    qreal elite_enemy_rate;//精英

    // 倒计时
    int countdown_count;
    QGraphicsTextItem *countdown_text;
    QTime countdown_time;
    void updateCountdown();

    // 角色升级
    int level;
    void levelCheck();
    QList<int> upPowerGenerator();
    void levelUp();

    // 经验条
    QGraphicsRectItem *exp_bar_bg;
    QGraphicsRectItem *exp_bar;
    QGraphicsTextItem *level_text;
    void setExpBar();

    // 金币
    int data_count;
    int data_money;
    int data_collector;//采集
    QGraphicsTextItem *data_text;
    void dataIncrement();
    QSettings *settings;

    // 存档
    QSettings *archive[6];
    void loadArchive(int sign);
    void saveArchive(int sign);
    void showArchive();
    void hideArchive();
    Archive *archive_mod[6];

    // 音效和bgm
    QSoundEffect *bgm_player;
    QSoundEffect *sef_respawn;
    //边界
    QRectF pillarBounds1 = QRectF(880, 1022, 150, 40);
    QRectF pillarBounds2 = QRectF(880, 1810, 150, 40);
    QRectF pillarBounds3 = QRectF(2270, 1300, 300, 100);
    QRectF pillarBounds4 = QRectF(3770, 1020, 150, 40);
    QRectF pillarBounds5 = QRectF(3770, 1810, 150, 40);


    // 游戏结束
    QGraphicsScene *end_scene;
    void endgame_lose();
    void endgame_win();

};

#endif // STARTGAME_H
