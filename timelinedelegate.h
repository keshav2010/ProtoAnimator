#ifndef TIMELINEDELEGATE_H
#define TIMELINEDELEGATE_H

#include<QAbstractItemDelegate>
#include<QPainter>

class TimelineDelegate : public QAbstractItemDelegate
{
    Q_OBJECT

public:
    TimelineDelegate(QObject *parent = nullptr);
    virtual ~TimelineDelegate();
    void paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // TIMELINEDELEGATE_H
