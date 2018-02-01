#include "frame.h"
#include<QGraphicsSceneMouseEvent>
#include<QDebug>
#include<QPainter>
#include "spritemanager.h"
Frame::Frame(QObject* parent):
    QGraphicsScene(parent),
    frameWidth(800),
    frameHeight(450)
{
    setBackgroundBrush(QBrush(QColor(220,50,100)));
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
void Frame::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    addRect(mouseEvent->buttonDownScenePos(Qt::MouseButton::LeftButton).x(),
            mouseEvent->buttonDownScenePos(Qt::MouseButton::LeftButton).y(),
            50,50);

}
void Frame::drawForeground(QPainter *painter, const QRectF &rect){
    const QMap<QString, AnimatableSpriteItem*> *objectGraph_ref = SpriteManager::getInstance()->getObjectGraph();
    for(int i=0; i<objectGraph_ref->size(); i++){
        AnimatableSpriteItem* item = *(objectGraph_ref->begin()+i);
        painter->drawImage(100,100, item->pixmap().toImage());
    }
}
