#ifndef FRAMESEDITOR_H
#define FRAMESEDITOR_H

#include<QGraphicsView>
#include<QGraphicsScene>
#include "frame.h"
#include "framemanager.h"
#include "spritemanager.h"
#include <QRectF>
#include "animationdriver.h"
/*
 * FrameEditor class inherits QGraphicsView, which is used to render QGraphicsScene
 * overall, FrameEditor will be used to view animation-frame (class in : frame.h) , interact with frame
 * data and manipulate it.
 *
 * It is to be noted that frameEditor when initialized, should provide atleast 1 single frame by default to work upon,
 * further frames can then later be added by user
 */
//only single instance of frameEditor will be used

// TODO : Remove singleton design and rather establish composition (has-a) relationship with frameManager
class FramesEditor : public QGraphicsView
{
    Q_OBJECT

public:
    ~FramesEditor();
    static FramesEditor* getInstance();
    static void setParent(QWidget *parent=0);
    static QWidget *objectParent;

    AnimationDriver* getAnimationDriver() const;

public slots:
    void renderFrame(Frame* activeFrame);

private:
    FramesEditor(QWidget* parent = 0);

    static bool isAlreadyExist;
    static FramesEditor* frameEditor;

    AnimationDriver *animationDriver;
};

#endif // FRAMESEDITOR_H
