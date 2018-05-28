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
    keyStartFrame(0)
{
    qDebug()<<"(FrameManager.cpp) constructor";
    frameBank = new QMap<int, Frame*>();

    qDebug()<<"(frameManager.cpp) constructor";
    frameBank->insert(0, new Frame(this));
    qDebug()<<"adding keyframe";
    keyBeginFrame = (*frameBank)[0];
    currentActiveFrame=0;

    qDebug()<<"frameManager.cpp : setting up current Frame "<<keyStartFrame;
    setCurrentActiveFrame(keyStartFrame);
    keyBeginFrame->setupFrameItems();
}

FrameManager::~FrameManager()
{
    delete frameBank;
    qDebug()<<"frameManager.cpp : clearing frameManager object...!!!";
    isAlreadyExist=false;
}

FrameManager* FrameManager::getInstance()
{
    qDebug()<<"inside FrameManager "<<isAlreadyExist;
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
    return keyBeginFrame;
}
Frame *FrameManager::getCurrentActiveFrame()
{
    return (*frameBank)[currentActiveFrame];
}
int FrameManager::getCurrentActiveFrameByID(){
    return currentActiveFrame;
}
void FrameManager::setCurrentActiveFrame(int frameID)
{
    qDebug()<<">>> frameManager.cpp : currentActiveFrame ID : "<<currentActiveFrame;
    Frame *activeFrame = (*frameBank)[currentActiveFrame];

    if(frameBank->contains(frameID)){
        qDebug()<<">>> frameManager.cpp : frame Found in frameBank, setting up for view";

        currentActiveFrame = frameID;
        activeFrame = (*frameBank)[frameID];

        activeFrame->setParent(this);
    }
    qDebug()<<">>> frameManager.cpp : currentActiveFrame ID updated: "<<currentActiveFrame;

    emit setNewActiveFrame(activeFrame);
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
    qDebug()<<"(FrameManager.cpp) : adding new Frame ";

    int oldFrameKey = frameBank->lastKey();
    int newFrameKey = frameBank->lastKey()+1;
    frameBank->insert(newFrameKey, new Frame(this));

    Frame *newFrame = (*frameBank)[newFrameKey];
    qDebug()<<">> frameManager.cpp : added new frame with key : "<<newFrameKey;
    qDebug()<<">> frameManager.cpp : switching to new frame";
    setCurrentActiveFrame(newFrameKey);

    //create deep copy of previous frame , frameData
    Frame *prevFrame = frameBank->value(oldFrameKey);
    newFrame->copyData(prevFrame);

    //x and y are for testing only
    static int x=0, y=0;
    getCurrentActiveFrame()->addRect(x*2, y*3, 50, 50, QPen(QColor(20,10,10*x)), QBrush(QColor(20,10,10)));
    x += 10;
    y += 5;

}
bool FrameManager::removeFrameObject()
{
    qDebug()<<"frameManager.cpp : removing a frame";
    return true;
}

void FrameManager::switchToFrame(int framePos)
{
    QMap<int, Frame*>::iterator frameBankItr = frameBank->begin();
    int totalFrames = frameBank->size();
    if(framePos > totalFrames-1 || framePos < 0)
        return;
    frameBankItr = frameBankItr + framePos;
    int selectedFrameID = frameBankItr.key();
    setCurrentActiveFrame(selectedFrameID);
}
