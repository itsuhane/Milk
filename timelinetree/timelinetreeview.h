#ifndef TIMELINETREEVIEW_H
#define TIMELINETREEVIEW_H

#include <QTreeView>

#include "timelinetreemodel.h"
#include "timelinetreeruler.h"

class TimelineTreeView : public QTreeView
{
    Q_OBJECT
public:
    TimelineTreeView(QWidget *parent = 0);
    ~TimelineTreeView();
    TimelineTreeRuler* ruler() const;
    void setModel(TimelineTreeModel *model);
    void scrollTo(const QModelIndex &index, ScrollHint hint);

public slots:
    void scrollToPosition(int position);

protected:
    void paintEvent(QPaintEvent *event);
private:
    void setModel(QAbstractItemModel *model);
private slots:
    void graphicalRepaint();
};
#endif // TIMELINETREEVIEW_H
