
#include "startGame.h"
#include <QFile>

#include "exp.h"

#include "bulletBase.h"

#include "enemyRangedDrone.h"
#include "enemyBot.h"
#include "enemyExploBall.h"
#include "enemyBotElite.h"

#include "enemyRangedDroneElite.h"
#include "upPower.h"
#include "firearmSmgun.h"
#include "firearmTrace.h"
#include "firearmShotgun.h"
#include "firearmSniper.h"

StartGame::StartGame(const QString &firearm, const QString &load_archive)
{   //字体
    QFontDatabase::addApplicationFont(":/source/font/fusion-pixel-proportional.ttf");
    // 生成场景
    setFixedSize(1280, 720);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//不可见滚动条
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_scene = new QGraphicsScene(this);

    // 背景生成
    QPixmap background_pic(":/source/picture/startGame/startBackground.png");
    m_background = new QGraphicsPixmapItem;
    m_background->setPixmap(background_pic);
    m_background->setZValue(-0x3ffffff);//越小的值在最下面
    m_background->moveBy(160,30);
    m_scene->addItem(m_background);


    //玩家生成
    m_player = new Player(this, this);
    m_player->setParentItem(m_background);
    connect(m_player, &Player::playerDeath, this, &StartGame::endgame_lose);

    // 移动player至地图中央
    m_player->moveBy(2400, 1350);
    m_background->moveBy(-2400, -1350);
    m_scene->addItem(m_player);

    //武器生成
    if (firearm == "smGun") m_firearm = new FirearmSmgun(m_player, m_scene, this);
    else if (firearm == "traceGun") m_firearm = new FirearmTrace(m_player, m_scene, this);
    else if (firearm == "shotGun") m_firearm = new FirearmShotgun(m_player, m_scene, this);
    else if (firearm == "sniperGun") m_firearm = new FirearmSniper(m_player, m_scene, this);
    m_firearm->setParentItem(m_background);
    m_scene->addItem(m_firearm);
    m_scene->setSceneRect(0, 0, 1280, 720);
    setScene(m_scene);

    // 背景音乐
    bgm_player = new QSoundEffect(this);
    bgm_player->setSource(QUrl::fromLocalFile(":/source/bgm/com.wav"));
    bgm_player->setLoopCount(0x3ffffff);
    bgm_player->setVolume(0.6);
    bgm_player->play();

    //经济设置
    settings = new QSettings("./game.ini", QSettings::IniFormat, this);
    data_money = settings->value("data", 0).toInt();
    // 读取样式表
    QFile file_sqr_pb(":/source/stystle/sqr_pb.qss");
    file_sqr_pb.open(QFile::ReadOnly);
    QString style_sqr_pb;
    if (file_sqr_pb.isOpen()) {
        style_sqr_pb = QLatin1String(file_sqr_pb.readAll());
        file_sqr_pb.close();
    }
    // 经济显示文本生成
    QString str("经济: ");
    str += QString::number(data_money);
    data_text = new QGraphicsTextItem(str);
    data_text->setDefaultTextColor(Qt::yellow);
    data_text->setFont(QFont("fusion pixel proportional", 16));
    data_text->setPos(50, 20);
    m_scene->addItem(data_text);

    // 角色血量升级
    int hp_increment = settings->value("HP Increment", 0).toInt();
    m_player->setMaxHP(m_player->getMaxHP() + hp_increment);
    m_player->setHP(m_player->getHP() + hp_increment);
    //枪口散射升级
    qreal muzzle_choke = settings->value("Muzzle Choke", 0).toInt() * qreal(0.2);
    m_firearm->setSpread(m_firearm->getSpread() * (qreal(1) - muzzle_choke));
    //采集升级
    data_collector = settings->value("Data Collector", 0).toInt();

    //计时器
    // 移动检测计时器
    main_timer = new QTimer(this);
    // player移动和贴图加载
    connect(main_timer, &QTimer::timeout, m_player, &Player::updatePos);
    connect(main_timer, &QTimer::timeout, m_player, &Player::load);
    connect(main_timer, &QTimer::timeout, m_player, &Player::inTheWind);//风行
    connect(main_timer, &QTimer::timeout, m_player, &Player::regen);//60s回复
    // 武器移动，加载贴图，开火
    connect(main_timer, &QTimer::timeout, m_firearm, &FirearmBase::updatePos);
    connect(main_timer, &QTimer::timeout, m_firearm, &FirearmBase::load);
    connect(main_timer, &QTimer::timeout, m_firearm, &FirearmBase::fire);
    // 背景移动
    connect(main_timer, &QTimer::timeout, this, &StartGame::updateBackground);
    // 敌人生成计时器
    connect(main_timer, &QTimer::timeout, this, &StartGame::enemyGenerator);
    // 敌人移动攻击计时器
    EnemyBase::e_timer = main_timer;
    // 子弹计时器
    BulletBase::b_timer = main_timer;
    // 经验计时器
    EXP::e_timer= main_timer;
    // 升级检测
    connect(main_timer, &QTimer::timeout, this, &StartGame::levelCheck);
    // 局外升级
    connect(main_timer, &QTimer::timeout, this, &StartGame::dataIncrement);
    //一个Qt GUI应用程序，仅有一个QApplication对象，负责管理应用程序的控制流和主设置
    connect(qApp, &QApplication::aboutToQuit, this, [=](){
        settings->setValue("data", data_money);
    });
    // 倒计时刷新
    connect(main_timer, &QTimer::timeout, this, &StartGame::updateCountdown);
    // 开始计时
    main_timer->start(10);

    // 血条生成
    setHPBar();
    connect(m_player, &Player::playerHurt, this, &StartGame::setHPBar);
    connect(m_player, &Player::playerRegen, this, &StartGame::setHPBar);

    // 游戏阶段初始化
    // 数据初始化
    enemy_generate_rate = 7.5;
    melee_enemy_rate = 100;
    ranged_enemy_rate = 0;
    charge_enemy_rate = 0;
    explosive_enemy_rate = 0;
    elite_enemy_rate = 0;
    // 计时器初始化
    connect(main_timer, &QTimer::timeout, this, &StartGame::phaseUp);
    // 倒计时初始化
    countdown_text = new QGraphicsTextItem();
    m_scene->addItem(countdown_text);
    countdown_text->setFont(QFont("fusion pixel proportional", 32));
    countdown_text->setPos(100, 80);
    countdown_text->setDefaultTextColor(Qt::white);
    countdown_time = QTime(0, 10, 0);//十分钟

    // 经验条生成
    // 经验条背景
    exp_bar_bg = new QGraphicsRectItem(0, 0, 400, 20);
    exp_bar_bg->setBrush(QColor(100, 100, 100));
    exp_bar_bg->setPen(QPen(QColor(0, 0, 0), 4));
    exp_bar_bg->setPos(440, 20);
    m_scene->addItem(exp_bar_bg);

    // 经验条
    exp_bar = new QGraphicsRectItem(0, 0, 0, 20);
    exp_bar->setBrush(QColor(0, 200, 255));
    exp_bar->setPos(440, 22);
    exp_bar->setRect(0, 0, 0, 16); // 初始化宽度为0
    m_scene->addItem(exp_bar);

    // 等级文本
    level_text = new QGraphicsTextItem("Level 1");
    level_text->setDefaultTextColor(Qt::white);
    level_text->setFont(QFont("fusion pixel proportional", 16));
    level_text->setPos(600, 30);
    m_scene->addItem(level_text);

    // 受击音效
    EnemyBase::sef_enemy_hurt = new QSoundEffect(this);
    EnemyBase::sef_enemy_hurt->setSource(QUrl(":/source/bgm/sounds_impact1.wav"));
    EnemyBase::sef_enemy_hurt->setVolume(0.15);

    // 复活音效
    sef_respawn = new QSoundEffect(this);
    sef_respawn->setSource(QUrl::fromLocalFile(":/source/bgm/com.wav"));
    sef_respawn->setVolume(0.4);

    // 载入存档
    for (int i = 0; i < 6; ++i) {
        QString fileName = QString("./archive_%1.ini").arg(i);
        archive[i] = new QSettings(fileName, QSettings::IniFormat, this);
    }
    if (load_archive == "none") return;
    else if (load_archive == "archive0") loadArchive(0);
    else if (load_archive == "archive1") loadArchive(1);
    else if (load_archive == "archive2") loadArchive(2);
    else if (load_archive == "archive3") loadArchive(3);
    else if (load_archive == "archive4") loadArchive(4);
    else if (load_archive == "archive5") loadArchive(5);

    // 暂停按键生成
    pause_btn = new QPushButton(this);
    connect(pause_btn, &QPushButton::clicked, this, [=](){
        gamePause();
        showArchive();
    });
    m_scene->addWidget(pause_btn);

}

