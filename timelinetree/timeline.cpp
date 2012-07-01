#include "timeline.h"

Timeline::Timeline(int end, QObject *parent) :
    QObject(parent), m_end(end), m_position(0)
{}

int Timeline::position() const
{
    return m_position;
}

void Timeline::setPosition(int t)
{
    if(t<0)
        t=0;
    else if(t>=m_end)
        t = m_end-1;
    if(m_position!=t) {
        m_position = t;
        emit positionChanged(m_position);
}
}

void Timeline::setEnd(int m)
{
    if(m>0)
        m_end = m;
}
