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
    qDebug()<<"(FrameEditor.cpp) constructor";
    setMouseTracking(true);
}
FramesEditor::~FramesEditor()
{
    qDebug()<<"(~FrameEditor.cpp) : deleting frameEditor";
    isAlreadyExist=false;
}

FramesEditor *FramesEditor::getInstance()
{
    if( !isAlreadyExist){
        isAlreadyExist=true;
        frameEditor = new FramesEditor(objectParent);
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
    setSceneRect(FrameManager::frameSceneRect);
}

//Visualising bounding Rectangle that represents a frame
void FramesEditor::drawBackground(QPainter *painter, const QRectF &rect)
{
    qDebug()<<"(FramesEditor.cpp) : Drawing background";
    painter->setBrush(QBrush(QColor(220,250,220)));
    painter->drawRect(sceneRect());
}

void FramesEditor::mousePressEvent(QMouseEvent *event)
{
    qDebug()<<" QGraphicsView > mousePressEvent";
    const QPoint clickPosition = event->pos();
    QGraphicsItem *selectedItem = (itemAt(clickPosition));
    if(selectedItem)
    {
        qDebug()<<" item selected : "<<selectedItem;
    }
    else qDebug()<<"(FramesEditor.cpp) :"<<clickPosition.x()<<", "<<clickPosition.y();
}
