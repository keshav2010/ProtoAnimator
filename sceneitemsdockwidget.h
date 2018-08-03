#ifndef SCENEITEMSDOCKWIDGET_H
#define SCENEITEMSDOCKWIDGET_H
#include<QDockWidget>
#include<QPushButton>
#include<QVBoxLayout>
#include<QFrame>
#include<QListView>
#include "framemanager.h"
class SceneItemsDockWidget:public QDockWidget
{
protected:
    QFrame *frameWidget;

    QVBoxLayout viewLayout;

    QListView sceneItemListView;
public:
    SceneItemsDockWidget(QWidget *parent);
    virtual ~SceneItemsDockWidget();
};
#endif // SCENEITEMSDOCKWIDGET_H
