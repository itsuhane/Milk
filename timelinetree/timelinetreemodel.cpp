#include <QtGui>

#include "timelinetreeitem.h"
#include "timelinetreemodel.h"

TimelineTreeModel::TimelineTreeModel(QObject *parent)
    : QAbstractItemModel(parent)
{
    rootItem = new TimelineTreeItem("Name");
    for(int i=0;i<10;++i) {
        QList<int> keys;
        for(int j=0;j<i+1;++j) {
            keys.push_back(j*j+i);
        }
        TimelineTreeItem* item = new TimelineTreeItem(tr("Model ")+QString::number(i), TimelineKeyframeList(keys), rootItem);
        for(int j=0;j<3;++j) {
            item->appendChild(new TimelineTreeItem(tr("Bone ")+QString::number(j), TimelineKeyframeList(keys), item));
        }
        rootItem->appendChild(item);
    }
}

TimelineTreeModel::~TimelineTreeModel()
{
    delete rootItem;
}

int TimelineTreeModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return static_cast<TimelineTreeItem*>(parent.internalPointer())->columnCount();
    else
        return rootItem->columnCount();
}

QVariant TimelineTreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    TimelineTreeItem *item = static_cast<TimelineTreeItem*>(index.internalPointer());

    return item->data(index.column());
}

Qt::ItemFlags TimelineTreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVariant TimelineTreeModel::headerData(int section, Qt::Orientation orientation,
                               int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootItem->data(section);

    return QVariant();
}

QModelIndex TimelineTreeModel::index(int row, int column, const QModelIndex &parent)
            const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    TimelineTreeItem *parentItem;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<TimelineTreeItem*>(parent.internalPointer());

    TimelineTreeItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

QModelIndex TimelineTreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    TimelineTreeItem *childItem = static_cast<TimelineTreeItem*>(index.internalPointer());
    TimelineTreeItem *parentItem = childItem->parent();

    if (parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

int TimelineTreeModel::rowCount(const QModelIndex &parent) const
{
    TimelineTreeItem *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<TimelineTreeItem*>(parent.internalPointer());

    return parentItem->childCount();
}

