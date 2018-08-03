#include "sceneitemsdockwidget.h"
#include<QDebug>
SceneItemsDockWidget::SceneItemsDockWidget(QWidget *parent)
{
    this->setFeatures(QDockWidget::DockWidgetMovable);
    setWindowTitle(tr("Frame Items"));
    this->frameWidget = new QFrame(this);
    this->frameWidget->setMinimumWidth(150);
    viewLayout.addWidget(&sceneItemListView);
    frameWidget->setLayout(&viewLayout);
    setWidget(frameWidget);
}

SceneItemsDockWidget::~SceneItemsDockWidget()
{
}
