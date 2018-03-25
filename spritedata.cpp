#include "spritedata.h"
SpriteData::SpriteData()
{
    spriteX=spriteY=0;
    spriteW=spriteH=0;
}

QPointF SpriteData::getSpritePosition()
{
    return QPointF(this->spriteX, this->spriteY);
}

QPointF SpriteData::getSpriteScale()
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
