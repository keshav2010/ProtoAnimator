#include "timelinemodel.h"
#include"framemanager.h"
TimelineModel::TimelineModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    qDebug()<<"(TimelineModel.cpp) constructor";

    //this line is causing issue (infinite loop)
    FrameManager *ins = FrameManager::getInstance();

    QMap<int, Frame*> *dataSource = ins->getPointerToFrameBank();

    setupDataSource(dataSource);
    qDebug()<<"(TimelineModel.cpp) constructor call complete";
}


//helper method
void TimelineModel::setupDataSource(QMap<int, Frame *> *source)
{
    qDebug()<<"(TimelineModel.cpp) > (setupDataSource() fxn) begins";
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
