#include "animationdriver.h"
#include<QDebug>
#include "framemanager.h"
#include "frameseditor.h"
/*
 *  AnimationDriver is responsible for traversing over each frame
 *  for a time period (mFps, frame per second)
 *
 *  It uses QTimer instead of a creating a seperate thread for sake of
 *  complexity of program.
 */
AnimationDriver::AnimationDriver():
    mLoop(true),
    mFps(1),
    mCurrentFrame(0),
    mIsPlaying(false)
{
    QObject::connect(&mTimer, SIGNAL(timeout()), this, SLOT(traverseFrames()));
}

AnimationDriver::~AnimationDriver()
{

}

void AnimationDriver::setFPS(int fps)
{
    this->mFps = fps;
}

void AnimationDriver::playAnim()
{
    mIsPlaying = mTimer.isActive();
    if(mIsPlaying){
        return;
    }
    mTimer.start(1000/mFps);
    if(mTimer.isActive())
        mIsPlaying = true;
}
void AnimationDriver::stopAnim()
{
    mIsPlaying = mTimer.isActive();
    if(!mIsPlaying)
        return;
    mTimer.stop();
    mIsPlaying=false;
}

void AnimationDriver::traverseFrames()
{
    const QMap<int, Frame*> *fb = FrameManager::getInstance()->getPointerToFrameBank();
    //FramesEditor::getInstance()->renderFrame((fb->begin() + mCurrentFrame).value());
    FrameManager::getInstance()->setCurrentActiveFrame(mCurrentFrame);
    mCurrentFrame++;
    if(mCurrentFrame >= fb->size()){
        mCurrentFrame=0;
        if(!mLoop)
            stopAnim();
    }
}
