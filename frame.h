#ifndef FRAME_H
#define FRAME_H

#include "animatable.h"
#include<QMap>
#include<QGraphicsScene>

/*
 *
 */
class Frame : public QGraphicsScene
{
private:
    //frameData holds basic properties
    QMap<QString, Animatable*> frameData;
    const int frameWidth, frameHeight;
public:
    Frame(QObject *parent=0);

    QSize getFrameSize();
    int getFrameWidth();
    int getFrameHeight();

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void drawBackground(QPainter *painter, const QRectF &rect) override;
};

#endif // FRAME_H
