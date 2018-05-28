#ifndef TIMELINEVIEW_H
#define TIMELINEVIEW_H

#include <QObject>
#include<QAbstractItemView>
#include "timelinedelegate.h"
#include "timelinemodel.h"
#include<QTableView>
class TimelineView : public QTableView
{
    Q_OBJECT
public:
    TimelineView( QWidget * parent = 0);
    TimelineModel* getModel() const;

protected:
    int sizeHintForColumn(int column) const;
private:
    TimelineDelegate *delegate;
    TimelineModel *model;
};

#endif // TIMELINEVIEW_H