void StartGame::gamePause()
{
    main_timer->stop();
    pause_btn->disconnect();
    connect(pause_btn, &QPushButton::clicked, this, [=](){
        hideArchive();
        gameContinue();
    });
}

void StartGame::gameContinue()
{
    main_timer->start();
    pause_btn->disconnect();
    connect(pause_btn, &QPushButton::clicked, this, [=](){
        gamePause();
        hideArchive();
    });
}

void StartGame::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_W:
        m_player->addVelocity(0, -1);
        break;
    case Qt::Key_S:
        m_player->addVelocity(0, 1);
        break;
    case Qt::Key_A:
        m_player->addVelocity(-1, 0);
        break;
    case Qt::Key_D:
        m_player->addVelocity(1, 0);
    default:
        break;
    }
}

void StartGame::keyReleaseEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_W:
        m_player->addVelocity(0, 1);
        break;
    case Qt::Key_S:
        m_player->addVelocity(0, -1);
        break;
    case Qt::Key_A:
        m_player->addVelocity(1, 0);
        break;
    case Qt::Key_D:
        m_player->addVelocity(-1, 0);
    default:
        break;
    }
}

void StartGame::mouseMoveEvent(QMouseEvent *event)
{
    m_firearm->rotateToCursor(event->pos());
    QGraphicsView::mouseMoveEvent(event);
}

void StartGame::mousePressEvent(QMouseEvent *event)
{
    switch (event->button()) {
    case Qt::LeftButton:
        m_firearm->fire_on();
        break;
    default:
        break;
    }
    // 将事件传递给视图
    QGraphicsView::mousePressEvent(event);
}

