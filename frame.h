#ifndef FRAME_H
#define FRAME_H

#include<animatablespriteitem.h>
#include<QMap>
#include<QGraphicsScene>

/*
 *
 */
class Frame : public QGraphicsScene
{

public:
    Frame(QObject *parent=0);
    virtual ~Frame();
    QSize getFrameSize();
    int getFrameWidth();
    int getFrameHeight();

    //method to create deep copy
    void copyData(Frame* other=0);

public slots:
    QMap<QString, AnimatableSpriteItem *> *getFrameData();
    void addFrameItem(QString itemName="", QPixmap *spritePixmap=0);
    void clearFrameItems();

private:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void drawBackground(QPainter *painter, const QRectF &rect);

    //required to create clones
    QMap<QString, AnimatableSpriteItem*> frameData;

    const int frameWidth, frameHeight;
};

#endif // FRAME_H
