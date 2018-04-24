#ifndef ANIMATIONDRIVER_H
#define ANIMATIONDRIVER_H

#include <QObject>
/*
 *
 * This class is responsible for driving the
 * animations by traversing some "N" number of
 * frames per second.
 *
 * Value of N is specified by user
 */
class AnimationDriver
{
public:
    AnimationDriver();
public slots:
    void setFPS(int fps);

private:
    int mFps;
};

#endif // ANIMATIONDRIVER_H