void StartGame::mouseReleaseEvent(QMouseEvent *event)
{
    switch (event->button()) {
    case Qt::LeftButton:
        m_firearm->fire_off();
        break;
    default:
        break;
    }
    // 将事件传递给视图
    QGraphicsView::mouseReleaseEvent(event);
}
void StartGame::updateBackground()//移动背景
{
    QPointF dis = m_player->posUpdate();
    m_background->moveBy(dis.x(), dis.y());
}

void StartGame::setHPBar()
{
    int health = m_player->getHP();
    int max_hp = m_player->getMaxHP();
    for (auto *p : hp_list) {
        if (p) p->deleteLater();
    }
    hp_list.clear();
    for (int i = 0; i < max_hp; ++i) {
        HPLabel *heart = new HPLabel(this);
        if (i >= health) heart->loseHP();
        heart->move(heart->x() - i*36, heart->y());
        hp_list.append(heart);
    }
}

void StartGame::enemyGenerator()
{
    enemy_gen_count++;
    if (enemy_gen_count < 1000 / enemy_generate_rate) return;
    enemy_gen_count = 0;
    // 随机生成敌人位置,直到满足生成条件
    QPointF enemyPos;
    qreal dist;
    do {
        enemyPos.setX(QRandomGenerator::global()->bounded(0, 4800));
        enemyPos.setY(QRandomGenerator::global()->bounded(0, 2700));
        dist = QLineF(m_player->pos(), enemyPos).length();

    } while (dist < 550
             || dist > 650
             || pillarBounds1.contains(enemyPos)
             || pillarBounds2.contains(enemyPos)
             || pillarBounds3.contains(enemyPos)
             || pillarBounds4.contains(enemyPos)
             || pillarBounds5.contains(enemyPos));   // 不在视野范围或过近时重新生成

    EnemyBase *enemy = nullptr;
    qreal random = QRandomGenerator::global()->bounded(0, 100);
    qreal ran_elite = QRandomGenerator::global()->bounded(0, 100);
    if (random <= melee_enemy_rate){
        if (ran_elite >= elite_enemy_rate) enemy = new EnemyBot(m_player, m_scene, this); // 生成近战敌人
        else enemy = new EnemyBotElite(m_player, m_scene, this);
    } else if (random > melee_enemy_rate && random <= melee_enemy_rate + ranged_enemy_rate){
        if (ran_elite >= elite_enemy_rate) enemy = new EnemyRangedDrone(m_player, m_scene, this); // 生成远程敌人
        else enemy = new EnemyRangedDroneElite(m_player, m_scene, this);
    } else if (random > melee_enemy_rate + ranged_enemy_rate && random <= melee_enemy_rate + ranged_enemy_rate + explosive_enemy_rate){
        enemy = new EnemyExploBall(m_player, m_scene, this);// 生成自爆敌人
    }
    if (!enemy) return;
    enemy->setParentItem(m_background);
    enemy->setPos(enemyPos);
    enemy->setZValue(1);
    // 将敌人添加到场景中
    m_scene->addItem(enemy);
}

void StartGame::phaseUp()//随游戏进行难度升高
{
    phase_count++;
    if (phase_count < 6000) return; // 60s
    phase_count = 0;
    phase++;
    switch (phase) {
    case 1:
        enemy_generate_rate = 10;
        melee_enemy_rate = 90;
        ranged_enemy_rate = 0;
        charge_enemy_rate = 0;
        explosive_enemy_rate = 10;
        elite_enemy_rate = 0;
        break;
    case 2:
        enemy_generate_rate = 10;
        melee_enemy_rate = 70;
        ranged_enemy_rate = 10;
        charge_enemy_rate = 0;
        explosive_enemy_rate = 20;
        elite_enemy_rate = 0;
        break;
    case 3:
        enemy_generate_rate = 12.5;
        melee_enemy_rate = 70;
        ranged_enemy_rate = 10;
        charge_enemy_rate = 0;
        explosive_enemy_rate = 20;
        elite_enemy_rate = 0;
        break;
    case 4:
        enemy_generate_rate = 15;
        melee_enemy_rate = 70;
        ranged_enemy_rate = 10;
        charge_enemy_rate = 0;
        explosive_enemy_rate = 20;
        elite_enemy_rate = 0;
        break;
    case 5:
        enemy_generate_rate = 15;
        melee_enemy_rate = 60;
        ranged_enemy_rate = 20;
        charge_enemy_rate = 0;
        explosive_enemy_rate = 20;
        elite_enemy_rate = 30;
        break;
    case 6:
        enemy_generate_rate = 20;
        melee_enemy_rate = 60;
        ranged_enemy_rate = 20;
        charge_enemy_rate = 0;
        explosive_enemy_rate = 20;
        elite_enemy_rate = 30;
        break;
    case 7:
        enemy_generate_rate = 20;
        melee_enemy_rate = 60;
        ranged_enemy_rate = 20;
        charge_enemy_rate = 0;
        explosive_enemy_rate = 20;
        elite_enemy_rate = 65;
        break;
    case 8:
        enemy_generate_rate = 30;
        melee_enemy_rate = 60;
        ranged_enemy_rate = 20;
        charge_enemy_rate = 0;
        explosive_enemy_rate = 20;
        elite_enemy_rate = 65;
        break;
    case 9:
        enemy_generate_rate = 50;
        melee_enemy_rate = 60;
        ranged_enemy_rate = 20;
        charge_enemy_rate = 0;
        explosive_enemy_rate = 20;
        elite_enemy_rate = 100;
        break;
    case 10:
        endgame_win();
        break;
    default:
        break;
    }
}

