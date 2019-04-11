#ifndef SCENEITEMSDOCKWIDGET_H
#define SCENEITEMSDOCKWIDGET_H
#include<QDockWidget>
#include<QPushButton>
#include<QVBoxLayout>
#include<QFrame>
#include<QTreeView>
#include<QMap>
#include "framemanager.h"

class ItemModel : public QAbstractItemModel
{
private:
    QMap<QString, AnimatableSpriteItem*> *ref_frameData;
    unsigned int rootLevelItems;

public:
    ItemModel(QObject *parent=nullptr);
    ~ItemModel();

    QModelIndex parent(const QModelIndex &child) const;
    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;

    //helper method
    AnimatableSpriteItem* nodeFromIndex(const QModelIndex &index) const;
    QMap<QString, AnimatableSpriteItem*> *getDataSource();

public slots:
    void updateDataSource(QMap<QString, AnimatableSpriteItem*> *src=nullptr);
};

class SceneItemsDockWidget:public QDockWidget
{
protected:
    QFrame *frameWidget;
    QVBoxLayout viewLayout;
    QTreeView sceneItemTreeView;
    ItemModel listModel;
public:
    ItemModel* getModel();
    SceneItemsDockWidget(QWidget *parent);
    ~SceneItemsDockWidget();
};


#endif // SCENEITEMSDOCKWIDGET_H
