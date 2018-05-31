#include "framemanager.h"
//static data
FrameManager* FrameManager::frameManager=0;
bool FrameManager::isAlreadyExist = false;

QObject* FrameManager::objectParent=0;
QRectF FrameManager::frameSceneRect = QRectF(0, 0, 800, 450);
//-------------------------------------------------------------

/* responsible for handling frames
 * uses frameEditor to render data. */
FrameManager::FrameManager(QObject *parent):
    QObject(parent),
    startFrameIndex(0)
{
    qDebug()<<"(frameManager.cpp) constructor";

    frameBank = new QMap<int, Frame*>();
    frameBank->insert(0, new Frame(this));
    startFrame = (*frameBank)[0];
    currentActiveFrame=0;


    FramesEditor::getInstance()->renderFrame(startFrame);
    qDebug()<<"frameManager.cpp : setting up current Frame "<<startFrameIndex;

}

FrameManager::~FrameManager()
{
    delete frameBank;
    qDebug()<<"frameManager.cpp : clearing frameManager object...!!!";
    isAlreadyExist=false;
}

FrameManager* FrameManager::getInstance()
{
    if(!isAlreadyExist)
    {
        isAlreadyExist=true;
        frameManager = new FrameManager(objectParent);
    }
    return frameManager;
}

void FrameManager::setObjectParent(QObject *parent)
{
    objectParent = parent;
}

Frame *FrameManager::getDefaultFrame()
{
    return startFrame;
}
Frame *FrameManager::getCurrentActiveFrame()
{
    return (*frameBank)[currentActiveFrame];
}
int FrameManager::getCurrentActiveFrameByID(){
    return currentActiveFrame;
}

//DEBUG : should be reconsidered,
//this is returning frameBank address
//where frameBank exists on stack
QMap<int, Frame *>* FrameManager::getPointerToFrameBank()
{
    return frameBank;
}

/*
 * Adds new frame object,
 * also copies data from previous frame and creates a deep copy of that frame.
 */
bool FrameManager::addFrameObject() //slot function
{
    qDebug()<<"(FrameManager.cpp) > addFrameObject() : adding new Frame ";

    int oldFrameKey = frameBank->lastKey();
    int newFrameKey = oldFrameKey+1;
    Frame *newFrame = new Frame(this);
    frameBank->insert(newFrameKey, newFrame);
    currentActiveFrame = newFrameKey;

    if(frameBank->value(oldFrameKey)->items().size() == 0)
    {
        qDebug()<<"(FrameManager.cpp) > addFrameObject() : setting newFrame in FrameEditor view with no data to carry forward";
        FramesEditor::getInstance()->renderFrame(newFrame);
        return true;
    }

    //create deep copy of previous frame , frameData
    Frame *prevFrame = frameBank->value(oldFrameKey);
    newFrame->copyData(prevFrame);

}
