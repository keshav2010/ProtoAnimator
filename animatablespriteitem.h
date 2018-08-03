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
    AnimatableSpriteItem(AnimatableSpriteItem* src, QGraphicsItem *parent=0);
    ~AnimatableSpriteItem();
    QRectF boundingRect() const; //returns estimate of area painted by this item
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setSpritePixmap(const QPixmap &sprite);

    SpriteData getSpriteData();
    void setSpriteData(SpriteData &data);
    QString getName();
    void setName(const QString &name);
    QPixmap *spritePixmap;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    SpriteData spriteData;
    QString mName;
};

#endif // ANIMATABLEIMAGEITEM_H
