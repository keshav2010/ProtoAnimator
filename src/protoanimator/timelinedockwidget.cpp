#include "timelinedockwidget.h"
#include "framemanager.h"
#include "frameseditor.h"
#include "animationdriver.h"
#include<QDebug>
TimelineDockWidget::TimelineDockWidget(QWidget *parent)
    :QDockWidget(parent)
{
    setWindowTitle(tr("Animation Tool"));

    mainWidget = new QWidget(this);

    animButtonGroup.setTitle(tr("Animation Control"));
    animButtonGroup.setLayout(&buttonsLayout);

    mainLayout = new QHBoxLayout();

    //qDebug()<<"(TimelineDockWidget.cpp) calling TimelineView constructor";
    timelineView = new TimelineView();

    btn_deleteFrame.setText(tr("delete Frame(s)"));
    btn_pause.setText(tr("Pause"));
    btn_play.setText(tr("Play"));

    label_fps.setText(tr("FPS "));
    sb_fps.setRange(1, 60);
    playrateLayout.addWidget(&label_fps);
    playrateLayout.addWidget(&sb_fps);

    label_loop.setText(tr("Loop "));
    playrateLayout.addWidget(&label_loop);
    playrateLayout.addWidget(&cb_loop);

    controlGroup.setTitle(tr("Playrate Setting"));
    controlGroup.setLayout(&playrateLayout);


    //add buttons to layout, further add layout to buttonGroup
    buttonsLayout.addWidget(&btn_play);
    buttonsLayout.addWidget(&btn_pause);
    buttonsLayout.addWidget(&btn_deleteFrame);

    groupLayout.addWidget(&animButtonGroup);
    groupLayout.addWidget(&controlGroup);
    mainGroup.setLayout(&groupLayout);

    //add animButtonGroup and timelineView to mainLayout
    mainLayout->addWidget(&mainGroup);
    mainLayout->addWidget(timelineView);


    setFeatures(DockWidgetMovable);

    //set mainLayout for mainWidget
    mainWidget->setLayout(mainLayout);
    //set dockwidget as parent
    setWidget(mainWidget);

    QObject::connect(FrameManager::getInstance(), &FrameManager::frameBankChanged,
                     timelineView->getModel(), &TimelineModel::updateDataSource);
    QObject::connect(&btn_deleteFrame, &QPushButton::clicked,
                     this, &TimelineDockWidget::removeSelectedFrames);
    QObject::connect(&btn_play, &QPushButton::clicked,
                     FramesEditor::getInstance()->getAnimationDriver(), &AnimationDriver::playAnim);
    QObject::connect(&btn_pause, &QPushButton::clicked,
                     FramesEditor::getInstance()->getAnimationDriver(), &AnimationDriver::stopAnim);

    //refer to this link : https://stackoverflow.com/questions/16794695/connecting-overloaded-signals-and-slots-in-qt-5
    //as to why old-style QObject::connect(..) syntax is used below
    QObject::connect(&sb_fps, SIGNAL(valueChanged(int)),
                     FramesEditor::getInstance()->getAnimationDriver(), SLOT(setFPS(int)));
    QObject::connect(&cb_loop, SIGNAL(clicked(bool)),
                     FramesEditor::getInstance()->getAnimationDriver(), SLOT(setLoop(bool)));
}

TimelineDockWidget::~TimelineDockWidget()
{
    if(timelineView != nullptr){
        delete timelineView;
        timelineView = nullptr;
    }
    if(mainLayout != nullptr)
    {
        delete mainLayout;
        mainLayout = nullptr;
    }
}
TimelineView *TimelineDockWidget::getTimelineView() const
{
    return timelineView;
}

//iterator getting invalidated, ERROR HERE
void TimelineDockWidget::removeSelectedFrames()
{
    QModelIndexList indexList = this->timelineView->selectionModel()->selectedIndexes();
    QVector<int> frameKeyVector;
    for(int i=0; i < indexList.size(); i++){
        QModelIndex index = indexList.at(i);
        if(index.column()==0)
            continue;
        //qDebug()<<" > index : "<<index;
        frameKeyVector.push_back(this->timelineView->getModel()->modelIndexToFrameID(index));
    }
    FrameManager::getInstance()->deleteFrames(frameKeyVector);
}
