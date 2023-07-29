#include "GraphicsButton.h"

GraphicsButton::GraphicsButton(QString path, QPointF pos, QObject *parent)
    : QObject{parent}, ic_path(path)
{
    setAcceptHoverEvents(true);
    setAcceptedMouseButtons(Qt::LeftButton);
    QString pt = ic_path + "_out.png";
    setPixmap((QPixmap(pt)));
    setPos(pos);
}

void GraphicsButton::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    QString path = ic_path + "_into.png";
    setPixmap((QPixmap(path)));
    is_hovered = true;
    emit hoverEnter();
}

void GraphicsButton::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    QString path = ic_path + "_out.png";
    setPixmap((QPixmap(path)));
    is_hovered = false;
    emit hoverLeave();
}

void GraphicsButton::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    is_pressed = true;
}

void GraphicsButton::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (is_pressed && is_hovered) emit mouseClicked();
    is_pressed = false;
}
