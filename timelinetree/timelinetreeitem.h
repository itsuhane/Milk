#ifndef TIMELINETREEITEM_H
#define TIMELINETREEITEM_H

#include <QList>
#include <QVariant>

#include "timeline.h"

class TimelineTreeItem
{
public:
    TimelineTreeItem(const QString &name, const TimelineKeyframeList &keyframes = TimelineKeyframeList(), TimelineTreeItem *parent = 0);
    ~TimelineTreeItem();

    void appendChild(TimelineTreeItem *child);

    TimelineTreeItem *child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    int row() const;
    TimelineTreeItem *parent();

private:
    QList<TimelineTreeItem*> childItems;
    QString name;
    TimelineKeyframeList keyframes;
    TimelineTreeItem *parentItem;
};

#endif
