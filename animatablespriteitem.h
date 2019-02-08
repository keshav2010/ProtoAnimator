#ifndef ANIMATABLEIMAGEITEM_H
#define ANIMATABLEIMAGEITEM_H

#include<QGraphicsItem>
#include<QGraphicsPixmapItem>
#include<QGraphicsRectItem>
#include<QRectF>
#include<QPixmap>
#include<QImage>
#include "spritedata.h"

#define TOP_LEFT 0
#define TOP_RIGHT 1
#define BOTTOM_LEFT 2
#define BOTTOM_RIGHT 3
class SizeChangeMarker;
class AnimatableSpriteItem : public QGraphicsPixmapItem
{

public:
    AnimatableSpriteItem(QGraphicsItem *parent = 0);
    AnimatableSpriteItem(AnimatableSpriteItem* src, QGraphicsItem *parent=0);
    ~AnimatableSpriteItem();

    QRectF boundingRect() const override; //returns estimate of area painted by this item
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    bool sceneEventFilter(QGraphicsItem *watched, QEvent *event) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;

    void setSpritePixmap(const QPixmap &sprite);

    SpriteData getSpriteData();
    void setSpriteData(SpriteData &data);
    QString getName();
    void setName(const QString &name);
    QPixmap *spritePixmap;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    void setSizeMarkerPosition();
    SizeChangeMarker *sizeMarkers[4];

    SpriteData spriteData;
    QString mName;
};


//Represent points at corner of the "Sprite" to rescale it
class SizeChangeMarker : public QGraphicsRectItem
{

public:
    SizeChangeMarker(QGraphicsItem *parent=0);

    ~SizeChangeMarker();

    qreal mouseDownX, mouseDownY; //position of mouse when user pressed the lmb
    enum{kMouseReleased=0, kMouseDown, kMouseMoving};

    int getMarkerType();
    void setMouseState(int);
    int getMouseState();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;

private:
    int mMarkerType; //which corner is this, either topLeft, topRight, etc
    int mMouseButtonState;
};

#endif // ANIMATABLEIMAGEITEM_H
