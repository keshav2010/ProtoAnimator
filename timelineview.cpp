#include "timelineview.h"
#include<QHeaderView>
#include<QDebug>
#include "frameseditor.h"
TimelineView::TimelineView(QWidget *parent)
    :QTableView(parent)
{
    qDebug()<<"(TimelineView.cpp) constructor";
    timelineDelegate = new TimelineDelegate(this);
    timelineModel = new TimelineModel(this);
    //this is never reached, problem found in TimelineModel() constructor

    this->setItemDelegate(timelineDelegate);
    this->setModel(timelineModel);
    this->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    this->horizontalHeader()->show();
    this->horizontalHeader()->setEnabled(false);
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

void TimelineView::selectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    if(selected.empty())
        return;

    QModelIndex ind = selected.indexes().at(0);
    int selectedFrameKey = timelineModel->modelIndexToFrameID(ind);
    //updates the currentactiveframe as well as renders it on display
    FrameManager::getInstance()->setCurrentActiveFrame(selectedFrameKey);
}
