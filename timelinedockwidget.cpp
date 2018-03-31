#include "timelinedockwidget.h"
#include "framemanager.h"

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

    spinbox_frameSelector = new QSpinBox(this);
    spinbox_frameSelector->setRange(0, 0);
    spinboxHLayout = new QHBoxLayout(this);
    spinboxHLayout->addWidget(spinbox_frameSelector);

    animationControlFrame->setMaximumWidth(100);
    framesHLayout->addWidget(animationControlFrame);
    framesHLayout->addWidget(timelineFrame);
    //adding buttons to layout
    buttonsVLayout->addWidget(btn_runAnimation);
    buttonsVLayout->addWidget(btn_pauseAnimation);
    buttonsVLayout->addWidget(btn_restartAnimation);

    animationControlFrame->setLayout(buttonsVLayout);

    framesHLayout->addLayout(spinboxHLayout);
    mainFrame->setLayout(framesHLayout);

    this->setWidget(mainFrame);

    //if user changes value of spinbox, ask frameManager to switch to respective frame
    //NOTE : Using old signal-slot syntax to avoid messy code
    QObject::connect(spinbox_frameSelector, SIGNAL(valueChanged(int)),
                     FrameManager::getInstance(),
                     SLOT(switchToFrame(int)));

    //if any new frame is added into frameManager, ask timelinedockwidget to update its
    //spinbox_frameSelector's maximum range
    QObject::connect(FrameManager::getInstance(), &FrameManager::signalTimelineWidget,
                     this, &TimelineDockWidget::updateFrameSelectorRange);
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

//slot fxn
void TimelineDockWidget::updateFrameSelectorRange(int upperBoundOfRange)
{
    spinbox_frameSelector->setRange(0, upperBoundOfRange-1);
    spinbox_frameSelector->setValue(upperBoundOfRange-1);
}
