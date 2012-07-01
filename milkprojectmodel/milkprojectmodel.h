#ifndef MILKPROJECTMODEL_H
#define MILKPROJECTMODEL_H

#include <QObject>

#include "milkcamera.h"

class MilkProjectModel : public QObject
{
    Q_OBJECT
public:
    MilkProjectModel(QObject * parent = 0) : QObject(parent), m_frame_position(0), m_frame_length(100) {}

public slots:
    void setFramePosition(int position) {
        if(position<0) {
            position = 0;
        } else if (position>=m_frame_length) {
            position = m_frame_length-1;
        }
        if(m_frame_position!=position) {
            m_frame_position = position;
            emit framePositionChanged(m_frame_position);
        }
    }

    void setFrameLength(int length) {
        if(length>0) {
            m_frame_length = length;
            emit frameLengthChanged(m_frame_length);
        }
    }

signals:
    void framePositionChanged(int);
    void frameLengthChanged(int);

private:
    int m_frame_length;
    int m_frame_position;
};

#endif // MILKPROJECTMODEL_H
