#include "animatablespriteitem.h"
#include<QPainter>
#include <QGraphicsSceneMouseEvent>
#include"frameseditor.h"

AnimatableSpriteItem::AnimatableSpriteItem(QGraphicsItem *parent):
    QGraphicsPixmapItem(parent),
    followMouse(false)
{
    this->setX(0);
    this->setY(0);
}

AnimatableSpriteItem::~AnimatableSpriteItem()
{
    delete spritePixmap;
}

QRectF AnimatableSpriteItem::boundingRect() const
{
    //return spritePixmap->rect();
    return pixmap().rect();
}

void AnimatableSpriteItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawImage(this->x(), this->y(), spritePixmap->toImage());
}

void AnimatableSpriteItem::setSpritePixmap(const QPixmap &sprite)
{
    spritePixmap = new QPixmap(sprite);
    this->setPixmap(*spritePixmap);
}

void AnimatableSpriteItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(this->followMouse)
        setPos(event->buttonDownScenePos(Qt::MouseButton::LeftButton));
}

void AnimatableSpriteItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent * event)
{
    /*
    QRectF imageRect = this->boundingRect();
    const QPointF mouseClickPos = event->buttonDownScenePos(Qt::MouseButton::LeftButton);
    if(imageRect.contains( mouseClickPos )){
        followMouse=true;
    }
    */
}
