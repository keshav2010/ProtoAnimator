#include "spritedata.h"
#include<QDebug>
SpriteData::SpriteData()
{
    qDebug()<<"(SpriteData.cpp) constructor";
    spriteX=spriteY=100;
    spriteW=spriteH=0;
}

QPointF SpriteData::getSpritePosition() const
{
    return QPointF(this->spriteX, this->spriteY);
}

QPointF SpriteData::getSpriteScale() const
{
    return QPointF(this->spriteW, this->spriteH);
}

void SpriteData::setSpritePosition(const QPointF &point)
{
    spriteX = point.x();
    spriteY = point.y();
}
void SpriteData::setSpriteScale(const QPointF &point){
    spriteW = point.x();
    spriteH = point.y();
}
