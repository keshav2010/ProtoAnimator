#ifndef ANIMATABLEIMAGEITEM_H
#define ANIMATABLEIMAGEITEM_H

#include<QGraphicsItem>
#include<QGraphicsPixmapItem>
#include<QRectF>
#include<QPixmap>
#include<QImage>
#include "spritedata.h"

class AnimatableSpriteItem : public QGraphicsPixmapItem
{

public:
    AnimatableSpriteItem(QGraphicsItem *parent = 0);
    ~AnimatableSpriteItem();
    QRectF boundingRect() const override; //returns estimate of area painted by this item
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void setSpritePixmap(const QPixmap &sprite);
    QPainter *getSpritePainter();

    SpriteData getSpriteData();
    void setSpriteData(SpriteData &data);

    QPixmap *spritePixmap;
protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent * event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent * event) override;

private:
    QPainter *spritePainter;
    bool followMouse;
    SpriteData spriteData;
};

#endif // ANIMATABLEIMAGEITEM_H
