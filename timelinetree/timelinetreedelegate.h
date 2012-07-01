#ifndef TIMELINETREEDELEGATE_H
#define TIMELINETREEDELEGATE_H

#include <QStyledItemDelegate>

#include "timelinetreeconfig.h"

class TimelineTreeDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    TimelineTreeDelegate(QWidget *parent = 0) : QStyledItemDelegate(parent) {}

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;

};

#endif // TIMELINETREEDELEGATE_H
