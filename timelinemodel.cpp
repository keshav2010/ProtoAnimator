#include "timelinemodel.h"
#include"framemanager.h"
TimelineModel::TimelineModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    setupDataSource(FrameManager::getInstance()->getPointerToFrameBank());
    //for testing only
    this->dataSource->insert(2, new Frame(0));
    this->dataSource->insert(3, new Frame(0));
    this->dataSource->insert(4, new Frame(0));
}

void TimelineModel::setupDataSource(QMap<int, Frame *> *source)
{
    beginResetModel();
    this->dataSource = source;
    endResetModel();
}

int TimelineModel::rowCount(const QModelIndex &parent) const
{
    return 1;
}

int TimelineModel::columnCount(const QModelIndex &parent) const
{
    return dataSource->size();
}

QVariant TimelineModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || role != Qt::DisplayRole)
        return QVariant();
    return index.row();
}
