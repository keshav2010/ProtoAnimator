#include "timelinedockwidget.h"

TimelineDockWidget::TimelineDockWidget(QWidget *parent)
    :QDockWidget(parent)
{
    btn_play.setText(QString("Play"));
    btn_pause.setText(QString("Pause"));
    timelineView.setParent(this);
    timelineView.show();
    timelineLayout.addWidget(&timelineView);
    buttonsLayout.addWidget(&btn_play);
    buttonsLayout.addWidget(&btn_pause);

    widgetLayout.addLayout(&buttonsLayout);
    widgetLayout.addLayout(&timelineLayout);
    setFeatures(DockWidgetMovable);
    setFeatures(DockWidgetVerticalTitleBar);
    setLayout(&widgetLayout);

}
