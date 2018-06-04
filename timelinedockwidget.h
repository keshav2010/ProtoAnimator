#ifndef TIMELINEDOCKWIDGET_H
#define TIMELINEDOCKWIDGET_H

#include<QDockWidget>
#include "timelineview.h"
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QPushButton>
#include<QFrame>
#include<QGroupBox>
#include<QWidget>
class TimelineDockWidget : public QDockWidget
{
public:
    TimelineDockWidget(QWidget *parent = nullptr);
    virtual ~TimelineDockWidget();
    TimelineView *getTimelineView() const;
private:
    QWidget *mainWidget;

    TimelineView *timelineView;

    QPushButton *btn_play;
    QPushButton *btn_pause;

    QGroupBox *buttonGroup;
    QVBoxLayout *buttonsLayout;
    QHBoxLayout *mainLayout;

};

#endif // TIMELINEDOCKWIDGET_H
