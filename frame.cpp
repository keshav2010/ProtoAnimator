#include "frame.h"
#include<QGraphicsSceneMouseEvent>
#include<QDebug>
#include<QPainter>
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

}

void Frame::drawBackground(QPainter *painter, const QRectF &rect)
{

}
