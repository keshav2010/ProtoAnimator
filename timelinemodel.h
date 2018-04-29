#ifndef TIMELINEMODEL_H
#define TIMELINEMODEL_H

#include <QObject>
#include<QAbstractListModel>
#include "frame.h"

class TimelineModel : public QAbstractListModel
{
    Q_OBJECT
public:
    TimelineModel(QObject *parent = Q_NULLPTR);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
private:
    void setupDataSource(QMap<int, Frame*> *source);
    QMap<int, Frame*> *dataSource;

};

#endif // TIMELINEMODEL_H
