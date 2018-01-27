#include "frameseditor.h"
#include "frame.h"
#include <QScrollBar>
FramesEditor::FramesEditor(QWidget* parent):
    QGraphicsView(parent),
    defaultKeyFrame(new Frame(this))
{
    //setting frame width,height and coordinates on screen
    frameWidth = 800;
    frameHeight = 450;

    frameRect.setX(-frameWidth/2);
    frameRect.setY(-frameHeight/2);

    frameRect.setWidth(frameWidth);
    frameRect.setHeight(frameHeight);

    //set frameRect as SCENE-RECTANGLE (this won't draw it on screen)
    setSceneRect(frameRect); //to keep grey-area focused

    this->setToolTip(QString("Frame Editor Window"));
    setScene(defaultKeyFrame);


    this->scene()->addEllipse(10,10, 500, 200); //adding an ecllipse
    this->scene()->addRect(10,10,250,100,QPen(QColor(200,0,0)));
}

//code to draw frameRect rectangle on screen on lower-most layer, i.e background-layer
//this is done so we can visually see the SCENE-REGION
void FramesEditor::drawBackground(QPainter *painter, const QRectF &rect)
{
    painter->setBrush(QBrush(QColor(240,240,240)));
    painter->drawRect(sceneRect());
}
