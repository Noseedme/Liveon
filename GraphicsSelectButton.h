
#ifndef GRAPHICSSELECTBUTTON_H
#define GRAPHICSSELECTBUTTON_H


#include <QObject>
#include "GraphicsButton.h"

class GraphicsSelectButton : public GraphicsButton
{
    Q_OBJECT
public:
    explicit GraphicsSelectButton(QString path,QPointF pos,QObject *parent = nullptr);
    void reset();
signals:
    void select();
protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent * event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent * event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent * event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent * event) override;

    bool is_selected = false;
};

#endif // GRAPHICSSELECTBUTTON_H
