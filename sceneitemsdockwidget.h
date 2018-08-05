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
private:
    QMap<QString, AnimatableSpriteItem*> *ref_frameData;
public:
    ItemListModel(QObject *parent=nullptr);
    ~ItemListModel();

    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QMap<QString, AnimatableSpriteItem*> *getDataSource();
public slots:
    void updateDataSource(QMap<QString, AnimatableSpriteItem*> *src=nullptr);

};

class SceneItemsDockWidget:public QDockWidget
{
protected:
    QFrame *frameWidget;
    QVBoxLayout viewLayout;
    QListView sceneItemListView;
    ItemListModel listModel;
public:
    ItemListModel* getModel();
    SceneItemsDockWidget(QWidget *parent);
    ~SceneItemsDockWidget();
};


#endif // SCENEITEMSDOCKWIDGET_H
