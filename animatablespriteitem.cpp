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
    setFlag(QGraphicsItem::ItemIsSelectable);
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
    this->setTransform(src->transform());
    this->setPos(src->pos());
    this->setScale(src->scale());
    this->setRotation(src->rotation());
    setFlag(GraphicsItemFlag::ItemIsMovable);
    setFlag(GraphicsItemFlag::ItemIsSelectable);
    //pre-defined properties
    this->setName(src->getName());
    this->setSpritePixmap(*spritePixmap);

}

AnimatableSpriteItem::~AnimatableSpriteItem()
{
    qDebug()<<"(~AnimatableSpiteItem.cpp) > removed "+this->getName()<<" from memory";
    if(spritePixmap != nullptr){
        delete spritePixmap;
        spritePixmap = nullptr;
    }
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
    qDebug()<<"(AnimatableSpriteItem.cpp) > paint() :: drawing picture ";
    //painter->drawImage(spriteData.getSpritePosition(), spritePixmap->toImage());
    painter->drawImage(this->x(), this->y(), this->pixmap().toImage());
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
}
