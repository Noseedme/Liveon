#include "FirearmSelect.h"

FirearmSelect::FirearmSelect(int s, int index, QGraphicsScene *scene, QObject *parent)
    : QObject{parent}, sign(s), f_index(index), f_scene(scene)
{
    f_explain = new QGraphicsTextItem();
    f_explain->setDefaultTextColor(Qt::white);
    f_explain->setFont(QFont("fusion pixel proportional", 16));
    setFirearm(f_index);
    f_scene->addItem(f_icon);
    connect(f_icon, &GraphicsButton::hoverEnter, this, &FirearmSelect::hoverEnter);
    connect(f_icon, &GraphicsButton::hoverLeave, this, &FirearmSelect::hoverLeave);
    connect(f_icon, &GraphicsButton::mouseClicked, this, &FirearmSelect::mouseClicked);
}

void FirearmSelect::resetButton()
{
    f_icon->reset();
}

void FirearmSelect::hoverEnter()
{
    f_scene->addItem(f_explain);
}

void FirearmSelect::hoverLeave()
{
    f_scene->removeItem(f_explain);
}

void FirearmSelect::mouseClicked()
{
    emit firearmSelected(f_firearm);
}

void FirearmSelect::setFirearm(int index)
{
    switch (index) {
    case 1:
        f_icon = new GraphicsSelectButton(":/source/picture/firearms/selectArm/smGun",QPointF(100 + 300 * sign,200));
        f_firearm = "smGun";
        f_explain->setPlainText("冲锋枪: 这个游戏不可能有比我更快的枪了 选我!!选我!! 享受极致快感...!");
        break;
    case 2:
        f_icon = new GraphicsSelectButton(":/source/picture/firearms/selectArm/shotgun",QPointF(100 + 300 * sign,200));
        f_firearm = "shotGun";
        f_explain->setPlainText("霰弹枪: 真男人的不二选择 你是真男人吗? (咆哮)那你还不快选我!!!");
        break;
    case 3:
        f_icon = new GraphicsSelectButton(":/source/picture/firearms/selectArm/sniperGun",QPointF(100 + 300 * sign,200));
        f_firearm = "sniperGun";
        f_explain->setPlainText("狙击步枪: 千里之外取上将首级 选我 ");
        break;
    case 4:
        f_icon = new GraphicsSelectButton(":/source/picture/firearms/selectArm/traceGun",QPointF(100 + 300 * sign,200));
        f_firearm = "traceGun";
        f_explain->setPlainText("追踪手枪: 人铁驭要死的时候才能用一下的枪在这里想怎么折腾人家就这么折腾人家~ 来玩啊~ 哥哥");
        break;
    default:
        break;
    }
    f_icon->setScale(4);
    f_explain->setPos(640 - f_explain->boundingRect().width() / 2, 360);
}