void StartGame::updateCountdown()//倒计时
{
    countdown_count++;
    if (countdown_count < 100) return;
    countdown_count = 0;
    countdown_time = countdown_time.addSecs(-1);
    countdown_text->setPlainText(countdown_time.toString("mm:ss"));
}

void StartGame::levelCheck()
{
    int exp = m_player->getExp();
    setExpBar();
    if (exp < 6 + 4 * level) return;
    m_player->setExp(0);
    if (level > 17) return;
    level++;
    gamePause();
    levelUp();
}

QList<int> StartGame::upPowerGenerator()//技能生成
{
    QList<int> list;
    const int MAX_COUNT = 100;
    int count = 0;
    for (int i = 0; i < 3; ++i) {
        int type_index = QRandomGenerator::global()->bounded(1, 21);
        count++;
        if (count > MAX_COUNT) {
            list.append(0);
            continue;
        }
        bool flag = false;
        for (int p : list) {
            if (type_index == p) {
                flag = true;
                break;
            }
        }
        if (flag) {
            i--;
            continue;
        }
        switch (type_index) {
        case 1:
            if (UpPower::getU_vitality() == false) {
                list.append(type_index);
            } else {
                i--;
                continue;
            }
            break;
        case 2:
            if (UpPower::getU_vitality() == true && UpPower::getU_giant() == false) {
                list.append(type_index);
            } else {
                i--;
                continue;
            }
            break;
        case 3:
            if (UpPower::getU_vitality() == true && UpPower::getU_dodge() == false) {
                list.append(type_index);
            } else {
                i--;
                continue;
            }
            break;
        case 4:
            if ((UpPower::getU_giant() == true || UpPower::getU_dodge() == true) && UpPower::getU_regeneration() == false) {
                list.append(type_index);
            } else {
                i--;
                continue;
            }
            break;
        case 5:
            if (UpPower::getU_hollowpoint() == false) {
                list.append(type_index);
            } else {
                i--;
                continue;
            }
            break;
        case 6:
            if (UpPower::getU_hollowpoint() == true && UpPower::getU_doubleshot() == false) {
                list.append(type_index);
            } else {
                i--;
                continue;
            }
            break;
        case 7:
            if (UpPower::getU_hollowpoint() == true && UpPower::getU_heavybarrel() == false) {
                list.append(type_index);
            } else {
                i--;
                continue;
            }
            break;
        case 8:
            if ((UpPower::getU_doubleshot() == true || UpPower::getU_heavybarrel() == true) && UpPower::getU_reaper() == false) {
                list.append(type_index);
            } else {
                i--;
                continue;
            }
            break;
        case 9:
            if (UpPower::getU_fasthand() == false) {
                list.append(type_index);
            } else {
                i--;
                continue;
            }
            break;
        case 10:
            if (UpPower::getU_fasthand() == true && UpPower::getU_overload() == false) {
                list.append(type_index);
            } else {
                i--;
                continue;
            }
            break;
        case 11:
            if (UpPower::getU_fasthand() == true && UpPower::getU_lightbullet() == false) {
                list.append(type_index);
            } else {
                i--;
                continue;
            }
            break;
        case 12:
            if ((UpPower::getU_overload() == true || UpPower::getU_lightbullet() == true) && UpPower::getU_barrage() == false) {
                list.append(type_index);
            } else {
                i--;
                continue;
            }
            break;
        case 13:
            if (UpPower::getU_streamline() == false) {
                list.append(type_index);
            } else {
                i--;
                continue;
            }
            break;
        case 14:
            if (UpPower::getU_streamline() == true && UpPower::getU_sniper() == false) {
                list.append(type_index);
            } else {
                i--;
                continue;
            }
            break;
        case 15:
            if (UpPower::getU_streamline() == true && UpPower::getU_takeaim() == false) {
                list.append(type_index);
            } else {
                i--;
                continue;
            }
            break;
        case 16:
            if ((UpPower::getU_sniper() == true || UpPower::getU_takeaim() == true) && UpPower::getU_pierecinground() == false) {
                list.append(type_index);
            } else {
                i--;
                continue;
            }
            break;
        case 17:
            if (UpPower::getU_haste() == false) {
                list.append(type_index);
            } else {
                i--;
                continue;
            }
            break;
        case 18:
            if (UpPower::getU_haste() == true && UpPower::getU_overspeed() == false) {
                list.append(type_index);
            } else {
                i--;
                continue;
            }
            break;
        case 19:
            if (UpPower::getU_haste() == true && UpPower::getU_runngun() == false) {
                list.append(type_index);
            } else {
                i--;
                continue;
            }
            break;
        case 20:
            if ((UpPower::getU_overspeed() == true || UpPower::getU_runngun() == true) && UpPower::getU_inthewind() == false) {
                list.append(type_index);
            } else {
                i--;
                continue;
            }
            break;
        default:
            break;
        }
    }
    return list;
}

