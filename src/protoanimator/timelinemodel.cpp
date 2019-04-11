#include "timelinemodel.h"
#include"framemanager.h"
TimelineModel::TimelineModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    qDebug()<<"(TimelineModel.cpp) constructor";
    ref_dataSource = nullptr;
}

TimelineModel::~TimelineModel()
{
    qDebug()<<"(~TimelineModel.cpp) : destructor";
    if(ref_dataSource == nullptr){
        return;
    }

    /*
     * Deletes all the items in the range [begin, end)
     * using the C++ delete operator.
     * The item type must be a pointer type
     */
    qDeleteAll(ref_dataSource->begin(), ref_dataSource->end());
    ref_dataSource->clear();
    ref_dataSource = nullptr;
}
int TimelineModel::rowCount(const QModelIndex &parent) const
{
    if(ref_dataSource == nullptr)
        return 0;
    return 1;
}

int TimelineModel::columnCount(const QModelIndex &parent) const
{
    if(ref_dataSource == nullptr)
     return 0;
    return ref_dataSource->size();
}

QVariant TimelineModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || role != Qt::DisplayRole)
        return QVariant();
    return index.row();
}

int TimelineModel::modelIndexToFrameID(QModelIndex ind)
{
    int col = ind.column();
    int frameKey = (ref_dataSource->begin()+col).key();
    return frameKey;
}

void TimelineModel::updateDataSource(QMap<int, Frame *> *src)
{
    beginResetModel();
    if(ref_dataSource != src){
        ref_dataSource = src;
    }
    endResetModel();
}

QMap<int, Frame *> *TimelineModel::getDataSource()
{
    return this->ref_dataSource;
}

int TimelineModel::getFramesCount() const
{
    return ref_dataSource->size();
}
