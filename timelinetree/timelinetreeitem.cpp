#include <QStringList>

#include "timelinetreeitem.h"

TimelineTreeItem::TimelineTreeItem(const QString &name, const TimelineKeyframeList &keyframes, TimelineTreeItem *parent)
{
    parentItem = parent;
    this->name = name;
    this->keyframes = keyframes;
}

TimelineTreeItem::~TimelineTreeItem()
{
    qDeleteAll(childItems);
}

void TimelineTreeItem::appendChild(TimelineTreeItem *item)
{
    childItems.append(item);
}

TimelineTreeItem *TimelineTreeItem::child(int row)
{
    return childItems.value(row);
}

int TimelineTreeItem::childCount() const
{
    return childItems.count();
}

int TimelineTreeItem::columnCount() const
{
    return 2;
}

QVariant TimelineTreeItem::data(int column) const
{
    switch(column) {
    case 0:
        return name;
    case 1:
        return qVariantFromValue(keyframes);
    default:
        return 0;
    }
}

TimelineTreeItem *TimelineTreeItem::parent()
{
    return parentItem;
}

int TimelineTreeItem::row() const
{
    if (parentItem)
        return parentItem->childItems.indexOf(const_cast<TimelineTreeItem*>(this));

    return 0;
}

