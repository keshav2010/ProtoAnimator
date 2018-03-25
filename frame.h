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
public slots:
    //Adds raw properties of an sprite object to frameData
    void addFrameItem(AnimatableSpriteItem *item=0, QString itemName="");
    void setupFrameItems();//take up ownership of items
    void clearFrameItems();//give up owner ship of items

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void drawForeground(QPainter *painter, const QRectF &rect) override;
private:
    //frameData contains list of all sprite names and stores their respective position and scale
    QMap<QString, SpriteData> frameData;

    const int frameWidth, frameHeight;
};

#endif // FRAME_H
