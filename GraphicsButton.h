
#ifndef GRAPHICSBUTTON_H
#define GRAPHICSBUTTON_H


#include <QObject>
#include <QGraphicsPixmapItem>

class GraphicsButton : public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
     GraphicsButton(QString path,QPointF pos,QObject *parent = nullptr);

signals:
    void hoverEnter();
    void hoverLeave();
    void mouseClicked();
protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent * event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent * event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent * event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent * event) override;

    QString ic_path;
    bool is_hovered = false;//在规定位置点击才会发送点击信号
    bool is_pressed = false;
};

#endif // GRAPHICSBUTTON_H
