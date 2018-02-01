#ifndef ANIMATABLEIMAGEITEM_H
#define ANIMATABLEIMAGEITEM_H

#include<QGraphicsItem>
#include<QGraphicsPixmapItem>
#include<QRectF>
#include<QPixmap>
#include<QImage>
#include "animatable.h"

class AnimatableSpriteItem : public QGraphicsPixmapItem
{
signals:

public:
    AnimatableSpriteItem(QGraphicsItem *parent = 0);
    ~AnimatableSpriteItem();
    QRectF boundingRect() const override; //returns estimate of area painted by this item
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void setSpritePixmap(const QPixmap &sprite);

    QPixmap *spritePixmap;
protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent * event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent * event) override;

public slots:

private:
    bool followMouse;
};

#endif // ANIMATABLEIMAGEITEM_H
