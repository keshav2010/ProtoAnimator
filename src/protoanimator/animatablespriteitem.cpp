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
    spritePixmap =  nullptr;
    this->spriteData.setSpritePosition(QPointF(0,0));

    setFlag(GraphicsItemFlag::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable);
    sizeMarkers.resize(4);
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
    sizeMarkers.resize(4);
}

AnimatableSpriteItem::~AnimatableSpriteItem()
{
    qDebug()<<"(~AnimatableSpiteItem.cpp) > removed "+this->getName()<<" from memory";

    for(int i=0; i<4; i++)
    {
        qDebug()<<"attempting for : sizeMarker "<<i<<" : "<<(sizeMarkers[i] == nullptr);
        if(sizeMarkers[i] == nullptr){
            continue;
        }
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
    //bounding rect is calculated based on values of "spriteData"
    qreal tempWidth = spriteData.getSpriteScale().x();
    qreal tempHeight = spriteData.getSpriteScale().y();
    return QRectF(0, 0, tempWidth, tempHeight);

    //return this->pixmap().rect();
}

/*
 * shape() method makes it possible for user to click on enlarged painted region and drag it around
 * also it does not adhere to the strict shape of image (such as ignoring transparency and only considering actual visible
 * image shape) but rather construct a rectangular area using spriteData object
 */
QPainterPath AnimatableSpriteItem::shape() const
{
    QPainterPath path;
    path.addRect(0, 0, this->spriteData.getSpriteScale().x(), this->spriteData.getSpriteScale().y());
    return path;
}


//override
void AnimatableSpriteItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPixmap temp = (*spritePixmap).scaled(spriteData.getSpriteScale().x(), spriteData.getSpriteScale().y());
    painter->drawPixmap(boundingRect().x(), boundingRect().y(),
                        temp.width(), temp.height(), temp);
    painter->setBrush(QBrush(QColor(Qt::black)));
    painter->drawRect(this->spritePixmap->rect());
    //painter->drawPixmap(boundingRect().x(), boundingRect().y(), boundingRect().width(), boundingRect().height(), this->pixmap());
   //QGraphicsPixmapItem::paint(painter, option, widget); //call base class paint method
}

bool AnimatableSpriteItem::sceneEventFilter(QGraphicsItem *watched, QEvent *event)
{ //RETURN FALSE => PROPAGATE EVENT TO watched , TRUE => DO NOT PROPAGATE
    qDebug()<<"QEvent == "<<QString::number(event->type());
    //when user clicks on any sizeMarker, this function will be called
    // the sizeMarker that is pressed is being pointed by *watched
    SizeChangeMarker *sizeBox = dynamic_cast<SizeChangeMarker*>(watched);
    if(sizeBox==nullptr) // not expected to execute this code
        return false;
    qDebug()<<"sizeBox is : "<<sizeBox->getMarkerType();
    qDebug()<<"EventFilter : checking event type";
    //cast to mouseEvent will be null for non-mouse events
    QGraphicsSceneMouseEvent *mevent = dynamic_cast<QGraphicsSceneMouseEvent*>(event);
    qDebug()<<" isEVENT of mouse ? "<<(mevent!=nullptr);
    if(mevent==nullptr)
        return false;

    switch(mevent->type()){
       case QEvent::GraphicsSceneMousePress:
        {
            sizeBox->setMouseState(SizeChangeMarker::kMouseDown);
            //Record position when clicked first, this won't update even if mouse is moved around
            sizeBox->mouseDownX = mevent->pos().x();
            sizeBox->mouseDownY = mevent->pos().y();

            qDebug()<<sizeBox->mouseDownX<<" "<<sizeBox->mouseDownY;
        }
        break;

    case QEvent::GraphicsSceneMouseRelease:
        {
            sizeBox->setMouseState(SizeChangeMarker::kMouseReleased);
        }
        break;

    case QEvent::GraphicsSceneMouseMove:
        {
            sizeBox->setMouseState(SizeChangeMarker::kMouseMoving);
        }
        break;

    default:
        return false;
        break;
    }
    if(sizeBox->getMouseState() == SizeChangeMarker::kMouseMoving)
    {
        qreal x = mevent->pos().x();
        qreal y = mevent->pos().y();
        int XaxisSign = 0;
        int YaxisSign = 0;
        switch(sizeBox->getMarkerType())
        {
            case TOP_LEFT:
            {
                XaxisSign=1;
                YaxisSign=1;
            }
            break;
            case TOP_RIGHT:
            {
                XaxisSign=-1;
                YaxisSign=1;
            }
            break;
            case BOTTOM_RIGHT:
            {
                XaxisSign=-1;
                YaxisSign=-1;
            }
            break;
            case BOTTOM_LEFT:
            {
                XaxisSign=1;
                YaxisSign=-1;
            }
            break;

        }

        //if mouse is being dragged, calculate new size + reposition sprite
        //to give appearance of dragging corner in/out
        int xMoved = sizeBox->mouseDownX - x;
        int yMoved = sizeBox->mouseDownY - y;
        int deltaWidth = XaxisSign*xMoved;
        int deltaHeight = YaxisSign*yMoved;

        //adjustSize by changing spriteData values, these values will be used by paint method to simply
        //scale the original pixmap according to these values, this way we retain the original pixmap too
        qreal currentWidth = this->spriteData.getSpriteScale().x();
        qreal currentHeight = this->spriteData.getSpriteScale().y();
        this->spriteData.setSpriteScale(QPointF(currentWidth+deltaWidth, currentHeight+deltaHeight));

        //TODO : if new scaling technique doesn't back, remove comments from below code
        //QPixmap currentPixmap = this->pixmap();
        //QPixmap newPixmap = currentPixmap.scaled(currentPixmap.width()+deltaWidth, currentPixmap.height()+deltaHeight);
        //this->setSpritePixmap(newPixmap);

        deltaWidth *= (-1);
        deltaHeight *= (-1);

        if(sizeBox->getMarkerType() == TOP_LEFT)
        {
            int newXpos = this->pos().x() + deltaWidth;
            int newYpos = this->pos().y() + deltaHeight;
             spriteData.setSpritePosition(QPointF(newXpos, newYpos));
             this->setPos(newXpos, newYpos);
        }
        else if(sizeBox->getMarkerType() == TOP_RIGHT)
        {
            int newYpos = this->pos().y() + deltaHeight;
             spriteData.setSpritePosition(QPointF(this->pos().x(), newYpos));
             this->setPos(this->pos().x(), newYpos);
        }
        else if(sizeBox->getMarkerType() == BOTTOM_LEFT)
        {
            int newXpos = this->pos().x() + deltaWidth;
             spriteData.setSpritePosition(QPointF(newXpos, this->pos().y()));
             this->setPos(newXpos, this->pos().y());
        }
        setSizeMarkerPosition();
        this->update();
    }
    return true;
}

