#ifndef FRAMEMANAGER_H
#define FRAMEMANAGER_H

#include <QObject>
#include<QMap>
#include "frame.h"
#include "frameseditor.h"
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

    static QObject *objectParent;
    //explicit FrameManager(QObject *parent = nullptr);
    static FrameManager* getInstance();

    static QRectF frameSceneRect;

    ~FrameManager();
    static void setObjectParent(QObject *parent);

    Frame* getDefaultFrame();
    Frame* getCurrentActiveFrame();
    int getCurrentActiveFrameByID();
    QMap<int, Frame*> *getPointerToFrameBank();

public slots:
    bool addFrameObject();

private:
    static FrameManager *frameManager;
    static bool isAlreadyExist;

    explicit FrameManager(QObject *parent = 0);

    /*
     *
     * frameBank maps key to each frame object, where key is
     * currently set to frame number
     */
    const int startFrameIndex;//default keyframe can't be removed or deleted, value is 0
    QMap<int, Frame*> *frameBank;
    Frame* startFrame;
    int currentActiveFrame;
};

#endif // FRAMEMANAGER_H
