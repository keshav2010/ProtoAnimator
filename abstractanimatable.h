#ifndef ABSTRACTANIMATABLE_H
#define ABSTRACTANIMATABLE_H

//an abstract class that must be inherited by any object that can be animated
class AbstractAnimatable
{

public:
    AbstractAnimatable();
protected:
    QVector<AbstractAnimatable> children;
    AbstractAnimatable parent;
};

#endif // ABSTRACTANIMATABLE_H
