#include "servicedockwidget.h"


ServiceDockWidget::ServiceDockWidget(QWidget *parent):
    QDockWidget(parent),
    buttonsLayout(new QVBoxLayout(this))
{
    frameWidget = new QFrame(this);

    setWindowTitle("Animator Tools");
    btn_addFrame = new QPushButton("Add Frame", this);
    btn_applyLerp = new QPushButton("Autofill Frames", this);


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

QPushButton* ServiceDockWidget::getAddFrameButton()
{
    return btn_addFrame;
}

QPushButton* ServiceDockWidget::getApplyLerpButton()
{
    return btn_applyLerp;
}
