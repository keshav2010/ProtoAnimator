#ifndef TIMELINEDOCKWIDGET_H
#define TIMELINEDOCKWIDGET_H

#include<QFrame>
#include<QHBoxLayout>
#include<QWidget>
#include<QVBoxLayout>
#include<QDockWidget>
#include<QPushButton>
class TimelineDockWidget :  public QDockWidget
{
protected:
    QFrame *timelineFrame;
    QFrame *animationControlFrame;

    QPushButton btn_runAnimation;
    QPushButton btn_pauseAnimation;
    QPushButton btn_restartAnimation;

public slots:
    void runAnim(int startFromFrame = 0);
    void pauseAnim();
    void restartAnim();

public:
    TimelineDockWidget(QWidget *parent);

};

#endif // TIMELINEDOCKWIDGET_H
