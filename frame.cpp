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
    this->frameData = new QMap<QString, AnimatableSpriteItem*>();
    qDebug()<<"(Frame.cpp) constructor";
    setBackgroundBrush(QBrush(QColor(120,50,100)));
}

Frame::~Frame(){
    qDebug()<<"***Frame.cpp : deleting frame";
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

void Frame::copyData(Frame *other)
{
    if(other == 0)
        return;
    QMap<QString, AnimatableSpriteItem*>::iterator sourceITR = other->getFrameData()->begin();
    QMap<QString, AnimatableSpriteItem*>::Iterator endITR = other->getFrameData()->end();
    for(sourceITR; sourceITR != endITR; sourceITR++)
    {
        AnimatableSpriteItem *sourceItem = sourceITR.value();
        QString sourceItemName = sourceITR.key();

    }
}

QMap<QString, AnimatableSpriteItem *> *Frame::getFrameData()
{
    return this->frameData;
}

/*
 * This function loads up an Item in frame
 */
void Frame::addFrameItem(QString itemName, QPixmap *spritePixmap) //slot fxn
{

    AnimatableSpriteItem *item = new AnimatableSpriteItem(0);
    qDebug()<<"(Frame.cpp > addFrameItem()) : adding item "<<itemName<<" to frame";
    itemName = itemName.trimmed();
    if(itemName.size()==0){
        return;
    }
    if(frameData->contains(itemName)){
        return; //same name not allowed
    }

    item->setName(itemName);
    item->setSpritePixmap(*spritePixmap);

    //frameData required to create clones
    (*frameData)[itemName]=item;

    addItem(item);
    qDebug()<<"(Frame.cpp > addFrameItem()) : item added !!! ";
}

//Function to load scene with the items
void Frame::setupFrameItems()
{
}


/*
 * clears frameData QMap container, as well also remove items from Scene itself.
 *
 * note that when an item is removed from scene, its children will also be removed
 * however they will still exist in the QMap
*/
void Frame::clearFrameItems()//slot fxn
{
    QMap<QString, AnimatableSpriteItem*>::iterator itemsITR =frameData->begin();
    QMap<QString, AnimatableSpriteItem*>::iterator endITR = frameData->end();
    for(itemsITR; itemsITR != endITR; itemsITR++)
    {
        AnimatableSpriteItem *item = itemsITR.value();
        if(this->items().contains(item))
            this->removeItem(item);
        delete item;
    }
}

void Frame::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{

}
void Frame::drawBackground(QPainter *painter, const QRectF &rect){
    painter->setBrush(QBrush(QColor(50, 250, 50)));
    painter->drawRect(FrameManager::frameSceneRect);
}
void Frame::drawForeground(QPainter *painter, const QRectF &rect)
{
}