void StartGame::levelUp()
{
    QList<int> u_list = upPowerGenerator();
    QList<UpPower*> mod_list;
    for (int i = 0; i < 3; ++i) {
        UpPower *mod = new UpPower(i, u_list[i], m_player, m_firearm, m_scene, this);
        mod_list.append(mod);
    }
    for (auto p : mod_list) {
        for (int i = 0; i < 3; ++i) {
            connect(p, &UpPower::upPowerSelected, mod_list[i], &UpPower::deleteLater);
        }
        connect(p, &UpPower::upPowerSelected, this, &StartGame::gameContinue);
        connect(p, &UpPower::upPowerSelected, this, &StartGame::setHPBar);
    }
}

void StartGame::setExpBar()
{
    int exp = m_player->getExp();
    float ratio = exp / (float)(6 + 4 * level);
    exp_bar->setRect(0, 0, 400 * ratio, 16);
    level_text->setPlainText(QString("Level %1").arg(level));
}

void StartGame::dataIncrement()
{
    data_count++;
    if (data_count < (100 * (1 - 0.15 * data_collector))) return;
    data_count = 0;
    data_money++;
    QString str("经济: ");
    str += QString::number(data_money);
    data_text->setPlainText(str);
}

void StartGame::loadArchive(int sign)
{
    bool is_saved = archive[sign]->value("is_saved", false).toBool();
    if (!is_saved) return;
    // 角色属性
    archive[sign]->beginGroup("player");
    int max_hp = archive[sign]->value("max_hp").toInt();
    int HP = archive[sign]->value("hp").toInt();
    qreal dodge = archive[sign]->value("dodge").toInt();
    qreal speed_boost = archive[sign]->value("speed_boost").toInt();
    QPointF player_pos = archive[sign]->value("player_pos").toPointF();
    qreal player_scale = archive[sign]->value("player_scale").toReal();
    bool inthewind = archive[sign]->value("inthewind").toInt();
    int exp = archive[sign]->value("exp").toInt();
    archive[sign]->endGroup();
    m_player->setMaxHP(max_hp);
    m_player->setHP(HP);
    m_player->setDodge(dodge);
    m_player->setSpeed_boost(speed_boost);
    m_player->setScale(player_scale);
    m_player->setU_inthewind(inthewind);
    m_player->setExp(exp);
    QPointF delta_pos = player_pos - m_player->pos();
    m_background->moveBy(-delta_pos.x(), -delta_pos.y());
    m_player->setPos(player_pos);
    setHPBar();

    // 武器属性
    archive[sign]->beginGroup("firearm");
    firearm_type = archive[sign]->value("firearm_type").toString();
    qreal damage_boost = archive[sign]->value("damage_boost").toReal();
    qreal firerate_boost = archive[sign]->value("firerate_boost").toReal();
    qreal bullet_speed_boost = archive[sign]->value("bullet_speed_boost").toReal();
    qreal spread = archive[sign]->value("spread").toReal();
    int round_boost = archive[sign]->value("round_boost").toInt();
    int barrage = archive[sign]->value("barrage").toInt();
    int penetration = archive[sign]->value("penetration").toInt();
    archive[sign]->endGroup();
    m_scene->removeItem(m_firearm);
    delete m_firearm;
    if (firearm_type == "smGun") m_firearm = new FirearmSmgun(m_player, m_scene, this);
    else if (firearm_type == "traceGun") m_firearm = new FirearmTrace(m_player, m_scene, this);
    else if (firearm_type == "shotGun") m_firearm = new FirearmShotgun(m_player, m_scene, this);
    else if (firearm_type == "sniperGun") m_firearm = new FirearmSniper(m_player, m_scene, this);
    m_firearm->setParentItem(m_background);
    m_firearm->setDamageBoost(damage_boost);
    m_firearm->setFireRateBoost(firerate_boost);
    m_firearm->setSpeedBoost(bullet_speed_boost);
    m_firearm->setSpread(spread);
    m_firearm->setRoundBoost(round_boost);
    m_firearm->setBarrage(barrage);
    m_firearm->setPenetration(penetration);
    m_scene->addItem(m_firearm);
    // 武器移动，加载贴图，开火
    connect(main_timer, &QTimer::timeout, m_firearm, &FirearmBase::updatePos);
    connect(main_timer, &QTimer::timeout, m_firearm, &FirearmBase::load);
    connect(main_timer, &QTimer::timeout, m_firearm, &FirearmBase::fire);

    // 局内升级
    archive[sign]->beginGroup("uppower");
    bool u_vitality = archive[sign]->value("u_vitality").toBool();
    bool u_giant = archive[sign]->value("u_giant").toBool();
    bool u_dodge = archive[sign]->value("u_dodge").toBool();
    bool u_regeneration = archive[sign]->value("u_regeneration").toBool();

    bool u_hollowpoint = archive[sign]->value("u_hollowpoint").toBool();
    bool u_doubleshot = archive[sign]->value("u_doubleshot").toBool();
    bool u_heavybarrel = archive[sign]->value("u_heavybarrel").toBool();
    bool u_reaper = archive[sign]->value("u_reaper").toBool();

    bool u_fasthand = archive[sign]->value("u_fasthand").toBool();
    bool u_overload = archive[sign]->value("u_overload").toBool();
    bool u_lightbullet = archive[sign]->value("u_lightbullet").toBool();
    bool u_barrage = archive[sign]->value("u_barrage").toBool();

    bool u_streamline = archive[sign]->value("u_streamline").toBool();
    bool u_sniper = archive[sign]->value("u_sniper").toBool();
    bool u_takeaim = archive[sign]->value("u_takeaim").toBool();
    bool u_pierecinground = archive[sign]->value("u_pierecinground").toBool();

    bool u_haste = archive[sign]->value("u_haste").toBool();
    bool u_overspeed = archive[sign]->value("u_overspeed").toBool();
    bool u_runngun = archive[sign]->value("u_runngun").toBool();
    bool u_inthewind = archive[sign]->value("u_inthewind").toBool();

    archive[sign]->endGroup();

    UpPower::setU_vitality(u_vitality);
    UpPower::setU_giant(u_giant);
    UpPower::setU_dodge(u_dodge);
    UpPower::setU_regeneration(u_regeneration);
    UpPower::setU_hollowpoint(u_hollowpoint);
    UpPower::setU_doubleshot(u_doubleshot);
    UpPower::setU_heavybarrel(u_heavybarrel);
    UpPower::setU_reaper(u_reaper);
    UpPower::setU_fasthand(u_fasthand);
    UpPower::setU_overload(u_overload);
    UpPower::setU_lightbullet(u_lightbullet);
    UpPower::setU_barrage(u_barrage);
    UpPower::setU_streamline(u_streamline);
    UpPower::setU_sniper(u_sniper);
    UpPower::setU_takeaim(u_takeaim);
    UpPower::setU_pierecinground(u_pierecinground);
    UpPower::setU_haste(u_haste);
    UpPower::setU_overspeed(u_overspeed);
    UpPower::setU_runngun(u_runngun);
    UpPower::setU_inthewind(u_inthewind);

    // 载入游戏阶段
    archive[sign]->beginGroup("gameStage");
    level = archive[sign]->value("level").toInt();
    phase = archive[sign]->value("phase").toInt();
    phase_count = archive[sign]->value("phase_count").toInt();
    countdown_time = archive[sign]->value("countdown_time").toTime();
    countdown_count = archive[sign]->value("countdown_count").toInt();
    archive[sign]->endGroup();
    switch (phase) {
    case 1:
        enemy_generate_rate = 10;
        melee_enemy_rate = 90;
        ranged_enemy_rate = 0;
        charge_enemy_rate = 0;
        explosive_enemy_rate = 10;
        elite_enemy_rate = 0;
        break;
    case 2:
        enemy_generate_rate = 10;
        melee_enemy_rate = 70;
        ranged_enemy_rate = 10;
        charge_enemy_rate = 0;
        explosive_enemy_rate = 20;
        elite_enemy_rate = 0;
        break;
    case 3:
        enemy_generate_rate = 12.5;
        melee_enemy_rate = 70;
        ranged_enemy_rate = 10;
        charge_enemy_rate = 0;
        explosive_enemy_rate = 20;
        elite_enemy_rate = 0;
        break;
    case 4:
        enemy_generate_rate = 15;
        melee_enemy_rate = 70;
        ranged_enemy_rate = 10;
        charge_enemy_rate = 0;
        explosive_enemy_rate = 20;
        elite_enemy_rate = 0;
        break;
    case 5:
        enemy_generate_rate = 15;
        melee_enemy_rate = 60;
        ranged_enemy_rate = 20;
        charge_enemy_rate = 0;
        explosive_enemy_rate = 20;
        elite_enemy_rate = 30;
        break;
    case 6:
        enemy_generate_rate = 20;
        melee_enemy_rate = 60;
        ranged_enemy_rate = 20;
        charge_enemy_rate = 0;
        explosive_enemy_rate = 20;
        elite_enemy_rate = 30;
        break;
    case 7:
        enemy_generate_rate = 20;
        melee_enemy_rate = 60;
        ranged_enemy_rate = 20;
        charge_enemy_rate = 0;
        explosive_enemy_rate = 20;
        elite_enemy_rate = 65;
        break;
    case 8:
        enemy_generate_rate = 30;
        melee_enemy_rate = 60;
        ranged_enemy_rate = 20;
        charge_enemy_rate = 0;
        explosive_enemy_rate = 20;
        elite_enemy_rate = 65;
        break;
    case 9:
        enemy_generate_rate = 50;
        melee_enemy_rate = 60;
        ranged_enemy_rate = 20;
        charge_enemy_rate = 0;
        explosive_enemy_rate = 20;
        elite_enemy_rate = 100;
        break;
    case 10:
        endgame_win();
        break;
    default:
        break;
    }
}

