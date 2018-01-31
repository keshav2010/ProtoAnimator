#ifndef TIMELINEDOCKWIDGET_H
#define TIMELINEDOCKWIDGET_H

#include<QFrame>
#include<QHBoxLayout>
#include<QDockWidget>
class TimelineDockWidget :  public QDockWidget
{
protected:
    QFrame *timelineFrame;

public:
    TimelineDockWidget(QWidget *parent);

};

#endif // TIMELINEDOCKWIDGET_H
