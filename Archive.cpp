
#include "Archive.h"

Archive::Archive(int index, QGraphicsScene * scence,QObject *parent)
    : QObject{parent},a_sign(index),a_scence(scence)
{
    QFontDatabase::addApplicationFont(":/source/font/fusion-pixel-proportional.ttf");
    a_Btn = new GraphicsButton(":/source/picture/stratMenu/blank",QPointF(640-16,180 * a_sign + 180));
    a_Btn->setTransformOriginPoint(a_Btn->boundingRect().center());//设置变换原点 - 外接矩形的中心
    a_Btn->setScale(4);//set缩放
    a_scence->addItem(a_Btn);

    QString filename = QString("./archive%1.ini").arg(a_sign);//创建.ini文件 由arg()管理存档
    archive = new QSettings(filename,QSettings::IniFormat,this);
    bool is_saved = archive->value("is_saved",false).toBool();//创建第一个数据

    a_explain = new QGraphicsTextItem;
    a_explain->setDefaultTextColor(Qt::white);//设置解释颜色
    a_explain->setFont(QFont("fusion pixel proportional", 16));//字体
    if(is_saved){
        a_explain->setPlainText("存档");
    } else
        a_explain->setPlainText("空存档");
    a_explain->setPos(640 - a_explain->boundingRect().width() / 2,180 * a_sign + 150 +a_explain->boundingRect().height() / 2);
    a_scence->addItem(a_explain);

    connect(a_Btn,&GraphicsButton::mouseClicked,this,&Archive::mouseClicked);//连接click事件

}


void Archive::hideAndDestory()
{
    a_scence->removeItem(a_Btn);
    a_scence->removeItem(a_explain);
    delete a_explain;
    deleteLater();//延迟关闭文件 维持代码健壮性
}

void Archive::mouseClicked()
{
    emit saveArchive(a_sign);//发送信号
    emit loadArchive(a_sign);
    bool is_saved = archive->value("is_saved",false).toBool();
    if(is_saved){
        a_explain->setPlainText("SAVE");
    } else
        a_explain->setPlainText("EMPTY");
    a_explain->setPos(640 - a_explain->boundingRect().width() / 2,180 * a_sign + 150 +a_explain->boundingRect().height() / 2);
    a_scence->addItem(a_explain);
}
