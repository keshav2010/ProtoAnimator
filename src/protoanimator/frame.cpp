#include "frame.h"
#include<QGraphicsSceneMouseEvent>
#include<QDebug>
#include<QPainter>
#include "spritemanager.h"
#include "framemanager.h"
Frame::Frame(QObject* parent):
    QGraphicsScene(parent),
    frameWidth(800),
    frameHeight(450)
{
    qDebug()<<"(Frame.cpp) constructor";
    setBackgroundBrush(QBrush(QColor(120,50,100)));
    setSceneRect(0, 0, frameWidth, frameHeight);
}

Frame::~Frame(){
    qDebug()<<"(~Frame.cpp ): deleting frame";
    if(frameData.size() < 1)
        return;
    qDeleteAll(frameData.begin(), frameData.end());
    frameData.clear();
}

QSize Frame::getFrameSize(){
    return QSize(frameWidth, frameHeight);
}
int Frame::getFrameWidth(){
    return frameWidth;
}
int Frame::getFrameHeight(){
    return frameHeight;
}

/*
 * This method can be used to copy content of given
 * Frame object.
 */
void Frame::copyData(Frame *other)
{
    qDebug()<<"(Frame.cpp) > copyData() : Copying data of prev. frame";
    if(other == 0){
        qDebug()<<"(Frame.cpp) > copyData() : end";
        return;
    }
    AnimatableSpriteItem *newItem;

    //traverse frameData of previous frame for each sprite item in that frame
    QMap<QString, AnimatableSpriteItem*>::iterator sourceITR = other->getFrameData()->begin();
    QMap<QString, AnimatableSpriteItem*>::Iterator endITR = other->getFrameData()->end();
    for(sourceITR; sourceITR != endITR; sourceITR++)
    {
        newItem = new AnimatableSpriteItem(sourceITR.value());
        frameData.insert(sourceITR.key(), newItem);
        addItem(newItem);

    }
    qDebug()<<" (Frame.cpp) : Cloning complete, items moved : "<<this->items().size()<<", items in previous frame : "<<other->items().size();
}

QMap<QString, AnimatableSpriteItem *>* Frame::getFrameData()
{
    return &frameData;
}

/*
 * This function loads up an Item in frame
 */
void Frame::addFrameItem(QString itemName, QPixmap *spritePixmap) //slot fxn
{

    AnimatableSpriteItem *item = new AnimatableSpriteItem();
    item->setFlag(QGraphicsItem::ItemIsMovable, true);
    qDebug()<<"(Frame.cpp > addFrameItem()) : adding item "<<itemName<<" to frame";
    itemName = itemName.trimmed();
    if(itemName.size()==0){
        return;
    }
    if(frameData.contains(itemName)){
        qDebug()<<"(Frame.cpp > addFrameItem()) > same name exists. failed to add item";
        return;
    }

    item->setName(itemName);
    item->setSpritePixmap(*spritePixmap);

    //frameData required to create clones
    frameData.insert(itemName, item);
    addItem(item);
    emit FrameManager::getInstance()->broadcastFrameItems(&frameData);
    qDebug()<<"(Frame.cpp > addFrameItem()) : item added !!! ";
}

/*
 * clears frameData QMap container, as well also remove items from Scene itself.
 *
 * note that when an item is removed from scene, its children will also be removed
 * however they will still exist in the QMap
*/
void Frame::clearFrameItems()//slot fxn
{
    qDeleteAll(frameData.begin(), frameData.end());
    frameData.clear();
}


/*
 * overloaded implementation used to visualize the
 * scene's bounding rectangle.
 */
void Frame::drawBackground(QPainter *painter, const QRectF &rect)
{
    painter->setBrush(QBrush(QColor(220,250,220)));
    painter->drawRect(this->sceneRect());
}
