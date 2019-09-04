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
    QPointF getSpriteRotation() const;

    SpriteData& setSpritePosition(const QPointF &point);
    SpriteData& setSpriteScale(const QPointF &point);
    SpriteData& setSpriteRotation(const QPointF &point);

    SpriteData& operator= (const SpriteData& t);

protected:
    qreal spriteX, spriteY, spriteW, spriteH;
    qreal rotX, rotY;
};

#endif // SPRITEDATA_H
