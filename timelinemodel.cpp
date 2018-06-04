#include "timelinemodel.h"
#include"framemanager.h"
TimelineModel::TimelineModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    qDebug()<<"(TimelineModel.cpp) constructor";
}

TimelineModel::~TimelineModel()
{
    qDebug()<<"(~TimelineModel.cpp) : destructor";
    qDeleteAll(dataSource.begin(), dataSource.end());
    dataSource.clear();
}
int TimelineModel::rowCount(const QModelIndex &parent) const
{
    return 1;
}

int TimelineModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}

QVariant TimelineModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || role != Qt::DisplayRole)
        return QVariant();
    return index.row();
}
