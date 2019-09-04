#include "spritedata.h"
#include<QDebug>
SpriteData::SpriteData()
{
    qDebug()<<"(SpriteData.cpp) constructor";
    spriteX=spriteY=100;
    spriteW=spriteH=0;
    rotX=0;
    rotY=0;
}

SpriteData::SpriteData(const SpriteData &data)
{
    this->setSpritePosition(data.getSpritePosition());
    this->setSpriteScale(data.getSpriteScale());
    this->setSpriteRotation(data.getSpriteRotation());
}

QPointF SpriteData::getSpritePosition() const
{
    return QPointF(this->spriteX, this->spriteY);
}

QPointF SpriteData::getSpriteScale() const
{
    return QPointF(this->spriteW, this->spriteH);
}
QPointF SpriteData::getSpriteRotation() const
{
    return QPointF(this->rotX, this->rotY);
}

SpriteData& SpriteData::setSpriteRotation(const QPointF &point)
{
    this->rotX = point.x();
    this->rotY = point.y();
    return *this;
}
SpriteData& SpriteData::setSpritePosition(const QPointF &point)
{
    this->spriteX = point.x();
    this->spriteY = point.y();
    return *this;
}
SpriteData& SpriteData::setSpriteScale(const QPointF &point){
    this->spriteW = point.x();
    this->spriteH = point.y();
    return *this;
}
SpriteData &SpriteData::operator=(const SpriteData &t)
{
    this->setSpritePosition(t.getSpritePosition());
    this->setSpriteScale(t.getSpriteScale());
    this->setSpriteRotation(t.getSpriteRotation());

    return *this;
}
