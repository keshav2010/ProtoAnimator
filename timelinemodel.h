#ifndef TIMELINEMODEL_H
#define TIMELINEMODEL_H

#include <QObject>
#include<QAbstractTableModel>
#include "frame.h"

class TimelineModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    TimelineModel(QObject *parent = nullptr);
    ~TimelineModel();
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
private:
    void setupDataSource(QMap<int, Frame*> *source);
    QMap<int, Frame*> *dataSource;

};

#endif // TIMELINEMODEL_H
