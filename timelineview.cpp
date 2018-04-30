#include "timelineview.h"
#include<QHeaderView>
TimelineView::TimelineView(QWidget *parent)
    :QTableView(parent)
{
    delegate = new TimelineDelegate(this);
    model = new TimelineModel();
    this->setItemDelegate(delegate);
    this->setModel(model);
    this->setPalette(QPalette(QColor(220,0,90)));
    this->horizontalHeader()->hide();
    this->verticalHeader()->hide();

}