void StartGame::saveArchive(int sign)
{
        // 是否存在存档
        bool is_saved = true;
        archive[sign]->setValue("is_saved", is_saved);
        // 角色属性
        int max_hp = m_player->getMaxHP();
        int health = m_player->getHP();
        qreal dodge = m_player->getDodge();
        qreal speed_boost = m_player->getSpeed_boost();
        QPointF player_pos = m_player->pos();
        qreal player_scale = m_player->scale();
        bool inthewind = m_player->getU_inthewind();
        int exp = m_player->getExp();
        archive[sign]->beginGroup("player");
        archive[sign]->setValue("max_hp", max_hp);
        archive[sign]->setValue("health", health);
        archive[sign]->setValue("dodge", dodge);
        archive[sign]->setValue("speed_boost", speed_boost);
        archive[sign]->setValue("player_pos", player_pos);
        archive[sign]->setValue("player_scale", player_scale);
        archive[sign]->setValue("exp", exp);
        archive[sign]->setValue("inthewind", inthewind);
        archive[sign]->endGroup();
        // 武器属性
        qreal damage_boost = m_firearm->getDamageBoost();
        qreal firerate_boost = m_firearm->getFireRateBoost();
        qreal bullet_speed_boost = m_firearm->getSpeedBoost();
        qreal spread = m_firearm->getSpread();
        int round_boost = m_firearm->getRoundBoost();
        int barrage = m_firearm->getBarrage();
        int penetration = m_firearm->getPenetration();
        archive[sign]->beginGroup("firearm");
        archive[sign]->setValue("firearm_type", firearm_type);
        archive[sign]->setValue("damage_boost", damage_boost);
        archive[sign]->setValue("firerate_boost", firerate_boost);
        archive[sign]->setValue("bullet_speed_boost", bullet_speed_boost);
        archive[sign]->setValue("spread", spread);
        archive[sign]->setValue("round_boost", round_boost);
        archive[sign]->setValue("barrage", barrage);
        archive[sign]->setValue("penetration", penetration);
        archive[sign]->endGroup();
        // 局内升级
        bool u_vitality = UpPower::getU_vitality();
        bool u_giant = UpPower::getU_giant();
        bool u_dodge = UpPower::getU_dodge();
        bool u_regeneration = UpPower::getU_dodge();

        bool u_hollowpoint = UpPower::getU_hollowpoint();
        bool u_doubleshot = UpPower::getU_doubleshot();
        bool u_heavybarrel = UpPower::getU_heavybarrel();
        bool u_reaper = UpPower::getU_reaper();

        bool u_fasthand = UpPower::getU_fasthand();
        bool u_overload = UpPower::getU_overload();
        bool u_lightbullet = UpPower::getU_lightbullet();
        bool u_barrage = UpPower::getU_barrage();

        bool u_streamline = UpPower::getU_streamline();
        bool u_sniper = UpPower::getU_sniper();
        bool u_takeaim = UpPower::getU_takeaim();
        bool u_pierecinground = UpPower::getU_pierecinground();

        bool u_haste = UpPower::getU_haste();
        bool u_overspeed = UpPower::getU_overspeed();
        bool u_runngun = UpPower::getU_runngun();
        bool u_inthewind = UpPower::getU_inthewind();

        archive[sign]->beginGroup("upgrade");

        archive[sign]->setValue("u_vitality", u_vitality);
        archive[sign]->setValue("u_giant", u_giant);
        archive[sign]->setValue("u_dodge", u_dodge);
        archive[sign]->setValue("u_regeneration", u_regeneration);

        archive[sign]->setValue("u_hollowpoint", u_hollowpoint);
        archive[sign]->setValue("u_doubleshot", u_doubleshot);
        archive[sign]->setValue("u_heavybarrel", u_heavybarrel);
        archive[sign]->setValue("u_reaper", u_reaper);

        archive[sign]->setValue("u_fasthand", u_fasthand);
        archive[sign]->setValue("u_overload", u_overload);
        archive[sign]->setValue("u_lightbullet", u_lightbullet);
        archive[sign]->setValue("u_barrage", u_barrage);

        archive[sign]->setValue("u_streamline", u_streamline);
        archive[sign]->setValue("u_sniper", u_sniper);
        archive[sign]->setValue("u_takeaim", u_takeaim);
        archive[sign]->setValue("u_pierecinground", u_pierecinground);

        archive[sign]->setValue("u_haste", u_haste);
        archive[sign]->setValue("u_overspeed", u_overspeed);
        archive[sign]->setValue("u_runngun", u_runngun);
        archive[sign]->setValue("u_inthewind", u_inthewind);

        archive[sign]->endGroup();

        // 敌人存储
        QVariantList enemyList;
        QList<QGraphicsItem*> itemlist = m_scene->items();
        for (auto item : itemlist) {
            QVariantMap enemyMap;//类似于C/C++的union  insert会覆盖前面键值相同的元素
            EnemyBot *enemybot = dynamic_cast<EnemyBot*>(item);
            if (enemybot) {
                enemyMap.insert("type", "bot");
                enemyMap.insert("pos", enemybot->pos());
                continue;
            }
            EnemyRangedDrone *enemydrone = dynamic_cast<EnemyRangedDrone*>(item);
            if (enemydrone) {
                enemyMap.insert("type", "drone");
                enemyMap.insert("pos", enemydrone->pos());
                continue;
            }
            EnemyExploBall *enemyball = dynamic_cast<EnemyExploBall*>(item);
            if (enemyball) {
                enemyMap.insert("type", "ball");
                enemyMap.insert("pos", enemyball->pos());
                continue;
            }
            EnemyBotElite *enemybotelite = dynamic_cast<EnemyBotElite*>(item);
            if (enemybotelite) {
                enemyMap.insert("type", "bot_elite");
                enemyMap.insert("pos", enemybotelite->pos());
                continue;
            }
            EnemyRangedDroneElite *enemydroneelite = dynamic_cast<EnemyRangedDroneElite*>(item);
            if (enemydroneelite) {
                enemyMap.insert("type", "drone_elite");
                enemyMap.insert("pos", enemydroneelite->pos());
                continue;
            }
            enemyList.append(enemyMap);
        }
        archive[sign]->beginGroup("enemy");
        archive[sign]->setValue("enemyList", enemyList);
        archive[sign]->endGroup();

        // 游戏阶段
        archive[sign]->beginGroup("gameStage");
        archive[sign]->setValue("phase", phase);
        archive[sign]->setValue("phase_count", phase_count);
        archive[sign]->setValue("countdown_time", countdown_time);
        archive[sign]->setValue("countdown_count", countdown_count);
        archive[sign]->setValue("level", level);
        archive[sign]->endGroup();
}

