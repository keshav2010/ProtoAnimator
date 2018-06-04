#include "timelinedockwidget.h"
#include<QDebug>
TimelineDockWidget::TimelineDockWidget(QWidget *parent)
    :QDockWidget(parent)
{
    qDebug()<<"(TimelineDockWidget.cpp) constructor";
    buttonGroup = new QGroupBox(tr("Animation Control"), this);
    mainWidget = new QWidget(this);
    buttonsLayout = new QVBoxLayout(buttonGroup);//implicit call to buttonGroup->setLayout(buttonsLayout);
    mainLayout = new QHBoxLayout();

    qDebug()<<"(TimelineDockWidget.cpp) calling TimelineView constructor";
    timelineView = new TimelineView();
    //DEBUG LOG : this is never reached

    btn_pause = new QPushButton(tr("pause"));
    btn_play = new QPushButton(tr("Play"));

    //add buttons to layout, further add layout to buttonGroup
    buttonsLayout->addWidget(btn_play);
    buttonsLayout->addWidget(btn_pause);
   //buttonGroup->setLayout(buttonsLayout);

    //add buttonGroup and timelineView to mainLayout
    mainLayout->addWidget(buttonGroup);
    mainLayout->addWidget(timelineView);

    setFeatures(DockWidgetMovable);

    //set mainLayout for mainWidget
    mainWidget->setLayout(mainLayout);

    //set dockwidget as parent
    setWidget(mainWidget);

}

TimelineDockWidget::~TimelineDockWidget()
{
    //order of deletion matters (parent-child relationship)

    qDebug()<<"(~TimelineDockWidget.cpp) Destructor";
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
    qDebug()<<"(~TimelineDockWidget.cpp) : buttonGroup"<<(buttonGroup != nullptr);
    if(buttonGroup != nullptr){
        delete buttonGroup;
        buttonGroup = nullptr;
    }
    qDebug()<<"(~TimelineDockWidget.cpp) timelineView "<<(timelineView != nullptr);
    if(timelineView != nullptr){
        delete timelineView;
        timelineView = nullptr;
    }
    qDebug()<<"(~TimelineDockWidget.cpp) : mainLayout "<<(mainLayout!=nullptr);
    if(mainLayout != nullptr)
    {
        delete mainLayout;
        mainLayout = nullptr;
    }
    qDebug()<<"(~TimelineDockWidget.cpp) mainWidget "<<(mainWidget != nullptr);
    if(mainWidget != nullptr){
        delete mainWidget;
        mainWidget = nullptr;
    }
}
TimelineView *TimelineDockWidget::getTimelineView() const
{
    return timelineView;
}
