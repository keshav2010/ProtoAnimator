#ifndef SERVICEDOCKWIDGET_H
#define SERVICEDOCKWIDGET_H
#include<QDockWidget>
#include<QPushButton>
#include<QVBoxLayout>
#include<QFrame>
/*
 * ServiceDockWidget consists of buttons, labels and other interactable
 * widgets that user can interact with, and they might provide a mean
 * to directly affect content of a animation-frame
*/
class ServiceDockWidget : public QDockWidget
{
protected:
    QPushButton *btn_addFrame;
    QPushButton *btn_applyLerp;
    QVBoxLayout *buttonsLayout;

    QFrame *frameWidget;

public:
    ServiceDockWidget(QWidget *parent);

    //helper fxns
    QPushButton* getAddFrameButton();
    QPushButton* getApplyLerpButton();

};

#endif // SERVICEDOCKWIDGET_H