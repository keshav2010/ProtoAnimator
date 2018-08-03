#ifndef FRAMESEDITOR_H
#define FRAMESEDITOR_H

#include<QGraphicsView>
#include<QGraphicsScene>
#include "frame.h"
#include "framemanager.h"
#include "spritemanager.h"
#include <QRectF>
/*
 * FrameEditor class inherits QGraphicsView, which is used to render QGraphicsScene
 * overall, FrameEditor will be used to view animation-frame (class in : frame.h) , interact with frame
 * data and manipulate it.
 *
 * It is to be noted that frameEditor when initialized, should provide atleast 1 single frame by default to work upon,
 * further frames can then later be added by user
 */
//only single instance of frameEditor will be used
class FramesEditor : public QGraphicsView
{
public:

    ~FramesEditor();
    static FramesEditor* getInstance();
    static void setParent(QWidget *parent=0);
    static QWidget *objectParent;

public slots:
    void renderFrame(Frame* activeFrame);

private:
    FramesEditor(QWidget* parent = 0);

    static bool isAlreadyExist;
    static FramesEditor* frameEditor;
    //void mousePressEvent(QMouseEvent *event);
};

#endif // FRAMESEDITOR_H
