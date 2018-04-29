#include "timelineview.h"
TimelineView::TimelineView(QWidget *parent)
    :QListView(parent)
{
    delegate = new TimelineDelegate(this);
    model = new TimelineModel();

    this->setItemDelegate(delegate);
    this->setModel(model);
}
