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
    animationDriver = new AnimationDriver();
}
FramesEditor::~FramesEditor()
{
    qDebug()<<"(~FrameEditor.cpp) : deleting frameEditor";
    isAlreadyExist=false;
    delete animationDriver;
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

AnimationDriver *FramesEditor::getAnimationDriver() const
{
    return animationDriver;
}

//SLOT FXN
void FramesEditor::renderFrame(Frame *activeFrame)
{
    qDebug()<<" >>>> framesEditor.cpp (renderFrame SLOT) setting updated scene to framesEditor view";
    setScene(activeFrame);
}
