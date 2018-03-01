#ifndef SPRITEDATA_H
#define SPRITEDATA_H
#include<QTransform>
#include<QPointF>
class SpriteData : public QTransform
{
public:
    SpriteData();
    QPointF getSpritePosition();
    QPointF getSpriteScale();

    void setSpritePosition(const QPointF &point);
    void setSpriteScale(const QPointF &point);
protected:
    qreal spriteX, spriteY, spriteW, spriteH;
};

#endif // SPRITEDATA_H
