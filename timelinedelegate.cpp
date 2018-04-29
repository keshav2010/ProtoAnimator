#include "timelinedelegate.h"


//definations for class TimelineDelegate goes here
TimelineDelegate::TimelineDelegate(QObject *parent)
    :QAbstractItemDelegate(parent)
{

}

void TimelineDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    //if item selected, fill the background of entire bounding rect
    if(option.state & QStyle::State_Selected)
    {
        painter->fillRect(option.rect, option.palette.highlight());
    }
    int rectPosition = 10*(index.row()-1);
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setPen(Qt::NoPen);

    if(option.state & QStyle::State_Selected)
        painter->setBrush(option.palette.highlightedText());
    else painter->setBrush(option.palette.text());

    painter->drawRect(option.rect.x(), option.rect.y(), 10, 20);

    painter->restore();
}

QSize TimelineDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QSize(10, 20);
}
