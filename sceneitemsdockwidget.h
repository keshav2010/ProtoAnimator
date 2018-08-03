#ifndef SCENEITEMSDOCKWIDGET_H
#define SCENEITEMSDOCKWIDGET_H
#include<QDockWidget>
#include<QPushButton>
#include<QVBoxLayout>
#include<QFrame>
#include<QListView>
#include<QMap>
#include "framemanager.h"

class ItemListModel : public QAbstractListModel
{
public:
    ItemListModel(QObject *parent=nullptr);
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    ~ItemListModel();
};

class SceneItemsDockWidget:public QDockWidget
{
protected:
    QFrame *frameWidget;
    QVBoxLayout viewLayout;
    QListView sceneItemListView;
    ItemListModel listModel;
public:
    SceneItemsDockWidget(QWidget *parent);
    ~SceneItemsDockWidget();
};


#endif // SCENEITEMSDOCKWIDGET_H
