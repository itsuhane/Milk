#ifndef TIMELINETREEMODEL_H
#define TIMELINETREEMODEL_H

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>

class TimelineTreeItem;

class TimelineTreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    TimelineTreeModel(QObject *parent = 0);
    ~TimelineTreeModel();

    QVariant data(const QModelIndex &index, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &index) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;

private:

    TimelineTreeItem *rootItem;
};

#endif
