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
    ~Frame();
    QSize getFrameSize();
    int getFrameWidth();
    int getFrameHeight();

    //method to create deep copy
    void copyData(Frame* other=0);

public slots:
    QMap<QString, AnimatableSpriteItem *> *getFrameData();
    //Adds raw properties of an sprite object to frameData
    void addFrameItem(QString itemName="", QPixmap *spritePixmap=0);
    void setupFrameItems();//take up ownership of items
    void clearFrameItems();//give up owner ship of items
protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void drawForeground(QPainter *painter, const QRectF &rect) override;
    void drawBackground(QPainter *painter, const QRectF &rect) override;
private:

    //required to create clones
    QMap<QString, AnimatableSpriteItem*> *frameData;//should be a pointer
    const int frameWidth, frameHeight;
};

#endif // FRAME_H