void AnimatableSpriteItem::setSpritePixmap(const QPixmap &sprite)
{
    qDebug()<<"AnimatableSpriteItem :: setSpritePixmap called \n Width,Height = ("<<sprite.width()<<","<<sprite.height()<<")";
    //if existing spritePixmap exists, clear it from memory
    if(spritePixmap != nullptr){
        delete spritePixmap;
        spritePixmap=nullptr;
    }
    spritePixmap = new QPixmap(sprite);

    //update Sprite Data
    spriteData.setSpriteScale(QPointF(sprite.width(), sprite.height()));
    spriteData.setSpritePosition(QPointF(this->x(), this->y()));

    this->setPixmap(*spritePixmap);
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
    for(int i=0; i<4; i++){

        if(sizeMarkers[i] != nullptr)
            continue;
        sizeMarkers[i] = new SizeChangeMarker(this);
        sizeMarkers[i]->installSceneEventFilter(this);
        sizeMarkers[i]->setMarkerType(i);
    }
    this->setSizeMarkerPosition();
    event->setAccepted(true);
}

void AnimatableSpriteItem::setSizeMarkerPosition()
{
    //assumed to be square
    float markerWidth = sizeMarkers[TOP_LEFT]->boundingRect().width();

    sizeMarkers[TOP_LEFT]->setPos(boundingRect().topLeft());
    sizeMarkers[TOP_RIGHT]->setPos(boundingRect().topRight() + QPointF(-markerWidth, 0));
    sizeMarkers[BOTTOM_LEFT]->setPos(boundingRect().bottomLeft() + QPointF(0,-markerWidth));
    sizeMarkers[BOTTOM_RIGHT]->setPos(boundingRect().bottomRight() + QPointF(-markerWidth, -markerWidth));
}
//----------------------------------------------------------------------------------------------



SizeChangeMarker::SizeChangeMarker(QGraphicsItem *parent):
    QGraphicsItem(parent),
    mouseDownX(0),
    mouseDownY(0)
{
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

void SizeChangeMarker::setMarkerType(int t)
{
    mMarkerType = t;
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
    brush.setColor(QColor(0,200,0));
    painter->fillRect(rect, brush);
}

QRectF SizeChangeMarker::boundingRect() const
{
    return QRectF(0,0, 10, 10);
}

void SizeChangeMarker::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    this->update(0, 0, 10, 10);
}

void SizeChangeMarker::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    this->update(0, 0, 10, 10);
}

void SizeChangeMarker::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    event->setAccepted(false);
}

void SizeChangeMarker::mouseMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    event->setAccepted(false);
}

void SizeChangeMarker::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    event->setAccepted(false);
}

void SizeChangeMarker::mousePressEvent(QGraphicsSceneDragDropEvent *event)
{
    event->setAccepted(false);
}

void SizeChangeMarker::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    event->setAccepted(true);
}
