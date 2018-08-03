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
    TimelineView( QWidget * parent = nullptr);
    ~TimelineView();
    TimelineModel* getModel() const;

public slots:

protected:
    int sizeHintForColumn(int column) const;
    void selectionChanged(const QItemSelection &selected, const QItemSelection &deselected) override;
private:
    TimelineDelegate *timelineDelegate;
    TimelineModel *timelineModel;
};

#endif // TIMELINEVIEW_H
