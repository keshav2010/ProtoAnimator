#ifndef TIMELINEDOCKWIDGET_H
#define TIMELINEDOCKWIDGET_H

#include<QDockWidget>
#include "timelineview.h"
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QPushButton>
#include<QFrame>
class TimelineDockWidget : public QDockWidget
{
public:
    TimelineDockWidget(QWidget *parent = 0);
private:
    TimelineView timelineView;

    QPushButton btn_play;
    QPushButton btn_pause;

    QVBoxLayout buttonsLayout;
    QVBoxLayout timelineLayout;

    QHBoxLayout widgetLayout;

};

#endif // TIMELINEDOCKWIDGET_H
