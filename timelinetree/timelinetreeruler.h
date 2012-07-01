#ifndef TIMELINETREERULER_H
#define TIMELINETREERULER_H

#include <QHeaderView>

#include "timeline.h"
#include "timelinetreeconfig.h"

class TimelineTreeRuler : public QHeaderView
{
    Q_OBJECT
public:
    TimelineTreeRuler(QWidget* parent = 0);

    Timeline* timeline() const;

protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void paintEvent(QPaintEvent *event);

private slots:
    void graphicalRepaint();

private:
    Timeline* m_timeline;
};

#endif // TIMELINETREERULER_H
