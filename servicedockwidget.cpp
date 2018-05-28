#include "servicedockwidget.h"


ServiceDockWidget::ServiceDockWidget(QWidget *parent):
    QDockWidget(parent)
{
    timelineModel=0;
    frameWidget = new QFrame(this);
    buttonsLayout = new QVBoxLayout(frameWidget);
    setWindowTitle("Animator Tools");
    btn_addFrame = new QPushButton("Add Frame");
    btn_applyLerp = new QPushButton("Autofill Frames");


    setFeatures(DockWidgetMovable);

    btn_addFrame->setToolTip(QString("Inserts a new frame which is clone of last frame"));
    btn_addFrame->setMinimumSize(QSize(100,50));

    btn_applyLerp->setToolTip(QString("Applies linear interpolation between previous and current frame"));
    btn_applyLerp->setMinimumSize(QSize(100,50));

    buttonsLayout->addWidget(btn_addFrame);
    buttonsLayout->addWidget(btn_applyLerp);

    frameWidget->setLayout(buttonsLayout);
    this->setWidget(frameWidget);
}

void ServiceDockWidget::setTimelineModel(TimelineModel *model)
{
    timelineModel = model;
}

QPushButton* ServiceDockWidget::getAddFrameButton()
{
    return btn_addFrame;
}

QPushButton* ServiceDockWidget::getApplyLerpButton()
{
    return btn_applyLerp;
}
