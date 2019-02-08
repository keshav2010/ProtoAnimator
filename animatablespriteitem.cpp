#include "animatablespriteitem.h"
#include<QPainter>
#include <QGraphicsSceneMouseEvent>
#include<QStyleOptionGraphicsItem>
#include"frameseditor.h"

AnimatableSpriteItem::AnimatableSpriteItem(QGraphicsItem *parent):
    QGraphicsPixmapItem(parent)
{
    qDebug()<<"(AnimatableSpriteItem.cpp) : constructor called";
    this->setX(0);
    this->setY(0);
    this->spriteData.setSpritePosition(QPointF(0,0));

    setFlag(GraphicsItemFlag::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable);
    this->setAcceptHoverEvents(true);
}

AnimatableSpriteItem::AnimatableSpriteItem(AnimatableSpriteItem *src, QGraphicsItem *parent):
    QGraphicsPixmapItem(parent)
{
    qDebug()<<"(AnimatableSpriteItem.cpp) : copy constructor called";

    //user defined properties (in order as they appear in declaration)
    this->spritePixmap = new QPixmap(*(src->spritePixmap));
    this->spriteData = src->spriteData;
    this->mName = QString(src->mName);
    this->setTransform(src->transform());
    this->setPos(src->pos());
    this->setScale(src->scale());
    this->setRotation(src->rotation());

    setFlag(GraphicsItemFlag::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable);
    this->setAcceptHoverEvents(true);

    //pre-defined properties
    this->setName(src->getName());
    this->setSpritePixmap(*spritePixmap);

}

AnimatableSpriteItem::~AnimatableSpriteItem()
{
    qDebug()<<"(~AnimatableSpiteItem.cpp) > removed "+this->getName()<<" from memory";

    for(int i=0; i<4; i++)
    {
        if(sizeMarkers[i] == nullptr)
            continue;
        delete sizeMarkers[i];
        sizeMarkers[i]=nullptr;
    }
    if(spritePixmap != nullptr){
        delete spritePixmap;
        spritePixmap = nullptr;
    }
}

//override method
QRectF AnimatableSpriteItem::boundingRect() const
{
    return this->pixmap().rect();
}

//override
void AnimatableSpriteItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(boundingRect().x(), boundingRect().y(), boundingRect().width(), boundingRect().height(), this->pixmap());
    QGraphicsPixmapItem::paint(painter, option, widget);
}

bool AnimatableSpriteItem::sceneEventFilter(QGraphicsItem *watched, QEvent *event)
{ //RETURN FALSE => PROPAGATE EVENT TO watched , TRUE => DO NOT PROPAGATE

    //when user clicks on any sizeMarker, this function will be called
    // the sizeMarker that is pressed is being pointed by *watched
    SizeChangeMarker *sizeBox = dynamic_cast<SizeChangeMarker*>(watched);
    if(sizeBox==NULL) // not expected to execute this code
        return false;

    //cast to mouseEvent will be null for non-mouse events
    QGraphicsSceneMouseEvent *mevent = dynamic_cast<QGraphicsSceneMouseEvent*>(event);
    if(mevent==NULL)
        return false;

    switch(mevent->type()){
       case QEvent::GraphicsSceneMousePress:
        {

        }
        break;

    case QEvent::GraphicsSceneMouseRelease:
        {

        }
        break;

    case QEvent::GraphicsSceneMouseMove:
        {

        }
        break;

    default:
        return false;
        break;
    }

    return true;
}

void AnimatableSpriteItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    qDebug()<<"Hover over imge";
    //instantiate all the corner markers on side
    for(int i=0; i<4; i++){
        sizeMarkers[i] = new SizeChangeMarker(this);
        sizeMarkers[i]->installSceneEventFilter(this);
    }
    this->setSizeMarkerPosition();
}

void AnimatableSpriteItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    //delete all the size markers
    for(int i=0; i<4; i++){
        if(sizeMarkers[i] == nullptr)
            continue;
        delete sizeMarkers[i];
        sizeMarkers[i]=nullptr;
    }
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
    QGraphicsPixmapItem::mousePressEvent(event);
}

void AnimatableSpriteItem::setSizeMarkerPosition()
{
    sizeMarkers[TOP_LEFT]->setPos(boundingRect().topLeft());
    sizeMarkers[TOP_RIGHT]->setPos(boundingRect().topRight());
    sizeMarkers[BOTTOM_LEFT]->setPos(boundingRect().bottomLeft());
    sizeMarkers[BOTTOM_RIGHT]->setPos(boundingRect().bottomRight());
}
//----------------------------------------------------------------------------------------------



SizeChangeMarker::SizeChangeMarker(QGraphicsItem *parent)
{
    setParentItem(parent);
    setFlag(GraphicsItemFlag::ItemIsMovable, true);
    setAcceptHoverEvents(true);
}

SizeChangeMarker::~SizeChangeMarker()
{

}

int SizeChangeMarker::getMarkerType()
{
    return mMarkerType;
}

void SizeChangeMarker::setMouseState(int s)
{
    mMouseButtonState = s;
}

int SizeChangeMarker::getMouseState()
{
    return mMouseButtonState;
}

void SizeChangeMarker::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    QPointF topLeft(0,0);
    QPointF bottomRight(10, 10);
    QRectF rect(topLeft, bottomRight);
    QBrush brush(Qt::SolidPattern);
    brush.setColor(QColor(10,200,10));
    painter->fillRect(rect, brush);
}

QRectF SizeChangeMarker::boundingRect() const
{
    return QRectF(0,0, 10, 10);
}
