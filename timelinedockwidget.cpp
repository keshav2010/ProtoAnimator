#include "timelinedockwidget.h"
#include "framemanager.h"
#include<QDebug>
TimelineDockWidget::TimelineDockWidget(QWidget *parent)
    :QDockWidget(parent)
{
    qDebug()<<"(TimelineDockWidget.cpp) constructor";
    setWindowTitle(tr("Animation Tool"));
    animButtonGroup = new QGroupBox(tr("Animation Control"), this);
    mainWidget = new QWidget(this);
    buttonsLayout = new QVBoxLayout(animButtonGroup);//implicit call to animButtonGroup->setLayout(buttonsLayout);
    mainLayout = new QHBoxLayout();

    qDebug()<<"(TimelineDockWidget.cpp) calling TimelineView constructor";
    timelineView = new TimelineView();
    //DEBUG LOG : this is never reached

    btn_deleteFrame = new QPushButton(tr("delete Frame(s)"));
    btn_pause = new QPushButton(tr("pause"));
    btn_play = new QPushButton(tr("Play"));

    //add buttons to layout, further add layout to buttonGroup
    buttonsLayout->addWidget(btn_play);
    buttonsLayout->addWidget(btn_pause);
    buttonsLayout->addWidget(btn_deleteFrame);
   //animButtonGroup->setLayout(buttonsLayout);

    //add animButtonGroup and timelineView to mainLayout
    mainLayout->addWidget(animButtonGroup);
    mainLayout->addWidget(timelineView);

    setFeatures(DockWidgetMovable);

    //set mainLayout for mainWidget
    mainWidget->setLayout(mainLayout);
    //set dockwidget as parent
    setWidget(mainWidget);

    QObject::connect(FrameManager::getInstance(), &FrameManager::frameBankChanged,
                     timelineView->getModel(), &TimelineModel::updateDataSource);
    QObject::connect(btn_deleteFrame, &QPushButton::clicked,
                     this, &TimelineDockWidget::removeSelectedFrames);
}

TimelineDockWidget::~TimelineDockWidget()
{
    //order of deletion matters (parent-child relationship)

    qDebug()<<"(~TimelineDockWidget.cpp) Destructor";
    qDebug()<<"(~TimelineDockWidget.cpp) btn_deleteFrame"<<(btn_deleteFrame!=nullptr);
    if(btn_deleteFrame!=nullptr){
        delete btn_deleteFrame;
        btn_deleteFrame=nullptr;
    }
    qDebug()<<"(~TimelineDockWidget.cpp) btn_play"<<(btn_play!=nullptr);
    if(btn_play!=nullptr){
        delete btn_play;
        btn_play=nullptr;
    }
    qDebug()<<"(~TimelineDockWidget.cpp) btn_pause"<<(btn_pause!=nullptr);
    if(btn_pause != nullptr){
        delete btn_pause;
        btn_pause=nullptr;
    }
    qDebug()<<"(~TimelineDockWidget.cpp) : buttonsLayout"<<(buttonsLayout!=nullptr);
    if(buttonsLayout != nullptr)
    {
        delete buttonsLayout;
        buttonsLayout = nullptr;
    }
    qDebug()<<"(~TimelineDockWidget.cpp) : buttonGroup"<<(animButtonGroup != nullptr);
    if(animButtonGroup != nullptr){
        delete animButtonGroup;
        animButtonGroup = nullptr;
    }
    qDebug()<<"(~TimelineDockWidget.cpp) timelineView "<<(timelineView != nullptr);
    if(timelineView != nullptr){
        delete timelineView;
        timelineView = nullptr;
    }
    qDebug()<<"(~TimelineDockWidget.cpp) : mainLayout "<<(mainLayout != nullptr);
    if(mainLayout != nullptr)
    {
        delete mainLayout;
        mainLayout = nullptr;
    }
    /*
    qDebug()<<"(~TimelineDockWidget.cpp) mainWidget "<<(mainWidget != nullptr);
    if(mainWidget != nullptr){
        delete mainWidget;
        mainWidget = nullptr;
    }
    */
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
