#ifndef TIMELINEWIDGET_H
#define TIMELINEWIDGET_H

#include <QtGui>
#include "timelinetree/timelinetreeview.h"

class TimelineWidget : public QMainWindow
{
    Q_OBJECT
public:
    TimelineWidget(QWidget *parent = 0);

    QToolBar* toolBar() const {
        return toolbar;
    }

    TimelineTreeView* view() const {
        return timelineView;
    }

protected:
    QToolBar* toolbar;
    QSpinBox* frameSpin;
    QTreeView* timelineTree;
    TimelineTreeView* timelineView;
private:
    void createToolBar();
    void createTimelineView();

};

#endif // TIMELINEWIDGET_H
