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
void Frame::addFrameItem(AnimatableSpriteItem *item, QString itemName)
{
    qDebug()<<"frame.cpp > addFrameItem : adding item "<<itemName<<" to frameData";

    itemName = itemName.trimmed();
    if(itemName.size()==0)
        return;
    frameData[itemName]=item->getSpriteData();
}

void Frame::setupFrameItems()
{

    QMap<QString, SpriteData>::iterator frameDataIterator = frameData.begin();
    for(frameDataIterator; frameDataIterator!=frameData.end(); frameDataIterator++){
        AnimatableSpriteItem *tempItem = SpriteManager::getInstance()->getObjectGraph()->value(frameDataIterator.key());
        addItem(tempItem);
    }
}


void Frame::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{

}
void Frame::drawForeground(QPainter *painter, const QRectF &rect){

    qDebug()<<"frame.cpp : drawing ForeGround";
    /*
    QMap<QString, QTransform>::iterator frameDataIterator = frameData.begin();
    for(frameDataIterator; frameDataIterator!=frameData.end(); frameDataIterator++){
        painter->drawImage(100,100, (*frameDataIterator)->pixmap().toImage());
    }
    */
    painter->setBrush(QBrush(QColor(5,255,255,1)));
    painter->drawRect(FrameManager::frameSceneRect);
    painter->drawRect(QRect(100,100,200,200));

    QMap<QString, SpriteData>::iterator frameDataIterator = frameData.begin();
    for(frameDataIterator; frameDataIterator!=frameData.end(); frameDataIterator++)
    {
        painter->drawPixmap((*frameDataIterator).getSpritePosition(),
                            SpriteManager::getInstance()->getObjectGraph()->value(frameDataIterator.key())->pixmap());
    }


}
