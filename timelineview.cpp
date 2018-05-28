#include "timelineview.h"
#include<QHeaderView>
#include<QDebug>
TimelineView::TimelineView(QWidget *parent)
    :QTableView(parent)
{
    qDebug()<<"(TimelineView.cpp) constructor";
    delegate = new TimelineDelegate(this);
    model = new TimelineModel();
    //this is never reached, problem found in TimelineModel() constructor

    this->setItemDelegate(delegate);
    this->setModel(model);

    this->horizontalHeader()->setMinimumSectionSize(1);
    this->verticalHeader()->setMinimumSectionSize(1);

    this->horizontalHeader()->hide();
    this->verticalHeader()->hide();

}

TimelineModel *TimelineView::getModel() const
{
    return model;
}

int TimelineView::sizeHintForColumn(int column) const
{
    return 10;
}
