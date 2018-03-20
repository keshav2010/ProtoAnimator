#include "timelinedockwidget.h"


TimelineDockWidget::TimelineDockWidget(QWidget *parent)
    :QDockWidget(parent)
{
    //sub frames
    timelineFrame = new QFrame(this);
    animationControlFrame = new QFrame(this);
    //main frame holds sub-frames
    mainFrame = new QFrame(this);
    framesHLayout = new QHBoxLayout(this);

    btn_runAnimation = new QPushButton("Play", this);
    btn_pauseAnimation = new QPushButton("Pause", this);
    btn_restartAnimation = new QPushButton("Replay", this);
    buttonsVLayout = new QVBoxLayout(this);

    animationControlFrame->setMaximumWidth(100);

    framesHLayout->addWidget(animationControlFrame);
    framesHLayout->addWidget(timelineFrame);
    //adding buttons to layout
    buttonsVLayout->addWidget(btn_runAnimation);
    buttonsVLayout->addWidget(btn_pauseAnimation);
    buttonsVLayout->addWidget(btn_restartAnimation);
    animationControlFrame->setLayout(buttonsVLayout);

    mainFrame->setLayout(framesHLayout);

    this->setWidget(mainFrame);
}
//SLOTS FXN
void TimelineDockWidget::runAnim(int startFromFrame)
{

}

void TimelineDockWidget::pauseAnim()
{

}

void TimelineDockWidget::restartAnim()
{

}
