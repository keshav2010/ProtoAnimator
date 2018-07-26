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

    addFrameObject();//frameBank.insert(0, new Frame(this));
    startFrame = frameBank.value(0);
    //currentActiveFrame=0;

    FramesEditor::getInstance()->renderFrame(startFrame);
    qDebug()<<"frameManager.cpp : setting up current Frame "<<startFrameIndex;
}

FrameManager::~FrameManager()
{
    qDeleteAll(frameBank);
    frameBank.clear();
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
    return frameBank.value(currentActiveFrame);
}

void FrameManager::setCurrentActiveFrame(int frameKey)
{
    if(this->frameBank.contains(frameKey))
        currentActiveFrame = frameKey;
    FramesEditor::getInstance()->renderFrame(frameBank.value(currentActiveFrame));
}
int FrameManager::getCurrentActiveFrameByID(){
    return currentActiveFrame;
}

//DEBUG : should be reconsidered,
//this is returning frameBank address
//where frameBank exists on stack
QMap<int, Frame *>* FrameManager::getPointerToFrameBank()
{
    return (&frameBank);
}

/**
 * Adds new frame object,
 * also copies data from previous frame and creates a deep copy of that frame.
 *
 * emits : frameBankChanged, slot triggered : TimelineModel::updateDataSource
 * see timelinedockwiget.cpp for QObject::connect(..)
 */
bool FrameManager::addFrameObject() //slot function
{
    qDebug()<<"(FrameManager.cpp) > addFrameObject() : adding new Frame ";
    int oldFrameKey=-1;

    if(!frameBank.empty())
        oldFrameKey = frameBank.lastKey();

    int newFrameKey = oldFrameKey+1;
    Frame *newFrame = new Frame(this);
    frameBank.insert(newFrameKey, newFrame);
    currentActiveFrame = newFrameKey;


    if(oldFrameKey >=0 && frameBank.value(oldFrameKey)->items().size() == 0)
    {
        qDebug()<<"(FrameManager.cpp) > addFrameObject() : setting newFrame in FrameEditor view with no data to carry forward";
        FramesEditor::getInstance()->renderFrame(newFrame);
        emit frameBankChanged(&frameBank);
        return true;
    }

    Frame *prevFrame = frameBank.value(oldFrameKey);

    //copy content of previous frame (deep copy)
    newFrame->copyData(prevFrame);

    FramesEditor::getInstance()->renderFrame(newFrame);

    /*
     * triggers slot TimelineModel::updateDataSource()
     * that re-assigns reference
    */
    emit frameBankChanged(&frameBank);
    return true;
}

void FrameManager::deleteFrames(QVector<int> &frameKeys)
{
    qDebug()<<"size before : "<<frameBank.size();
    QVector<int>::iterator itrBegin = frameKeys.begin();
    QVector<int>::iterator itrEnd = frameKeys.end();
    for(itrBegin; itrBegin != itrEnd; itrBegin++){
        int frameKey = (*itrBegin);
        if(!frameBank.contains(frameKey))
            continue;
        delete frameBank.value(frameKey);
        frameBank.remove(frameKey);
    }
    qDebug()<<"frameBank size : "<<frameBank.size();
    emit frameBankChanged(&frameBank);
}
