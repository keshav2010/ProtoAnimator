#include "servicedockwidget.h"
#include "framemanager.h"
#include<QDebug>

ServiceDockWidget::ServiceDockWidget(QWidget *parent):
    QDockWidget(parent)
{
    ref_timelineModel=nullptr;
    frameWidget = new QFrame(this);
    buttonsLayout = new QVBoxLayout(frameWidget);
    setWindowTitle(tr("Animator Tools"));
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

    QObject::connect(this->btn_addFrame, &QPushButton::clicked,  FrameManager::getInstance(), &FrameManager::addFrameObject);
}

ServiceDockWidget::~ServiceDockWidget()
{
    qDebug()<<"(~ServiceDockWidget.cpp) : destructor";
    qDebug()<<"(~ServiceDockWidget.cpp) : btn_addFrame "<<(btn_addFrame!=nullptr);
    if(btn_addFrame != nullptr){
        delete btn_addFrame;
        btn_addFrame=nullptr;
    }
    qDebug()<<"(~ServiceDockWidget.cpp) : btn_applyLerp "<<(btn_applyLerp!=nullptr);
    if(btn_applyLerp != nullptr){
        delete btn_applyLerp;
        btn_applyLerp=nullptr;
    }
    qDebug()<<"(~ServiceDockWidget.cpp) : buttonsLayout "<<(buttonsLayout!=nullptr);
    if(buttonsLayout != nullptr)
        delete buttonsLayout;
    //qDebug()<<"(~ServiceDockWidget.cpp) : timelineModel "<<(timelineModel!=nullptr);
    /*
    if(timelineModel != nullptr){
        delete timelineModel;
        timelineModel = nullptr;
    }

    qDebug()<<"(~ServiceDockWidget.cpp) : frameWidget "<<(frameWidget!=nullptr);
    if(frameWidget != nullptr){
        delete frameWidget;
        frameWidget = nullptr;
    }
    */
    qDebug()<<"(~ServiceDockWidget.cpp) destructor call complete !";
}

void ServiceDockWidget::setTimelineModel(TimelineModel *model)
{
    ref_timelineModel = model;
}

QPushButton* ServiceDockWidget::getAddFrameButton()
{
    return btn_addFrame;
}

QPushButton* ServiceDockWidget::getApplyLerpButton()
{
    return btn_applyLerp;
}
