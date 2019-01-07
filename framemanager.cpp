#include "framemanager.h"
//static data
FrameManager* FrameManager::frameManager=0;
bool FrameManager::isAlreadyExist = false;

QObject* FrameManager::objectParent=0;
QRectF FrameManager::frameSceneRect = QRectF(0, 0, 800, 400);
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
    if(!isAlreadyExist){
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

    emit this->broadcastFrameItems(this->getCurrentActiveFrame()->getFrameData());
}
int FrameManager::getCurrentActiveFrameByID(){
    return currentActiveFrame;
}

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
    if(!frameBank.empty()){
        oldFrameKey = frameBank.lastKey();
    }
    int newFrameKey = oldFrameKey+1;
    Frame *newFrame = new Frame(this);
    frameBank.insert(newFrameKey, newFrame);
    currentActiveFrame = newFrameKey;
    /*
     * if the newly created frame is not the first frame,
     * check if immediate previous frame contains any data, if yes ignore this
     * conditional check
     *
     * otherwise execute this check and simply emit signals and stop.
     * NOTE : Using nested if because i don't wish to take any risk
     * regarding short-circuit evaluation of the condition which may cause
     * segmentation fault.
     */
    if(frameBank.contains(oldFrameKey)){
        if(frameBank.value(oldFrameKey)->items().size() != 0){
            Frame *prevFrame = frameBank.value(oldFrameKey);
            //copy content of previous frame (deep copy)
            newFrame->copyData(prevFrame);
        }
    }
    FramesEditor::getInstance()->renderFrame(newFrame);
    //signal that carry the updated frameBank information
    //this information is what used by Timeline to show frameCount.
    emit frameBankChanged(&frameBank);

    //signal Broadcasting content of newly created frame,this information is
    //used by FrameItemTree dockwidget to display content in a frame.
    emit broadcastFrameItems(getCurrentActiveFrame()->getFrameData());
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
