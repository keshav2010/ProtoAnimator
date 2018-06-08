#include "timelineview.h"
#include<QHeaderView>
#include<QDebug>
TimelineView::TimelineView(QWidget *parent)
    :QTableView(parent)
{
    qDebug()<<"(TimelineView.cpp) constructor";
    timelineDelegate = new TimelineDelegate(this);
    timelineModel = new TimelineModel(this);
    //this is never reached, problem found in TimelineModel() constructor

    this->setItemDelegate(timelineDelegate);
    this->setModel(timelineModel);

    this->horizontalHeader()->setMinimumSectionSize(1);
    this->verticalHeader()->setMinimumSectionSize(1);

    this->horizontalHeader()->hide();
    this->verticalHeader()->hide();
}

TimelineView::~TimelineView()
{
    qDebug()<<"(~TimelineView.cpp) : destructor";
    if(timelineDelegate != nullptr)
    {
        delete timelineDelegate;
        timelineModel = nullptr;
    }
    if(timelineModel != nullptr)
    {
        delete timelineModel;
        timelineModel = nullptr;
    }
    qDebug()<<"(~TimelineView.cpp): destructor call end";
}

TimelineModel *TimelineView::getModel() const
{
    return timelineModel;
}

int TimelineView::sizeHintForColumn(int column) const
{
    return 10;
}
