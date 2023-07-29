
#ifndef FIREARMSELECT_H
#define FIREARMSELECT_H


#include <QObject>
#include "GraphicsSelectButton.h"
#include <QFontDatabase>
#include <QGraphicsTextItem>
#include <QGraphicsScene>

class FirearmSelect : public QObject
{
    Q_OBJECT
public:
    explicit FirearmSelect(int s,int index,QGraphicsScene *sence,QObject *parent = nullptr);

    void resetButton();
signals:
    void firearmSelected(QString firearm);
private:
    void hoverEnter();
    void hoverLeave();
    void mouseClicked();
    void setFirearm(int index);

    int sign;
    int f_index;
    QString f_firearm;
    QGraphicsScene * f_scene;
    GraphicsSelectButton *f_icon;
    QGraphicsTextItem *f_explain;
};

#endif // FIREARMSELECT_H
