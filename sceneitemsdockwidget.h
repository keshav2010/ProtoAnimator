#ifndef SCENEITEMSDOCKWIDGET_H
#define SCENEITEMSDOCKWIDGET_H
#include<QDockWidget>
#include<QPushButton>
#include<QVBoxLayout>
#include<QFrame>
#include<QListView>
class SceneItemsDockWidget:public QDockWidget
{
protected:
    QVBoxLayout viewLayout;
    QFrame *frameWidget;
    QListView sceneItemListView;
public:
    SceneItemsDockWidget(QWidget *parent);
    virtual ~SceneItemsDockWidget();
};
#endif // SCENEITEMSDOCKWIDGET_H
