#include "animatablespriteitem.h"
#include<QPainter>
#include <QGraphicsSceneMouseEvent>
#include<QStyleOptionGraphicsItem>
#include<QVector2D>
#include"frameseditor.h"
#include"vectormaths.h"

#define RAD2DEG 57.2958

AnimatableSpriteItem::AnimatableSpriteItem(QGraphicsItem *parent):
    QGraphicsPixmapItem(parent),
    rotationMarker(nullptr)
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
    QGraphicsPixmapItem(parent),
    spritePixmap(nullptr),
    rotationMarker(nullptr)
{
    qDebug()<<"(AnimatableSpriteItem.cpp) : copy constructor called";

    setFlag(GraphicsItemFlag::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable);

    this->setName(src->getName());

    /*
     * Note that call to setSpritePixmap
     * must be made first, because this method internally
     * assigns some default value to spriteData, so in
     * case we need to have custom spriteData values, we must
     * assign them after call to this method so as to overwrite old values
     */
    this->setSpritePixmap(*(src->spritePixmap));
    this->spriteData = src->spriteData;

    //this->spritePixmap = new QPixmap(*(src->spritePixmap));


    this->setTransform(src->transform());
    this->setPos(src->pos());
    this->setScale(src->scale());
    this->setRotation(src->rotation());
    this->setTransformOriginPoint(src->transformOriginPoint());

    this->setAcceptHoverEvents(true);

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
    if(rotationMarker != nullptr){
        delete rotationMarker;
        rotationMarker = nullptr;
    }
}

//override method
QRectF AnimatableSpriteItem::boundingRect() const
{
    //bounding rect is calculated based on values of "spriteData"
    qreal tempWidth = spriteData.getSpriteScale().x();
    qreal tempHeight = spriteData.getSpriteScale().y();
    return QRectF(0, 0, tempWidth, tempHeight);
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
    //obtain scaled pixmap from base original pixmap and draw it
    QPixmap temp = (*spritePixmap).scaled(spriteData.getSpriteScale().x(), spriteData.getSpriteScale().y());

    /*
     * note that boundingRect is local to the item's coordinate system,
     * translation of its center x,y is done into scene space by painter's transformation system.
    */
    const QRectF boundingBox = this->boundingRect();


    painter->drawPixmap(boundingBox.x(), boundingBox.y(),
                        boundingBox.width(), boundingBox.height(), temp);

    //DEBUG ONLY
    painter->fillRect(QRect(boundingBox.center().x(), boundingBox.center().y(), 20, 20),QColor(200,0,0));
    painter->setBrush(QBrush(QColor(250,250,250)));
    painter->drawText(boundingRect().center() + QPointF(-5, 5), "boundingRectCenter");

    painter->fillRect(QRect(this->transformOriginPoint().x(), transformOriginPoint().y(), 10, 10), QColor(0, 200, 200));
    painter->setBrush(QBrush(QColor(250,250,250)));
    painter->drawText(transformOriginPoint() + QPointF(-5, 5), "TransformOriginPoint");

}


