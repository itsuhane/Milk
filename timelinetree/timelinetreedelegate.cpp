#include <QtGui>

#include "timeline.h"
#include "timelinetreedelegate.h"
#include "timelinetreeconfig.h"

QSize TimelineTreeDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);
    return QSize(0,FRAME_HEIGHT);
}

void TimelineTreeDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
//    QPoint marker[3] = {
//        QPoint(-MARKER_SIZE,FRAME_HEIGHT),
//        QPoint(0,FRAME_HEIGHT-MARKER_SIZE),
//        QPoint(MARKER_SIZE,FRAME_HEIGHT)
//    };
    const QList<int> &keyframes = index.data().value<TimelineKeyframeList>().keyframes();

    painter->save();
    painter->setPen(QPen(QColor(220,220,220)));

    painter->translate(0,option.rect.top());
    painter->drawLine(0, FRAME_HEIGHT-1, painter->viewport().width(), FRAME_HEIGHT-1);

    painter->translate(option.rect.left()+FRAME_HALF_WIDTH,0);

    QLinearGradient gradient(0,0,0,1);
    gradient.setCoordinateMode(QGradient::ObjectBoundingMode);
    gradient.setColorAt(0,QColor(110,161,241));
    gradient.setColorAt(1,QColor(87,127,191));
    painter->setPen(QPen(QColor(64,64,64)));
    painter->setBrush(QBrush(gradient));
    for(int i=1;i<keyframes.size();++i) {
        painter->drawRect(keyframes[i-1]*FRAME_WIDTH,BAR_MARGIN-1,(keyframes[i]-keyframes[i-1])*FRAME_WIDTH, FRAME_HEIGHT-BAR_MARGIN*2);
    }

    painter->setPen(QPen(QColor(64,64,64)));
    painter->setBrush(QBrush(QColor(255,255,255)));
    for(int i=0;i<keyframes.size();++i) {
        painter->save();
        painter->translate(keyframes[i]*FRAME_WIDTH, -1);
//        painter->drawPolygon(marker, 3);
        painter->drawRect(-MARKER_HALF_WIDTH,FRAME_HALF_HEIGHT-MARKER_HALF_HEIGHT,MARKER_WIDTH, MARKER_HEIGHT);
        painter->restore();
    }

    painter->restore();
}
