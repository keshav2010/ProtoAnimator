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

Frame::~Frame()
{
    qDebug()<<"***Frame.cpp : deleting frame";
}

QSize Frame::getFrameSize()
{
    return QSize(frameWidth, frameHeight);
}

int Frame::getFrameWidth()
{
    return frameWidth;
}

int Frame::getFrameHeight()
{
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
    frameData[itemName]=item->getSpriteData();
}

//Function to load scene with the items
void Frame::setupFrameItems()
{

    QMap<QString, SpriteData>::iterator frameDataIterator = frameData.begin();
    for(frameDataIterator; frameDataIterator!=frameData.end(); frameDataIterator++){
        //obtain each value/object and add it to this scene/frame
        AnimatableSpriteItem *tempItem = SpriteManager::getInstance()->getObjectGraph()->value(frameDataIterator.key());
        //tempItem->setTransform(frameDataIterator.value());
        addItem(tempItem);
    }

}

void Frame::clearFrameItems()
{
    QMap<QString, SpriteData>::iterator frameDataIterator = frameData.begin();
    for(frameDataIterator; frameDataIterator!=frameData.end(); frameDataIterator++){
        //obtain each value/object and add it to this scene/frame
        AnimatableSpriteItem *tempItem = SpriteManager::getInstance()->getObjectGraph()->value(frameDataIterator.key());
        removeItem(tempItem);
    }
}


void Frame::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    qDebug()<<"lol moing mouse";

}
void Frame::drawForeground(QPainter *painter, const QRectF &rect){

    qDebug()<<"frame.cpp : drawing ForeGround";

    painter->setBrush(QBrush(QColor(5,5,5,1)));
    painter->drawRect(FrameManager::frameSceneRect);
    painter->drawRect(QRect(100,100,200,200));

    QMap<QString, SpriteData>::iterator frameDataIterator = frameData.begin();
    for(frameDataIterator; frameDataIterator!=frameData.end(); frameDataIterator++)
    {
        painter->drawImage((*frameDataIterator).getSpritePosition(),
                           SpriteManager::getInstance()->getObjectGraph()->value(frameDataIterator.key())->pixmap().toImage());
    }
}
