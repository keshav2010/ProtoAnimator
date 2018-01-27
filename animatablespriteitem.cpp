#include "animatablespriteitem.h"
#include<QPainter>

AnimatableSpriteItem::AnimatableSpriteItem(QGraphicsItem *parent):
    QGraphicsPixmapItem(parent),
    spritePixmap(new QPixmap),
    followMouse(false)
{
}

AnimatableSpriteItem::~AnimatableSpriteItem()
{
    delete spritePixmap;
}

QRectF AnimatableSpriteItem::boundingRect() const
{
    return spritePixmap->rect();
}

void AnimatableSpriteItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawRoundedRect(-10,-10,20,20,5,5);
}
