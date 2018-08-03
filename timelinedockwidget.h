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
    ~TimelineDockWidget();
    TimelineView *getTimelineView() const;

public slots:
    void removeSelectedFrames();

private:
    QWidget *mainWidget;

    TimelineView *timelineView;

    QPushButton *btn_play, *btn_pause;
    QGroupBox *animButtonGroup;
    QPushButton *btn_deleteFrame;
    QVBoxLayout *buttonsLayout;
    QHBoxLayout *mainLayout;

};

#endif // TIMELINEDOCKWIDGET_H
