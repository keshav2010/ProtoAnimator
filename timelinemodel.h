#ifndef TIMELINEMODEL_H
#define TIMELINEMODEL_H

#include <QObject>
#include<QAbstractListModel>

class TimelineModel : public QAbstractListModel
{
    Q_OBJECT
public:
    TimelineModel();
};

#endif // TIMELINEMODEL_H
