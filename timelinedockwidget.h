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
#include<QSpinBox>
#include<QLabel>
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
        QHBoxLayout *mainLayout;
            QGroupBox mainGroup;
                QVBoxLayout groupLayout;
                    QGroupBox animButtonGroup;
                        QVBoxLayout buttonsLayout;
                            QPushButton btn_play, btn_pause, btn_deleteFrame;

                    QGroupBox controlGroup;
                        QHBoxLayout playrateLayout;
                            QSpinBox sb_fps;
                            QLabel label_fps;

            TimelineView *timelineView;

};

#endif // TIMELINEDOCKWIDGET_H
