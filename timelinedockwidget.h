#ifndef TIMELINEDOCKWIDGET_H
#define TIMELINEDOCKWIDGET_H
/*
 * TimelineDockWidget will obtain following information from frameManager
 * 1. Current Active Frame
 * 2. Total Number of Frames
 */
#include<QFrame>
#include<QHBoxLayout>
#include<QWidget>
#include<QVBoxLayout>
#include<QDockWidget>
#include<QPushButton>
#include<QHBoxLayout>
#include<QVBoxLayout>
class TimelineDockWidget :  public QDockWidget
{
protected:
    //sub frames
    QFrame *timelineFrame;
    QFrame *animationControlFrame;
    //main dockWidget frame
    QFrame *mainFrame;
    QHBoxLayout *framesHLayout;


    QPushButton *btn_runAnimation;
    QPushButton *btn_pauseAnimation;
    QPushButton *btn_restartAnimation;
    QVBoxLayout *buttonsVLayout;

public slots:
    void runAnim(int startFromFrame = 0);
    void pauseAnim();
    void restartAnim();

public:
    TimelineDockWidget(QWidget *parent);

};

#endif // TIMELINEDOCKWIDGET_H
