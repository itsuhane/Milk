#include <QtGui>

#include "timelinetreeview.h"
#include "timelinetreedelegate.h"

TimelineTreeView::TimelineTreeView(QWidget *parent)
    : QTreeView(parent)
{
    setHeader(new TimelineTreeRuler);
    setItemDelegate(new TimelineTreeDelegate);
    setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    setIndentation(0);
    setRootIsDecorated(false);
    setMouseTracking(true);
    connect(ruler()->timeline(), SIGNAL(positionChanged(int)), this, SLOT(scrollToPosition(int)));
    connect(ruler()->timeline(), SIGNAL(positionChanged(int)), this, SLOT(graphicalRepaint()));
}

TimelineTreeView::~TimelineTreeView()
{}

TimelineTreeRuler *TimelineTreeView::ruler() const
{
    return dynamic_cast<TimelineTreeRuler*>(header());
}

void TimelineTreeView::setModel(TimelineTreeModel *model)
{
    QTreeView::setModel(model);
    setColumnHidden(0,true);
    setColumnWidth(1,900);
}

void TimelineTreeView::scrollTo(const QModelIndex &index, QAbstractItemView::ScrollHint hint)
{
    int myValue = horizontalScrollBar()->value();
    QTreeView::scrollTo(index, hint);
    horizontalScrollBar()->setValue(myValue);
}

void TimelineTreeView::scrollToPosition(int position)
{
    int value = position*FRAME_WIDTH;
    int curr_pos = horizontalOffset();
    if(value-5*FRAME_WIDTH<curr_pos) {
        horizontalScrollBar()->setValue(value-5*FRAME_WIDTH);
    } else if(value+5*FRAME_WIDTH>curr_pos+viewport()->rect().width()) {
        horizontalScrollBar()->setValue(value+5*FRAME_WIDTH-viewport()->rect().width());
    }
}

void TimelineTreeView::setModel(QAbstractItemModel*)
{}

void TimelineTreeView::paintEvent(QPaintEvent *event)
{
    QPainter p;

    int off = header()->offset();
    int left = viewport()->rect().left()+off;
    int right = viewport()->rect().right()+off;
    int height = viewport()->height();

    int frame_left = left/FRAME_WIDTH;
    int frame_right = right/FRAME_WIDTH;
    int frame_current = ruler()->timeline()->position();

    p.begin(viewport());
    p.save();
    p.translate(-off+FRAME_HALF_WIDTH, 0);

    for(int f=frame_left;f<=frame_right;++f) {
        if(f%10==0) {
            p.setPen(QPen(QColor(192,192,192)));
        } else {
            p.setPen(QPen(QColor(220,220,220)));
        }
        p.drawLine(f*FRAME_WIDTH,0,f*FRAME_WIDTH,height);
    }
    p.restore();
    p.end();

    QTreeView::paintEvent(event);

    p.begin(viewport());
    p.save();
    p.translate(-off+FRAME_HALF_WIDTH, 0);
    p.setPen(QPen(QColor(220,90,90)));
    p.drawLine(frame_current*FRAME_WIDTH,0,frame_current*FRAME_WIDTH, height-1);

    p.restore();
    p.end();
    event->accept();
}

void TimelineTreeView::graphicalRepaint()
{
    setDirtyRegion(viewport()->rect());
    repaint();
}
