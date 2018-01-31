#include "frameseditor.h"
#include "frame.h"
#include <QScrollBar>

//static data
bool FramesEditor::isAlreadyExist=false;
FramesEditor* FramesEditor::frameEditor = 0;
QWidget* FramesEditor::objectParent = 0;


FramesEditor::~FramesEditor()
{
    isAlreadyExist=false;
    delete frameEditor;
}

FramesEditor *FramesEditor::getInstance()
{
    if( !isAlreadyExist){
        frameEditor = new FramesEditor(objectParent);
        isAlreadyExist=true;
    }
    return frameEditor;
}

void FramesEditor::setParent(QWidget *parent)
{
    objectParent = parent;
}

FramesEditor::FramesEditor(QWidget* parent):
    QGraphicsView(parent)
{
    //set frameRect as SCENE-RECTANGLE (this won't draw it on screen)
    setSceneRect(FrameManager::frameSceneRect); //to keep grey-area focused

    this->setToolTip(QString("Frame Editor Window"));
    setScene(FrameManager::getInstance()->getDefaultFrame());

    //add graphicsItem to scene

}

//Visualising bounding Rectangle that represents a frame
void FramesEditor::drawBackground(QPainter *painter, const QRectF &rect)
{
    painter->setBrush(QBrush(QColor(240,240,240)));
    painter->drawRect(sceneRect());

}
