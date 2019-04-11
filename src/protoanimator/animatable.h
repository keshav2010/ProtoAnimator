#ifndef ANIMATABLE_H
#define ANIMATABLE_H

#include<QMap>
#include<QPoint>

/*
 * Base Class for all objects that are intended to be animated
 * note that the functions written in this class are now quite useless as
 * Qt already provides its own Base Classes for similar purpose, which has its own seperate
 * environment known as Graphics-View-Framework.
 */
class Animatable
{
public:
    Animatable(const QString& str=0);
    virtual ~Animatable();

    //getters
    int getCenterX() const;
    int getCenterY() const;
    QPoint getCenterPos() const;

    int getParentX() const;
    int getParentY() const;
    QPoint getParentPos() const;

    int getParentRelativeOffsetX() const;
    int getParentRelativeOffsetY() const;
    QPoint getParentRelativeOffset() const;

    int getPivotX() const;
    int getPivotY() const;
    QPoint getPivotPos() const;

    QString getName() const;
    void setName(const QString &);

    Animatable* getParent() const;


    //this function is called to update pivot point
    void updatePivotPoint(int, int);
    void resetPivotPoint();

    void moveTo(int, int);//move an object relative to world

    void addChild(Animatable*);
    void removeChild(const QString&, bool removeFromMemory=false);//removes
    void removeAllChild(bool removeFromMemory=false); //removes all children of this object from memory


    //updates offset that measure relative distance between pivot-point and center-point
    //once offset is updated, pivot point position is also changed to validate this offset change
    void updateOffset(int, int);

    //updates offset that measure relative distance between parent's center point
    //and child's center point (this), once offset is updated, it then changes center-point
    //of child (this) so as to validate the change in offset
    void updateParentRelativeOffset(int, int);
protected:
    //helper fxn
    void setParent(Animatable*);
    void unsetParent();

    //name is always unique so as to access object
    QString name;
    //indicates if object have a parent or not
    bool isChild;

    //centerX and centerY specify position
    int centerX, centerY;
    //pivotX and pivotY specifies the point around which object will be rotated
    int pivotX, pivotY;
    float angle;

    //offset calculates how far pivot point is from the center point, this is
    //by default 0 but when user will move the pivot point
    //offset will store the relative distance between center and pivot points
    int offsetX, offsetY;

    //if in case an object have a parent, these variables keep track of relative position between
    //object and it's parent
    int parentRelativeOffsetX, parentRelativeOffsetY;
    QMap<QString,Animatable*> children;
    Animatable *parent;
};
#endif // ANIMATABLE_H
