#include "sceneitemsdockwidget.h"
#include<QDebug>
#include<QItemDelegate>
ItemListModel* SceneItemsDockWidget::getModel(){
    return (&listModel);
}

SceneItemsDockWidget::SceneItemsDockWidget(QWidget *parent)
{

    this->setFeatures(QDockWidget::DockWidgetMovable);
    setWindowTitle(tr("Frame Items"));

    this->frameWidget = new QFrame(this);
    this->frameWidget->setMinimumWidth(150);

    sceneItemListView.setModel(&listModel);
    viewLayout.addWidget(&sceneItemListView);

    frameWidget->setLayout(&viewLayout);
    setWidget(frameWidget);
    QObject::connect(FrameManager::getInstance(), &FrameManager::broadcastFrameItems,
                     this->getModel(), &ItemListModel::updateDataSource);

}

SceneItemsDockWidget::~SceneItemsDockWidget()
{
}

//------------------------------------------------

ItemListModel::ItemListModel(QObject *parent):
    QAbstractListModel(parent)
{
    ref_frameData=nullptr;
}

ItemListModel::~ItemListModel()
{

}

int ItemListModel::rowCount(const QModelIndex &parent) const
{
    if(ref_frameData == nullptr)
        return 0;
    return ref_frameData->size();
}

QVariant ItemListModel::data(const QModelIndex &index, int role) const
{
    if( !index.isValid() || role != Qt::DisplayRole)
        return QVariant();
    return (ref_frameData->begin()+index.row()).key();
}

void ItemListModel::updateDataSource(QMap<QString, AnimatableSpriteItem* > *src)
{
    qDebug()<<"updating data source for itemListModel";
    beginResetModel();
    if(src != nullptr && ref_frameData != src){
        qDebug()<<"updated";
        ref_frameData = src;
    }
    endResetModel();
}

QMap<QString, AnimatableSpriteItem *> *ItemListModel::getDataSource()
{
    return this->ref_frameData;
}

