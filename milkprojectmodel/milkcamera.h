#ifndef MILKCAMERA_H
#define MILKCAMERA_H

#include <QObject>
#include <mmd/mmd.hxx>

class CameraPose {
public:
    CameraPose() {}
};

class CameraParameter : public QObject
{
    Q_OBJECT
public:
    CameraParameter(QObject * parent = 0) : QObject(parent) {}

    enum parameter_type { CAMERA_MMD, CAMERA_MILK, CAMERA_GENERAL };
    virtual parameter_type type() const = 0;

    virtual operator CameraPose() const = 0;

    virtual void interpolate(float ratio, const CameraParameter* p1, const CameraParameter* p2);
signals:
    void changed();
};

class CameraObject : public QObject
{
    Q_OBJECT
public:
    CameraObject(CameraParameter* parameter, QObject * parent = 0) : QObject(parent) {
        m_parameter = parameter;
        m_parameter->setParent(this);
    }

    const CameraPose& pose() const {
        return CameraPose(*m_parameter);
    }

    CameraParameter* parameter() const {
        return m_parameter;
    }

protected:
    CameraParameter* m_parameter;
};

#endif // MILKCAMERA_H
