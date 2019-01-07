#ifndef ANIMATIONDRIVER_H
#define ANIMATIONDRIVER_H

#include <QObject>
#include<QTimer>
/*
 *
 * This class is responsible for driving the
 * animations by traversing some "N" number of
 * frames per second.
 *
 * Value of N is specified by user
 */
class AnimationDriver : public QObject
{
    Q_OBJECT

public:
    AnimationDriver();
    ~AnimationDriver();

public slots:
    void setFPS(int fps);
    void playAnim(); //handles AnimationDriver's state
    void stopAnim();

private slots:
    void traverseFrames(); //responsible for switching frame, called by timer's tick

private:
    int mFps;
    int mCurrentFrame;
    bool mLoop;
    bool mIsPlaying; //current state
    QTimer mTimer; //this signals when to switch to next frame based on fps value
};

#endif // ANIMATIONDRIVER_H