bool AnimatableSpriteItem::sceneEventFilter(QGraphicsItem *watched, QEvent *event)
{
    //RETURN FALSE => PROPAGATE EVENT further (to watched)
    //TRUE => DO NOT PROPAGATE further

    QGraphicsSceneMouseEvent *mevent = dynamic_cast<QGraphicsSceneMouseEvent*>(event);
    if(mevent==nullptr)
        return false;

    // 1 dynamic cast must be != nullptr
    SizeChangeMarker *sizeBox = dynamic_cast<SizeChangeMarker*>(watched);
    RotationMarker *rotBox = dynamic_cast<RotationMarker*>(watched);

    //below if-condition is not expected to execute
    if(rotBox == nullptr && sizeBox == nullptr)
        return false;

    //ROTBOX BEGINS
    if(rotBox != nullptr)
    {
        this->setTransformOriginPoint(boundingRect().center());
        switch(mevent->type()){
            case QEvent::GraphicsSceneMousePress:
                {
                    rotBox->setMouseState(RotationMarker::kMouseDown);
                    //first clicked pos, won't change even if moved
                    rotBox->mouseDownX = mevent->scenePos().x();//mevent->pos().x();
                    rotBox->mouseDownY = mevent->scenePos().y();//mevent->pos().y();
                }break;

            case QEvent::GraphicsSceneMouseRelease:
                {
                    rotBox->setMouseState(RotationMarker::kMouseReleased);
                }break;

            case QEvent::GraphicsSceneMouseMove:
                {
                    rotBox->setMouseState(RotationMarker::kMouseMoving);
                }break;

            default:
                return false; break; //propagate further to the marker itself
        }//end of switch

        if(rotBox->getMouseState() == RotationMarker::kMouseMoving)
        {

            /*
             * all points are in same coordinate space as mousePos
             * pos() method returns the coordinates in parent (if no parent, => coordinate in Scene/Frame Space)
             *
             * Might want to consider ScenePos() in case "this" represents an item which is child of another graphics item
             * or
             * see docs to look up how to transform to scene space
            */
            QPointF sprCenterPos(this->pos() + this->transformOriginPoint());
            QPointF refHeadPos(rotBox->mouseDownX, rotBox->mouseDownY);
            QPointF mousePos(mevent->scenePos());

            qDebug()<<"rotbox > sprCenterPos : "<<(int)sprCenterPos.x()<<(int)sprCenterPos.y();

            //vector from center of sprite to the point where mouse was clicked first before being dragged
            QVector2D referenceVector(0, -1);//(refHeadPos - sprCenterPos); //Reference doesn't change during mouse movement

            //vector from center to current mouse position;
            QVector2D mouseVector(mousePos - sprCenterPos);

            referenceVector.normalize();
            mouseVector.normalize();

            float _dot = referenceVector.x()*mouseVector.x() + referenceVector.y()*mouseVector.y();
            float _det = referenceVector.x()*mouseVector.y() - referenceVector.y()*mouseVector.x();
            float _angle = atan2(_det, _dot)*RAD2DEG;

            qDebug()<<"angle = "<<_angle;

            //before rotation, reset transform origin to be at center
            float newAngle = _angle;//(this->rotation() + _angle);
            if(newAngle < 0)
                newAngle = 360 + newAngle;
            if(newAngle >= 360)
                newAngle = newAngle - 360;

            this->setRotation(newAngle);

            this->update();
        }
        return true; //no need to propagate event any further to marker, every action is processed !
    }
    //------ ROTBOX ENDS----


    //SIZEBOX BEGINS
    if(sizeBox!=nullptr) //sizeBoxes clicked
    {
        switch(mevent->type())
        {
           case QEvent::GraphicsSceneMousePress:
            {
                this->setTransformOriginPoint(boundingRect().center());
                sizeBox->setMouseState(SizeChangeMarker::kMouseDown);

                //Record position when clicked first, this won't update even if mouse is moved around
                sizeBox->mouseDownX = sizeBox->scenePos().x();//sizeBox->boundingRect().center().x();
                sizeBox->mouseDownY = sizeBox->scenePos().y();//sizeBox->boundingRect().center().y();

                //record current center point of image on click in scene/frame space
                sizeBox->refCenterPoint = this->pos() + this->transformOriginPoint();//this->scenePos();//this->boundingRect().center();
            }
            break;

        case QEvent::GraphicsSceneMouseRelease:
            {
                sizeBox->setMouseState(SizeChangeMarker::kMouseReleased);
                this->setTransformOriginPoint(boundingRect().center());
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
        //end of switch

        if(sizeBox->getMouseState() == SizeChangeMarker::kMouseMoving)
        {
            qreal currentMouseX = mevent->scenePos().x();
            qreal currentMouseY = mevent->scenePos().y();

            //vector from center of sprite to current Mouse Position
            QVector2D newRefVector(QPointF(currentMouseX, currentMouseY) - sizeBox->refCenterPoint);

            float newVecSizeX = VectorMaths::projectVector(newRefVector, QVector2D(1, 0)).length();
            float newVecSizeY = VectorMaths::projectVector(newRefVector, QVector2D(0,1)).length();
            QVector2D newVecSize(newVecSizeX, newVecSizeY);

            this->spriteData.setSpriteScale(QPointF(newVecSize.x()*2.0f, newVecSize.y()*2.0f));

            //updates markers position around the sprite
            setSizeMarkerPosition();

            //making sure image stays at same point
            this->setPos(sizeBox->refCenterPoint - this->transformOriginPoint());

            this->setTransformOriginPoint(boundingRect().center());
            this->update();
        }
        return true;
    }
    //------SIZEBOX END
}

void AnimatableSpriteItem::setSpritePixmap(const QPixmap &sprite)
{
    qDebug()<<"AnimatableSpriteItem :: setSpritePixmap called \n Width,Height = ("<<sprite.width()<<","<<sprite.height()<<")";
    //if existing spritePixmap exists, clear it from memory
    qDebug()<<"spritePixmap is : "<<this->spritePixmap;
    if(this->spritePixmap != nullptr){
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

    //init. points on corners
    for(int i=0; i<4; i++){

        if(sizeMarkers[i] != nullptr)
            continue;
        sizeMarkers[i] = new SizeChangeMarker(this);
        sizeMarkers[i]->installSceneEventFilter(this); //all events to markers go-through sprite first
        sizeMarkers[i]->setMarkerType(i);
    }

    this->setSizeMarkerPosition();

    //init rotation Marker
    if(rotationMarker == nullptr){
        rotationMarker = new RotationMarker(this);
        rotationMarker->installSceneEventFilter(this);
    }
    rotationMarker->setPos(boundingRect().center().x(), boundingRect().topLeft().y());

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

    if(this->rotationMarker)
        rotationMarker->setPos(boundingRect().center().x(), boundingRect().topLeft().y());
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
    if(option->state & QStyle::State_MouseOver)
        brush.setColor(QColor(0,200,0));
    else brush.setColor(QColor(0, 0, 200));
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

//--------------------------------------------------------

//--------------------Rotation Marker -----------------
RotationMarker::RotationMarker(QGraphicsItem *parent):
    QGraphicsItem(parent),
    mouseDownX(0),
    mouseDownY(0)
{
    setFlag(GraphicsItemFlag::ItemIsMovable, true);
    setAcceptHoverEvents(true);
}
RotationMarker::~RotationMarker(){

}

int RotationMarker::getMouseState(){
    return mMouseButtonState;
}
void RotationMarker::setMouseState(int s){
    mMouseButtonState = s;
}
//The marker itself
void RotationMarker::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    QPointF topLeft(0,0);
    QPointF bottomRight(10, 10);
    QRectF rect(topLeft, bottomRight);
    QBrush brush(Qt::SolidPattern);
    brush.setColor(QColor(222,0,200));
    painter->fillRect(rect, brush);
}
QRectF RotationMarker::boundingRect() const
{
    return QRectF(0,0, 10, 10);
}
void RotationMarker::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    this->update(0, 0, 10, 10);
}

void RotationMarker::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    this->update(0, 0, 10, 10);
}

void RotationMarker::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    event->setAccepted(false);
}

void RotationMarker::mouseMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    event->setAccepted(false);
}

void RotationMarker::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    event->setAccepted(false);
}

void RotationMarker::mousePressEvent(QGraphicsSceneDragDropEvent *event)
{
    event->setAccepted(false);
}

void RotationMarker::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    event->setAccepted(true);
}
