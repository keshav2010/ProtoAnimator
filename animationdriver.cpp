#include "animationdriver.h"
#include<ctime>
#include<QDebug>
#define SEC2MILLISEC 1000

AnimationDriver::AnimationDriver():
    mLoop(true),
    mFps(30)
{

}

AnimationDriver::~AnimationDriver()
{

}

void AnimationDriver::setFPS(int fps)
{
    this->mFps = fps;
    qDebug()<<"fps is : "<<mFps;
}

void AnimationDriver::playAnim()
{
    int temp = 3;
    float timePerFrame = (1.0/mFps * SEC2MILLISEC); //time slot that is completely reserved to each frame
    clock_t timeTracker;
    /*
     * for each frame
     *      timeTracker = clock();
     *      set it as activeFrame
     *      timeTracker = clock() - timeTracker; (convert to ms)
     *      if(timeTracker < 1000)
     *          wait for remaining period
     *  repeat
     */
}
void AnimationDriver::stopAnim()
{

}
