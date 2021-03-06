#ifndef FRAMEMANAGER_H
#define FRAMEMANAGER_H

#include <QObject>
#include<QMap>
#include "frame.h"
#include "frameseditor.h"
#include "timelinemodel.h"
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
    static void setObjectParent(QObject *parent);
    ~FrameManager();

    Frame* getDefaultFrame();
    Frame* getCurrentActiveFrame();
    int getCurrentActiveFrameByID();
    int getTotalFrames();
    QPixmap getFramePixmap(int);

    void setCurrentActiveFrame(int frameKey);

    QMap<int, Frame*> *getPointerToFrameBank();

signals:
    //signal that carries information related to number of frames
    void frameBankChanged(QMap<int, Frame*> *ref=nullptr);

    //signal that carries information for single active frame
    void broadcastFrameItems(QMap<QString, AnimatableSpriteItem*> *ref=nullptr);

public slots:
    //adds a single frame object
    bool addFrameObject();

    /*
     * deletes a single frame object
     */
    void deleteFrames(QVector<int> &frameKeys);

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
    QMap<int, Frame*> frameBank;
    Frame* startFrame;
    int currentActiveFrame;
};

#endif // FRAMEMANAGER_H
