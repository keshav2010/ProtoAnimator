#include "frameseditor.h"
#include "frame.h"
#include<QMouseEvent>
#include <QScrollBar>

//static data
bool FramesEditor::isAlreadyExist=false;
FramesEditor* FramesEditor::frameEditor = 0;
QWidget* FramesEditor::objectParent = 0;
//---------------------------------------------

FramesEditor::FramesEditor(QWidget* parent):
    QGraphicsView(parent)
{
    qDebug()<<"frameEditor.cpp : initialized FrameEditor (sort of canvas) (QGraphicsView) ...";

    //set frameRect as SCENE-RECTANGLE (this won't draw it on screen)
    setSceneRect(FrameManager::frameSceneRect); //to keep grey-area focused

    this->setToolTip(QString("Frame Editor Window"));
}
FramesEditor::~FramesEditor()
{
    qDebug()<<"frameEditor.cpp : deleting frameEditor/QGraphicsView/Canvas (analogy) from mem";
    isAlreadyExist=false;
    //delete frameEditor; //causing infinite destructor calls
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

//SLOT FXN
void FramesEditor::renderFrame(Frame *activeFrame)
{
    qDebug()<<" >>>> framesEditor.cpp (renderFrame SLOT) setting updated scene to framesEditor view";
    setScene(activeFrame);
    setSceneRect(FrameManager::frameSceneRect); //to keep grey-area focused
}



//Visualising bounding Rectangle that represents a frame
void FramesEditor::drawBackground(QPainter *painter, const QRectF &rect)
{
    //qDebug()<<"frameEditor.cpp : drawing background for scene( current active frames)..";
    //painter->setBrush(QBrush(QColor(50, 50, 50)));
    painter->drawRect(sceneRect());

}

void FramesEditor::drawForeground(QPainter *painter, const QRectF &rect)
{
    //qDebug()<<"frameEditor.cpp : drawing Foreground (current active Frame) : ";
    //painter->setBrush(QBrush(QColor(250,250,200)));
    //painter->drawRect(50,50,100,100);
    scene()->render(painter, sceneRect(), sceneRect());
}

void FramesEditor::mousePressEvent(QMouseEvent *event)
{
    const QPoint clickPosition = event->pos();
    QGraphicsItem *selectedItem = (itemAt(clickPosition));
    if(selectedItem)
    {
        qDebug()<<" item selected : "<<selectedItem;
    }
    else qDebug()<<clickPosition.x()<<", "<<clickPosition.y()<<"";

    qDebug()<<selectedItem;
}
