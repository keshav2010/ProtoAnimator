#ifndef FRAMEMANAGER_H
#define FRAMEMANAGER_H

#include <QObject>
#include<QMap>
#include "frame.h"
/*
 *  Contains list of frames that are visible on timeline and thus are responsible
 * for generation of animated sequences, this class is intended to work with
 * FRAME-SPRITE MANAGER INTERFACE in order to work properly, the signal propagation
 * takes place between these classes.
 *
 *
 * This class also contain information about current active frame
 */
class FrameManager : public QObject
{
    Q_OBJECT
public:
    explicit FrameManager(QObject *parent = nullptr);

signals:

public slots:
    bool addFrameObject();

private:
    //A Data structure holding frames
    //A Flag holding current active frame

    QMap<int, Frame*> FrameBank;
    int currentActiveFrame;
    const int keyStartFrame;//default keyframe can't be removed or deleted, value is 0
};

#endif // FRAMEMANAGER_H
