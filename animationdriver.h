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
class AnimationDriver : public QObject
{
    Q_OBJECT

public:
    AnimationDriver();
    ~AnimationDriver();

public slots:
    void setFPS(int fps);
    void playAnim();
    void stopAnim();

private:
    int mFps;
    bool mLoop;
};

#endif // ANIMATIONDRIVER_H
