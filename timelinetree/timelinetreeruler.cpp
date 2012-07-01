#include <QtGui>

#include "timelinetreeruler.h"

TimelineTreeRuler::TimelineTreeRuler(QWidget *parent) :
    QHeaderView(Qt::Horizontal, parent)
{
    m_timeline = new Timeline(100, this);
    setResizeMode(QHeaderView::Fixed);
    connect(m_timeline, SIGNAL(positionChanged(int)), this, SLOT(graphicalRepaint()));
}

Timeline *TimelineTreeRuler::timeline() const
{
    return m_timeline;
}

void TimelineTreeRuler::mousePressEvent(QMouseEvent *e)
{
    timeline()->setPosition((e->pos().x()+offset())/FRAME_WIDTH);
    e->accept();
}

void TimelineTreeRuler::mouseMoveEvent(QMouseEvent *e)
{
    if(e->buttons()==Qt::LeftButton) {
        timeline()->setPosition((e->pos().x()+offset())/FRAME_WIDTH);
        e->accept();
    }
}

void TimelineTreeRuler::paintEvent(QPaintEvent *event)
{
    QPainter p(viewport());

    int off = offset();
    int left = viewport()->rect().left()+off;
    int right = viewport()->rect().right()+off;
    int height = viewport()->height();

    int frame_left = left/FRAME_WIDTH;
    int frame_right = right/FRAME_WIDTH;

    p.save();
    p.translate(-off+FRAME_HALF_WIDTH, 0);

    for(int f=frame_left/10*10;f<=frame_right;f+=10) {
        p.setPen(QPen(QColor(192,192,192)));
        p.drawLine(f*FRAME_WIDTH,0,f*FRAME_WIDTH,height);
        p.setPen(QPen(QColor(0,0,0)));
        p.drawText(f*FRAME_WIDTH+FRAME_HALF_WIDTH, height-4, QString::number(f));
    }
    p.restore();

    p.save();
    p.setPen(QPen(QColor(220,220,220)));
    p.drawLine(0, height-1, viewport()->width(), height-1);
    p.restore();

    p.save();
    p.translate(-off+FRAME_HALF_WIDTH, 0);

    p.setPen(QPen(QColor(220,90,90)));
    p.setBrush(QBrush(QColor(220,90,90,128)));
    p.drawRect(timeline()->position()*FRAME_WIDTH-FRAME_HALF_WIDTH,0,FRAME_WIDTH, height-1);

    p.restore();
    event->accept();
}

void TimelineTreeRuler::graphicalRepaint()
{
    setDirtyRegion(viewport()->rect());
    repaint();
}
