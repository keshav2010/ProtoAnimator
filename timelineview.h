#ifndef TIMELINEVIEW_H
#define TIMELINEVIEW_H

#include <QObject>
#include<QAbstractItemView>
#include "timelinedelegate.h"
#include "timelinemodel.h"
#include<QListView>
class TimelineView : public QListView
{
    Q_OBJECT
public:
    TimelineView( QWidget * parent = 0);
private:
    TimelineDelegate *delegate;
    TimelineModel *model;
};

#endif // TIMELINEVIEW_H
