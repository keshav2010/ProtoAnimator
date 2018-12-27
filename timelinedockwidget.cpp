#include "timelinedockwidget.h"
#include "framemanager.h"
#include<QDebug>
TimelineDockWidget::TimelineDockWidget(QWidget *parent)
    :QDockWidget(parent)
{
    setWindowTitle(tr("Animation Tool"));

    mainWidget = new QWidget(this);

    animButtonGroup.setTitle(tr("Animation Control"));
    animButtonGroup.setLayout(&buttonsLayout);

    mainLayout = new QHBoxLayout();

    qDebug()<<"(TimelineDockWidget.cpp) calling TimelineView constructor";
    timelineView = new TimelineView();

    btn_deleteFrame.setText(tr("delete Frame(s)"));
    btn_pause.setText(tr("Pause"));
    btn_play.setText(tr("Play"));

    label_fps.setText(tr("Animation Speed"));
    sb_fps.setRange(1, 60);
    playrateLayout.addWidget(&label_fps);
    playrateLayout.addWidget(&sb_fps);
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
    qDebug()<<"so farso good";
    for(int i=0; i < indexList.size(); i++){
        QModelIndex index = indexList.at(i);
        if(index.column()==0)
            continue;
        qDebug()<<" > index : "<<index;
        frameKeyVector.push_back(this->timelineView->getModel()->modelIndexToFrameID(index));
    }
    FrameManager::getInstance()->deleteFrames(frameKeyVector);
}
