#include "framemanager.h"
//static data
FrameManager* FrameManager::frameManager=0;
bool FrameManager::isAlreadyExist=false;
QObject* FrameManager::objectParent=0;
QRectF FrameManager::frameSceneRect = QRectF(0, 0, 800, 450);
//-------------------------------------------------------------



/*
 * FrameManager is only responsible for handling
 * frame Banks and acting as an efficient frame-storage manager.
 *
 *  it should not directly interact with rendering but rather use
 * frameEditor to render data.
 */
FrameManager::FrameManager(QObject *parent) : QObject(parent),
    keyStartFrame(0)
{
    qDebug()<<"frameManager.cpp : initialized frameManager";

    frameBank.insert(0, new Frame(this));

    keyBeginFrame = frameBank[0];
    currentActiveFrame=0;

    qDebug()<<"frameManager.cpp : setting up current Frame "<<keyStartFrame;
    setCurrentActiveFrame(keyStartFrame);
    keyBeginFrame->setupFrameItems();
}
FrameManager::~FrameManager()
{
    qDebug()<<"frameManager.cpp : clearing frameManager object...!!!";
    isAlreadyExist=false;
    //delete frameManager;
}
FrameManager* FrameManager::getInstance(){

    if(isAlreadyExist)
        return frameManager;

    frameManager = new FrameManager(objectParent);
    isAlreadyExist=true;
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
    return frameBank[currentActiveFrame];
}
int FrameManager::getCurrentActiveFrameByID(){
    return currentActiveFrame;
}
void FrameManager::setCurrentActiveFrame(int frameID)
{
    qDebug()<<">>> frameManager.cpp : currentActiveFrame ID : "<<currentActiveFrame;
    Frame *activeFrame = frameBank[currentActiveFrame];

    if(frameBank.contains(frameID)){
        qDebug()<<">>> frameManager.cpp : frame Found in frameBank, setting up for view";

        currentActiveFrame = frameID;
        activeFrame = frameBank[currentActiveFrame];

        activeFrame->setParent(this);
    }
    qDebug()<<">>> frameManager.cpp : currentActiveFrame ID updated: "<<currentActiveFrame;

    emit setNewActiveFrame(activeFrame);
}
//SLOTS FXN
bool FrameManager::addFrameObject()
{
    qDebug()<<"frameManager.cpp : adding new Frame ";

    int newFrameKey = frameBank.lastKey()+1;
    frameBank.insert(newFrameKey, new Frame(this));

    Frame *newFrame = frameBank[newFrameKey];
    qDebug()<<"frameManager.cpp : added new frame with key : "<<newFrameKey;
    qDebug()<<"frameManager.cpp : switching to new frame";

    //load content from content bank into this frame
    const QMap<QString, AnimatableSpriteItem*> *ptrObjectGraph = SpriteManager::getInstance()->getObjectGraph();
    QMap<QString, AnimatableSpriteItem*>::const_iterator graphItr = (*ptrObjectGraph).begin();
    qDebug()<<"frameManager.cpp : adding content of object graph into newly added frame";
    for(graphItr; graphItr != (*ptrObjectGraph).end(); graphItr++)
    {
        newFrame->addFrameItem(graphItr.value(), graphItr.value()->getName());
    }
    setCurrentActiveFrame(newFrameKey);

    //x and y are for testing only
    static int x=0, y=0;
    getCurrentActiveFrame()->addRect(x*2, y*3, 50, 50, QPen(QColor(20,10,10*x)), QBrush(QColor(20,10,10)));
    getCurrentActiveFrame()->addRect(x+10, 2*y+100, 50, 50, QPen(QColor(20+y,10,10)), QBrush(QColor(20,10,10)));
    getCurrentActiveFrame()->addRect(x, y+20, 50, 50, QPen(QColor(20,10*x,10)), QBrush(QColor(20,10,10)));
    x += 10;
    y += 5;

    //emit signal to update timeline Dock
    emit signalTimelineWidget(frameBank.size());
}
bool FrameManager::removeFrameObject()
{
    qDebug()<<"frameManager.cpp : removing a frame";
    /*
     * if Frame to remove is keyFrame
     *    return false
     */
}

void FrameManager::loadFrameDataInFrame()
{
    qDebug()<<" ****** frameManager.cpp >>>>> loading frameData in frame";
    getCurrentActiveFrame()->reloadFrameData();
    FramesEditor::getInstance()->renderFrame(getCurrentActiveFrame());
}

void FrameManager::switchToFrame(int framePos)
{
    QMap<int, Frame*>::iterator frameBankItr = frameBank.begin();
    int totalFrames = frameBank.size();
    if(framePos > totalFrames-1 || framePos < 0)
        return;
    frameBankItr = frameBankItr + framePos;
    int selectedFrameID = frameBankItr.key();
    setCurrentActiveFrame(selectedFrameID);
}
