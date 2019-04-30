#include "spritedata.h"
#include<QDebug>
SpriteData::SpriteData()
{
    qDebug()<<"(SpriteData.cpp) constructor";
    spriteX=spriteY=100;
    spriteW=spriteH=0;
}

SpriteData::SpriteData(const SpriteData &data)
{
    this->setSpritePosition(data.getSpritePosition());
    this->setSpriteScale(data.getSpriteScale());
}

QPointF SpriteData::getSpritePosition() const
{
    return QPointF(this->spriteX, this->spriteY);
}

QPointF SpriteData::getSpriteScale() const
{
    return QPointF(this->spriteW, this->spriteH);
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
    return *this;
}
