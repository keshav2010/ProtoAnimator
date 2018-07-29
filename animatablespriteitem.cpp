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
    setFlag(GraphicsItemFlag::ItemIsMovable, true);
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
    setFlag(GraphicsItemFlag::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable);
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
    painter->drawImage(this->pos(), this->pixmap().toImage());
    painter->setPen(QColor(200,100,50));
    painter->drawRect(this->pos().x(), this->pos().y(), this->pixmap().rect().width(), this->pixmap().rect().height());
}

void AnimatableSpriteItem::setSpritePixmap(const QPixmap &sprite)
{
    spritePixmap = new QPixmap(sprite);
    this->setPixmap(*spritePixmap);

    //update Sprite Data
    spriteData.setSpriteScale(QPointF(pixmap().rect().width(), pixmap().rect().height()));
    spriteData.setSpritePosition(QPointF(this->x(), this->y()));
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

void AnimatableSpriteItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug()<<" Item clicked : "<<this->mName;
}
