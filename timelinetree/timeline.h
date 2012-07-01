#ifndef TIMELINE_H
#define TIMELINE_H

#include <QObject>
#include <QMetaType>

class Timeline : public QObject {
    Q_OBJECT
public:
    Timeline(int end = 100, QObject * parent = 0);
    int position() const;
signals:
    void positionChanged(int t);
public slots:
    void setPosition(int t);
    void setEnd(int m);
private:
    int m_position;
    int m_end;
};

class TimelineKeyframeList {
public:
    TimelineKeyframeList(const QList<int> &keyframes = QList<int>()) {
        m_keyframes = keyframes;
    }

    QList<int>& keyframes() { return m_keyframes; }
private:
    QList<int> m_keyframes;
};

Q_DECLARE_METATYPE(TimelineKeyframeList)

#endif // TIMELINE_H