void StartGame::showArchive()
{
    for (int i = 0; i < 3; ++i) {
        archive_mod[i] = new Archive(i, m_scene, this);
        connect(archive_mod[i], &Archive::saveArchive, this, [=](int index){
            saveArchive(index);
        });
    }
}

void StartGame::hideArchive()
{
    for (int i = 0; i < 3; ++i) {
        archive_mod[i]->disconnect();
        archive_mod[i]->hideAndDestory();
    }
}

void StartGame::endgame_lose()
{
    int respawn_udisk = settings->value("Respawn Udisk", 0).toInt();//复活
    if (respawn_udisk > 0) {
        m_player->setHP(m_player->getMaxHP());
        setHPBar();
        respawn_udisk--;
        settings->setValue("Respawn Udisk", respawn_udisk);
        sef_respawn->play();
        return;
    }
    // 读取样式表
    QFile file_sqr_pb(":/source/stystle/sqr_pb.qss");
    file_sqr_pb.open(QFile::ReadOnly);
    QString style_sqr_pb;
    if (file_sqr_pb.isOpen()) {
        style_sqr_pb = QLatin1String(file_sqr_pb.readAll());
        file_sqr_pb.close();
    }
    // 重置所有局内升级
    UpPower::resetAll();
    // 停止所有计时器
    main_timer->stop();
    // 停止背景音乐
    bgm_player->stop();
    // 删除血条
    for (auto *p : hp_list) {
        if (p) p->deleteLater();
    }
    // 保存
    settings->setValue("data", data_money);
    // 显示游戏结束界面
    end_scene = new QGraphicsScene(this);
    end_scene->setSceneRect(0, 0, 1280, 720);
    setScene(end_scene);
    end_scene->setFocus();
    // 背景
    end_scene->addPixmap(QPixmap(":/source/picture/stratMenu/Background.png"));
    // 文字
    QGraphicsTextItem *end_text = new QGraphicsTextItem("菜!");
    end_text->setFont(QFont("fusion pixel proportional", 72));
    end_text->setDefaultTextColor(Qt::red);
    end_text->setPos(600, 260);
    end_scene->addItem(end_text);
    // 返回按钮
    QPushButton *return_btn = new QPushButton("菜鸡点我回去!");
    end_scene->addWidget(return_btn);
    return_btn->move(500, 540);
    return_btn->setStyleSheet(style_sqr_pb);
    return_btn->resize(220, 110);
    connect(return_btn, &QPushButton::clicked, this, [=](){
        emit EndGame();
        deleteLater();
    });
}

