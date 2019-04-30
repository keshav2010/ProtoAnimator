#ifndef SPRITEDATA_H
#define SPRITEDATA_H
#include<QTransform>
#include<QPointF>
class SpriteData
{
public:
    SpriteData();
    SpriteData(const SpriteData &data);
    QPointF getSpritePosition() const;
    QPointF getSpriteScale() const;

    SpriteData& setSpritePosition(const QPointF &point);
    SpriteData& setSpriteScale(const QPointF &point);

    SpriteData& operator= (const SpriteData& t);

protected:
    qreal spriteX, spriteY, spriteW, spriteH;
};

#endif // SPRITEDATA_H
