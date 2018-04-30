#include "timelinedockwidget.h"
#include<QDebug>
TimelineDockWidget::TimelineDockWidget(QWidget *parent)
    :QDockWidget(parent)
{
    mainWidget = new QWidget(this);
    buttonsLayout = new QVBoxLayout(buttonGroup);//implicit call to buttonGroup->setLayout(buttonsLayout);
    mainLayout = new QHBoxLayout(this);//implicit call to setLayout(timelineLayout);

    timelineView = new TimelineView();
    buttonGroup = new QGroupBox(tr("Animation Control"), this);

    btn_pause = new QPushButton(tr("pause"));
    btn_play = new QPushButton(tr("Play"));

    //add buttons to layout, further add layout to buttonGroup
    buttonsLayout->addWidget(btn_play);
    buttonsLayout->addWidget(btn_pause);
    buttonGroup->setLayout(buttonsLayout);

    //add buttonGroup and timelineView to mainLayout
    mainLayout->addWidget(buttonGroup);
    mainLayout->addWidget(timelineView);

    setFeatures(DockWidgetMovable);

    //set mainLayout for mainWidget
    mainWidget->setLayout(mainLayout);

    //set dockwidget as parent
    setWidget(mainWidget);

}