void StartGame::endgame_win()
{
    // 读取样式表
    QFile file_sqr_pb(":/source/stystle/sqr_pb.qss");
    file_sqr_pb.open(QFile::ReadOnly);
    QString style_sqr_pb;
    if (file_sqr_pb.isOpen()) {
        style_sqr_pb = QLatin1String(file_sqr_pb.readAll());
        file_sqr_pb.close();
    }
    // 重置所有局内升级
    UpPower::resetAll();
    // 停止所有计时器
    main_timer->stop();
    // 停止背景音乐
    bgm_player->stop();
    // 删除血条
    for (auto *p : hp_list) {
        if (p) p->deleteLater();
    }
    // 保存
    settings->setValue("data", data_money);
    // 显示游戏结束界面
    end_scene = new QGraphicsScene(this);
    end_scene->setSceneRect(0, 0, 1280, 720);
    setScene(end_scene);
    // 背景
    end_scene->addPixmap(QPixmap(":/source/picture/stratMenu/Background.png"));
    // 文字
    QGraphicsTextItem *end_text = new QGraphicsTextItem("哟 可以啊你小子");
    end_text->setFont(QFont("fusion pixel proportional", 72));
    end_text->setDefaultTextColor(Qt::green);
    end_text->setPos(600, 260);
    end_scene->addItem(end_text);
    // 返回按钮
    QPushButton *return_btn = new QPushButton("点本按钮回去");
    end_scene->addWidget(return_btn);
    return_btn->move(520, 540);
    return_btn->setStyleSheet(style_sqr_pb);
    return_btn->resize(220, 110);
    connect(return_btn, &QPushButton::clicked, this, [=](){
        emit EndGame();
        deleteLater();
    });
}
