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
    virtual ~AnimatableSpriteItem();
    QRectF boundingRect() const; //returns estimate of area painted by this item
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setSpritePixmap(const QPixmap &sprite);
    QPainter *getSpritePainter();

    SpriteData getSpriteData();
    void setSpriteData(SpriteData &data);
    QString getName();
    void setName(const QString &name);
    QPixmap *spritePixmap;

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent * event) override;

private:
    QPainter *spritePainter;
    bool followMouse;
    SpriteData spriteData;
    QString mName;
};

#endif // ANIMATABLEIMAGEITEM_H
