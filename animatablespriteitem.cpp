#include "animatablespriteitem.h"
#include<QPainter>
#include <QGraphicsSceneMouseEvent>
#include"frameseditor.h"

AnimatableSpriteItem::AnimatableSpriteItem(QGraphicsItem *parent):
    QGraphicsPixmapItem(parent),
    followMouse(false)
{
    qDebug()<<"(AnimatableSpriteItem.cpp) : constructor called";
    this->setX(0);
    this->setY(0);
    this->spriteData.setSpritePosition(QPointF(0,0));
    setFlag(GraphicsItemFlag::ItemIsMovable);
}

AnimatableSpriteItem::AnimatableSpriteItem(AnimatableSpriteItem *src, QGraphicsItem *parent):
    QGraphicsPixmapItem(parent)
{
    qDebug()<<"(AnimatableSpriteItem.cpp) : copy constructor called";

    //user defined properties (in order as they appear in declaration)
    this->spritePixmap = new QPixmap(*(src->spritePixmap));
    this->followMouse = src->followMouse;
    this->spriteData = src->spriteData;
    this->mName = QString(src->mName);
    this->setX(src->x());
    this->setY(src->y());
    this->spriteData.setSpritePosition(QPointF(this->x(), this->y()));
    setFlag(GraphicsItemFlag::ItemIsMovable);

    //pre-defined properties
    this->setName(src->getName());
    this->setSpritePixmap(*spritePixmap);

}

AnimatableSpriteItem::~AnimatableSpriteItem()
{
    qDebug()<<"(~AnimatableSpiteItem.cpp) > removed "+this->getName()<<" from memory";
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
    qDebug()<<"(AnimatableSpriteItem.cpp) Mouse Moving";
    //if(this->followMouse)
        //setPos(event->buttonDownScenePos(Qt::MouseButton::LeftButton));
}

void AnimatableSpriteItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent * event)
{
    qDebug()<<"animatableSpriteItem.cpp : Double Clicked on Sprite Item";
}

