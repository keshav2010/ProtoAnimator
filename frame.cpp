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
    qDebug()<<"frame.cpp : initialized frame ";
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

//SLOTS FXN:
/*
 * This function loads up an Item in frame Bank
 * Note that frame will never directly communicate with objectGraph/SpriteBank
 * but rather always tries to indirectly copies its content in its internal
 * bank and later use the internal bank for any modification on it.
 */
void Frame::addFrameItem(AnimatableSpriteItem *item, QString itemName)
{
    qDebug()<<"frame.cpp > addFrameItem : adding item "<<itemName<<" to frameData";

    itemName = itemName.trimmed();

    if(itemName.size()==0)
        return;
    item->setName(itemName);
    frameData[itemName]=item->getSpriteData();
}

//Function to load scene with the items
void Frame::setupFrameItems()
{

    QMap<QString, SpriteData>::iterator frameDataIterator = frameData.begin();
    for(frameDataIterator; frameDataIterator!=frameData.end(); frameDataIterator++){
        //obtain each value/object and add it to this scene/frame
        AnimatableSpriteItem *tempItem = SpriteManager::getInstance()->getObjectGraph()->value(frameDataIterator.key());
           addItem(tempItem);
    }

}
void Frame::clearFrameItems()//slot fxn
{
    QMap<QString, SpriteData>::iterator frameDataIterator = frameData.begin();
    for(frameDataIterator; frameDataIterator!=frameData.end(); frameDataIterator++){

        AnimatableSpriteItem *tempItem =
                SpriteManager::getInstance()->getObjectGraph()->value(frameDataIterator.key());

        removeItem(tempItem);
    }
}
void Frame::reloadFrameData()//slot fxn
{
    qDebug()<<"**(frame.cpp) ::: reloading frame bank with items";
    const QMap<QString, AnimatableSpriteItem*> &tempObjectGraph = *(SpriteManager::getInstance()->getObjectGraph());
    QMap<QString, AnimatableSpriteItem*>::const_iterator objectGraphItr = tempObjectGraph.begin();
    for(objectGraphItr; objectGraphItr != tempObjectGraph.end(); objectGraphItr++)
    {
        AnimatableSpriteItem *tempItemPtr = objectGraphItr.value();
        if(frameData.contains(tempItemPtr->getName()))
            continue;
        frameData[tempItemPtr->getName()] = tempItemPtr->getSpriteData();
    }
    emit FrameManager::getInstance()->frameReadyForDisplay(this);
}


void Frame::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    //qDebug()<<"lol moing mouse";

}
void Frame::drawBackground(QPainter *painter, const QRectF &rect){
    painter->setBrush(QBrush(QColor(50, 250, 50)));
    painter->drawRect(FrameManager::frameSceneRect);
    qDebug()<<"@@@@@@@@@(frame.cpp)::::drawing background";

}
void Frame::drawForeground(QPainter *painter, const QRectF &rect){

    qDebug()<<"**************************************************************frame.cpp : drawing ForeGround";
    QMap<QString, SpriteData>::iterator frameDataIterator = frameData.begin();
    for(frameDataIterator; frameDataIterator!=frameData.end(); frameDataIterator++)
    {
        QPointF tempSpritePos = frameDataIterator.value().getSpritePosition();
        painter->drawImage(tempSpritePos.x(), tempSpritePos.y(),SpriteManager::getInstance()->getObjectGraph()->value(frameDataIterator.key())->pixmap().toImage());
    }
}
