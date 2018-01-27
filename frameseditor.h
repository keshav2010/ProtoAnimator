#ifndef FRAMESEDITOR_H
#define FRAMESEDITOR_H

#include<QGraphicsView>
#include<QGraphicsScene>
#include "frame.h"
#include <QRectF>
/*
 * FrameEditor class inherits QGraphicsView, which is used to render QGraphicsScene
 * overall, FrameEditor will be used to view animation-frame (class in : frame.h) , interact with frame
 * data and manipulate it.
 *
 * It is to be noted that frameEditor when initialized, should provide atleast 1 single frame by default to work upon,
 * further frames can then later be added by user
 */
class FramesEditor : public QGraphicsView
{
public:
    FramesEditor(QWidget* parent = Q_NULLPTR);

private:
    int frameWidth, frameHeight;
    void drawBackground(QPainter *painter, const QRectF &rect);
    QRectF frameRect;
    Frame *defaultKeyFrame;//the default non-deletable key-frame
};

#endif // FRAMESEDITOR_H
