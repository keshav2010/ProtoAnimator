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
private:
    //frameData contains list of all sprite names and stores their respective position and scale
    QMap<QString, SpriteData> frameData;

    const int frameWidth, frameHeight;
public:
    Frame(QObject *parent=0);

    QSize getFrameSize();
    int getFrameWidth();
    int getFrameHeight();
public slots:
    //Adds raw properties of an sprite object to frameData
    void addFrameItem(AnimatableSpriteItem *item=0, QString itemName="");
    void setupFrameItems();

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void drawForeground(QPainter *painter, const QRectF &rect) override;
};

#endif // FRAME_H
