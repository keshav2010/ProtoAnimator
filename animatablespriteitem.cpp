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
    this->spriteData.setSpritePosition(QPointF(0,0));
    setFlag(ItemIsMovable);
}

AnimatableSpriteItem::~AnimatableSpriteItem()
{
    qDebug()<<"spriteItem : removed "+this->getName()<<" from memory";
    delete spritePixmap;
}

//override method
QRectF AnimatableSpriteItem::boundingRect() const
{
    //qDebug()<<"(AnimatableSpriteItem.cpp) : "<<spritePixmap->rect().width()<<" ** and ** "<<spritePixmap->rect().height();
    return this->spritePixmap->rect();
}

//override
void AnimatableSpriteItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    this->spritePainter = painter;
    qDebug()<<"AnimatableSpriteItem > paint :: drawing picture ";
    painter->drawImage(spriteData.getSpritePosition(), spritePixmap->toImage());
}

void AnimatableSpriteItem::setSpritePixmap(const QPixmap &sprite)
{
    spritePixmap = new QPixmap(sprite);
    this->setPixmap(*spritePixmap);

    //update Sprite Data
    spriteData.setSpriteScale(QPointF(pixmap().rect().width(), pixmap().rect().height()));
    spriteData.setSpritePosition(QPointF(this->x(), this->y()));
}

QPainter *AnimatableSpriteItem::getSpritePainter()
{
    return this->spritePainter;
}

SpriteData AnimatableSpriteItem::getSpriteData()
{
    return spriteData;
}

void AnimatableSpriteItem::setSpriteData(SpriteData &data)
{
    spriteData = data;
}

QString AnimatableSpriteItem::getName()
{
    return mName;
}

void AnimatableSpriteItem::setName(const QString &name)
{
    mName = name;
}

void AnimatableSpriteItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(this->followMouse)
        setPos(event->buttonDownScenePos(Qt::MouseButton::LeftButton));
}

void AnimatableSpriteItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent * event)
{
    qDebug()<<"animatableSpriteItem.cpp : Double Clicked on Sprite Item";
    /*
    qDebug()<<"Double Clicked";
    QRectF imageRect = boundingRect();
    const QPointF mouseClickPos = event->buttonDownScenePos(Qt::MouseButton::LeftButton);
    if(imageRect.contains( mouseClickPos )){
        qDebug()<<"Mouse inside image ";
        followMouse=true;
    }
    */
}

