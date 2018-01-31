#include "framemanager.h"


//static data
FrameManager* FrameManager::frameManager=0;
bool FrameManager::isAlreadyExist=false;
QObject* FrameManager::objectParent=0;
QRectF FrameManager::frameSceneRect = QRectF(0, 0, 800, 450);

FrameManager* FrameManager::getInstance(){

    if(isAlreadyExist)
        return frameManager;

    frameManager = new FrameManager(objectParent);
    isAlreadyExist=true;
    return frameManager;

}

FrameManager::~FrameManager()
{
    isAlreadyExist=false;
    delete frameManager;
}

void FrameManager::setObjectParent(QObject *parent)
{
    objectParent = parent;
}

Frame *FrameManager::getDefaultFrame()
{
    return keyBeginFrame;
}

FrameManager::FrameManager(QObject *parent) : QObject(parent),
    keyStartFrame(0)
{
    keyBeginFrame = new Frame(this);
    currentActiveFrame=0;
    frameBank.insert(keyStartFrame, keyBeginFrame);
}

//slot
bool FrameManager::addFrameObject()
{
    int lastKey = frameBank.lastKey();
    frameBank.insert(lastKey+1, new Frame(this));
    //emit signal to update timeline Dock
}

bool FrameManager::removeFrameObject()
{
    /*
     * if Frame to remove is keyFrame
     *    return false
     */
}
