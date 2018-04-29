#include "timelinemodel.h"
#include"framemanager.h"
TimelineModel::TimelineModel(QObject *parent) :
    QAbstractListModel(parent)
{
    setupDataSource(FrameManager::getInstance()->getPointerToFrameBank());
}

void TimelineModel::setupDataSource(QMap<int, Frame *> *source)
{
    beginResetModel();
    this->dataSource = source;
    endResetModel();
}

int TimelineModel::rowCount(const QModelIndex &parent) const
{
    return dataSource->size();
}

QVariant TimelineModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || role != Qt::DisplayRole)
        return QVariant();
    return index.row();
}
