#ifndef SERVICEDOCKWIDGET_H
#define SERVICEDOCKWIDGET_H
#include<QDockWidget>
#include<QPushButton>
#include<QVBoxLayout>
#include<QFrame>
#include "timelinemodel.h"
/*
 * ServiceDockWidget consists of buttons, labels and other interactable
 * widgets that user can interact with, and they might provide a mean
 * to directly affect content of a animation-frame
*/
class ServiceDockWidget : public QDockWidget
{
    Q_OBJECT

protected:
    QPushButton *btn_addFrame;
    QPushButton *btn_applyLerp;
    QVBoxLayout *buttonsLayout;//to store buttons in vertically stacked fashion

    TimelineModel *ref_timelineModel;

    QFrame *frameWidget;

public:
    ServiceDockWidget(QWidget *parent);
    ~ServiceDockWidget();

    void setTimelineModel(TimelineModel *model);
    //helper fxns
    QPushButton* getAddFrameButton();
    QPushButton* getApplyLerpButton();

};

#endif // SERVICEDOCKWIDGET_H
