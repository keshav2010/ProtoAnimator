#include "animatable.h"
#include <QDebug>
#include <QPoint>
Animatable::Animatable(const QString &_name):name(_name)
{
    centerX = centerY = 0;
    pivotX = pivotY = 0;
    offsetX = offsetY = 0;
    parentRelativeOffsetX = 0;
    parentRelativeOffsetY = 0;
    angle=0;
    isChild = false;
}
Animatable::~Animatable()
{
    removeAllChild(true); //destroy all children from memory
}

QString Animatable::getName() const{
    return name;
}
void Animatable::setName(const QString& _name){
    name = _name;
}

QPoint Animatable::getCenterPos() const{
    return QPoint(centerX, centerY);
}
int Animatable::getCenterX() const {
    return centerX;
}
int Animatable::getCenterY() const {
    return centerY;
}

QPoint Animatable::getParentPos() const{
    QPoint parentPosition(0,0);
    if(parent)
    {
        parentPosition.setX(parent->getParentX());
        parentPosition.setY(parent->getParentY());
    }
    return parentPosition;
}
int Animatable::getParentX() const{
    return parent->getCenterX();
}
int Animatable::getParentY() const{
    return parent->getCenterY();
}


QPoint Animatable::getPivotPos() const{
    return QPoint(pivotX, pivotY);
}
int Animatable::getPivotX() const{
    return pivotX;
}
int Animatable::getPivotY() const{
    return pivotY;
}

//helper private function, sets up flags and assign parent reference
void Animatable::setParent(Animatable *_parent){
    isChild=true;
    parent = _parent;
}
//helper private function
void Animatable::unsetParent() //does not remove parent from memory
{
    isChild=false;
    parent = nullptr;
}
Animatable* Animatable::getParent() const{
    return parent;
}

QPoint Animatable::getParentRelativeOffset() const{
    return QPoint(parentRelativeOffsetX, parentRelativeOffsetY);

}
int Animatable::getParentRelativeOffsetX() const{
    return parentRelativeOffsetX;
}
int Animatable::getParentRelativeOffsetY() const{
    return parentRelativeOffsetY;
}

void Animatable::addChild(Animatable *child)
{
    QString childName(child->getName());
    if(name == childName){ //child name can't be same as parent name
        qDebug()<<"Parent and Child Name same, failed to addChild";
        return;
    }
    qDebug()<<"setting child : "<<childName;
    if(children.contains(childName)){
        removeChild(childName, true);//true deletes the existing child from memory thus it is not even available for render
    }
    child->setParent(this);//set up flags and parent reference
    children.insert(childName, child);
    children[childName]->setParent(this);
    qDebug()<<"\n child added , now parent holds : "<<children.size()<<"\n";
}
void Animatable::removeAllChild(bool removeFromMemory)
{
    QMap<QString, Animatable*>::iterator childrenIterator = children.begin();

    for(childrenIterator; childrenIterator!=children.end(); childrenIterator++){
        removeChild( (*childrenIterator)->getName(), removeFromMemory);
    }
}

/*removeFromMemory = false by default
* when false, the object is retained in the memory and is being rendered based on its own properties
* when true, the object is removed from memory as well as it is not being rendered anymore (i.e, delete)
*/
void Animatable::removeChild(const QString& _childName, bool removeFromMemory)
{
    if(!children.contains(_childName)){
        return;
    }
    //reset flags and parent-reference in child
    children[_childName]->unsetParent();
    if(removeFromMemory)
        delete children[_childName]; //free up memory by deleting the object
    children.remove(_childName);
}

//moveTo is responsible for changing position of object in world space
void Animatable::moveTo(int _centerX, int _centerY)
{
    qDebug()<<"---- parent moving : "<<"("<<centerX<<","<<centerY<<")";
    centerX = _centerX;
    centerY = _centerY;
    updatePivotPoint(centerX+offsetX, centerY+offsetY);

    if(isChild){
       /*call function only if there is a change in offset, this happens when user directly changes
        * parentRelativeOffset Value, otherwise if moveTo() is called via parent on its child while being
        * in motion itself, then this updateParentRelativeOffset() function call on child
        * is avoided as parentOffset remains
        * same in such case and re-calling the function makes no change.
        */
       if(centerX - getParentX() != getParentRelativeOffsetX() &&
               centerY - getParentY() != getParentRelativeOffsetY())
       {
        updateParentRelativeOffset(centerX - getParentX(), centerY - getParentY());
       }
    }
    //now if the object recently moved have children, then move the children
    //by (parentPosition + parentRelativeOffset of children)
    QMap<QString, Animatable*>::iterator childrenIterator = children.begin();
    for(childrenIterator; childrenIterator!=children.end(); childrenIterator++)
    {
        int childX = (*childrenIterator)->getCenterX(); //debug purpose only
        int childY = (*childrenIterator)->getCenterY(); //debug purpose only
        int childParentOffsetX = (*childrenIterator)->getParentRelativeOffsetX();
        int childParentOffsetY = (*childrenIterator)->getParentRelativeOffsetY();
        qDebug()<<"updating child : "<<(*childrenIterator)->getName();
        (*childrenIterator)->moveTo(childParentOffsetX + centerX, childParentOffsetY + centerY);
        qDebug()<<" children pos : ("<<childX<<","<<childY<<")"<<" parent offsets : "<<"("<<(*childrenIterator)->getParentRelativeOffsetX()<<","<<(*childrenIterator)->getParentRelativeOffsetY()<<")";
    }
}

void Animatable::updateParentRelativeOffset(int _parentRelativeOffsetX, int _parentRelativeOffsetY)
{
    parentRelativeOffsetX = _parentRelativeOffsetX;
    parentRelativeOffsetY = _parentRelativeOffsetY;


    qDebug()<<"** offset-relative-to-parent of "<<this->getName()<<" : "<<parentRelativeOffsetX<<","<<parentRelativeOffsetY;


    //not calling moveTo() as if(isChild) check would lead to infinite fxn calls
    //so instead just copied essential code from moveTo() here
    centerX = parentRelativeOffsetX + getParentX();
    centerY = parentRelativeOffsetY + getParentY();
    updatePivotPoint(centerX + offsetX, centerY+offsetY);

    // NOTE : when changing relative position of child and parent, the children of child won't be affected
    //relative to their parent, only the selected node will be affected
    /*
    QMap<QString, Animatable*>::iterator childrenIterator = children.begin();
    for(childrenIterator; childrenIterator!=children.end(); childrenIterator++)
    {
        (*childrenIterator)->updateParentRelativeOffset((*childrenIterator)->getCenterX() - (*childrenIterator)->getParentX(),
                                                (*childrenIterator)->getCenterY() - (*childrenIterator)->getParentY());
    }
    */
}
//this method updates offset that measure relative distance between pivot points and center point
//and also, in order to validate this change, it moves pivot point accordingly
void Animatable::updateOffset(int _offsetX, int _offsetY)
{
    //change offset
    offsetX = _offsetX;
    offsetY = _offsetY;

    //move pivot points to validate above change
    pivotX = centerX + offsetX;
    pivotY = centerY + offsetY;
}


//call to updatePivotPoint() must terminate at terminate at some point(finite)
void Animatable::updatePivotPoint(int _pivotX, int _pivotY)
{
    //changes pivot points
    pivotX = _pivotX;
    pivotY = _pivotY;

    //Also updating offset that measure relative position of pivot with respect to center point
    updateOffset(pivotX - centerX, pivotY - centerY);
}
void Animatable::resetPivotPoint(){
    //move pivot Point to same position as center point
    updatePivotPoint(centerX, centerY);
}

