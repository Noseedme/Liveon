
#include "GraphicsSelectButton.h"

GraphicsSelectButton::GraphicsSelectButton(QString path,QPointF pos,QObject *parent)
    : GraphicsButton{path,pos,parent}
{

}

void GraphicsSelectButton::reset()
{
    is_selected = false;
    QString path = ic_path + "_out.png";
    setPixmap((QPixmap(path)));
}

void GraphicsSelectButton::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    emit hoverEnter();
    if(is_selected) return;
    QString path = ic_path + "_into.png";
    setPixmap((QPixmap(path)));
    is_hovered = true;

}

void GraphicsSelectButton::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    emit hoverLeave();
    if(is_selected) return;
    QString path = ic_path + "_out.png";
    setPixmap((QPixmap(path)));
    is_hovered = false;

}

void GraphicsSelectButton::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    is_pressed = true;
}

void GraphicsSelectButton::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(is_hovered && is_pressed) {
        emit mouseClicked();
        QString path = ic_path + "_selected.png";
        setPixmap((QPixmap(path)));
    }
    is_selected = true;
    is_pressed = false;
}

