#include "sceneitemsdockwidget.h"
#include<QDebug>
#include<QItemDelegate>
ItemModel* SceneItemsDockWidget::getModel(){
    return (&listModel);
}

SceneItemsDockWidget::SceneItemsDockWidget(QWidget *parent)
{

    this->setFeatures(QDockWidget::DockWidgetMovable);
    setWindowTitle(tr("Frame Items"));

    this->frameWidget = new QFrame(this);
    this->frameWidget->setMinimumWidth(150);

    sceneItemTreeView.setModel(&listModel);
    viewLayout.addWidget(&sceneItemTreeView);

    frameWidget->setLayout(&viewLayout);
    setWidget(frameWidget);
    QObject::connect(FrameManager::getInstance(), &FrameManager::broadcastFrameItems,
                     this->getModel(), &ItemModel::updateDataSource);
}

SceneItemsDockWidget::~SceneItemsDockWidget()
{
}

//------------------------------------------------
ItemModel::ItemModel(QObject *parent):
    QAbstractItemModel(parent)
{
    ref_frameData=nullptr;
}

ItemModel::~ItemModel()
{
}

QModelIndex ItemModel::parent(const QModelIndex &child) const
{
    qDebug()<<"parent : parent index calculation requested";
    if(!child.isValid()){
        return QModelIndex();
    }
    AnimatableSpriteItem *childObject = static_cast<AnimatableSpriteItem*>( child.internalPointer());
    if(!childObject)
        return QModelIndex();
     qDebug()<<childObject->getName();
    AnimatableSpriteItem *parentObject = static_cast<AnimatableSpriteItem*>(childObject->parentItem());
    if( !parentObject)
        return QModelIndex();
    AnimatableSpriteItem *grandParentObject = static_cast<AnimatableSpriteItem*>( parentObject->parentItem());

    if(!grandParentObject)
        return QModelIndex();

    int row = grandParentObject->childItems().indexOf(parentObject);
    return createIndex(row, 0, parentObject);
}

//called whenever model/view need to create
//QModelIndex for child Item whose parent is
//"parent", and this child item need to be
//rendered at "row" relative to its parent's row
QModelIndex ItemModel::index(int row, int column, const QModelIndex &parent) const
{
    qDebug()<<"index : "<<row<<" "<<column<<" for "<<parent;
    if(ref_frameData == nullptr){
        qDebug()<<" frameData is null";
        return QModelIndex();
    }
    AnimatableSpriteItem *parentObject = nodeFromIndex(parent);
    //top level item (root item)
    if(parentObject==nullptr){
        qDebug()<<"no parent => root item";
        parentObject = (ref_frameData->begin() + row).value();
        return createIndex(row, column, parentObject);
    }
    AnimatableSpriteItem *childObject=static_cast<AnimatableSpriteItem*>(parentObject->childItems().at(row));
    if(!childObject)
        return QModelIndex();
    return createIndex(row, column, childObject);
}
QVariant ItemModel::data(const QModelIndex &index, int role) const
{
    qDebug()<<"data called";
    if( !index.isValid() || role != Qt::DisplayRole)
        return QVariant();
    return static_cast<AnimatableSpriteItem*>(index.internalPointer())->getName();
}
int ItemModel::rowCount(const QModelIndex &parent) const
{
    //for top level root items (with no parent)
    if(!parent.isValid()){
        if(ref_frameData==nullptr)
            return 0;
        //otherwise return items with no parent
        //TODO : this is an incomplete implementation, im returning
        //ref_frameData size() by assuming every time is a top-level item
        return ref_frameData->size();
    }
    int parentChildrenCount = static_cast<AnimatableSpriteItem*>(parent.internalPointer())->childItems().size();
    qDebug()<<parentChildrenCount<<" << ";
    return parentChildrenCount;

}
int ItemModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}


//if index belongs to model returns the associated object it refers
AnimatableSpriteItem *ItemModel::nodeFromIndex(const QModelIndex &index) const
{
    if(index.isValid()){
        return static_cast<AnimatableSpriteItem*> ( index.internalPointer() );
    }
    return  0;
}



void ItemModel::updateDataSource(QMap<QString, AnimatableSpriteItem* > *src)
{
    qDebug()<<"calld";
    beginResetModel();
    if(src != nullptr && ref_frameData != src){
        qDebug()<<"set";
        ref_frameData = src;
        //TODO : count items with no parent in optimal manner without performing sequential
        //scan for entire frameData every time.
    }
    endResetModel();
}

QMap<QString, AnimatableSpriteItem *> *ItemModel::getDataSource()
{
    return this->ref_frameData;
}

