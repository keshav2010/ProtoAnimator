#include "timelinedelegate.h"
#include "QDebug"

#define REDCOLOR QColor(200, 0, 0)
#define GREENCOLOR QColor(0, 200, 0)

//definations for class TimelineDelegate goes here
TimelineDelegate::TimelineDelegate(QObject *parent)
    :QAbstractItemDelegate(parent)
{
    qDebug()<<"(TimelineDelegate.cpp) constructor";
}

TimelineDelegate::~TimelineDelegate()
{
    qDebug()<<"(~TimelineDelegate.cpp) destructor";
}

void TimelineDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    //if item selected, fill the background of entire bounding rect
    if(option.state & QStyle::State_Selected)
    {
        painter->fillRect(option.rect, option.palette.highlight());
    }
    int rectPosition = 10*index.row();
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing, true);

    painter->setPen(Qt::NoPen);

    if(option.state & QStyle::State_Selected)
        painter->setBrush(option.palette.highlightedText());
    else
        painter->setBrush(QBrush(GREENCOLOR));

    //color immutable frame with red
    if(index.column() == 0)
        painter->setBrush(QBrush(REDCOLOR));

    painter->drawRect(option.rect.x() + rectPosition, option.rect.y(), 10, 20);
    painter->restore();
}

QSize TimelineDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QSize(10, 20);
}

