#include "manager.h"
//parent : mainWindow

//static data
bool Manager::isAlreadyExist=false;
Manager* Manager::manager = 0;
QObject* Manager::objectParent = 0;

Manager::~Manager()
{
    isAlreadyExist=false;
}

//improvement required, currently manager class is **assummed** to be initialized in
//mainWindow first and thus based on my personal coding style or lazyness, im just avoiding any special
//checks or function call to explicitly set parent of this manager class.
Manager* Manager::getInstance()
{
    if( !isAlreadyExist){
        manager = new Manager(objectParent);
        isAlreadyExist=true;
    }
    return manager;
}

void Manager::setParent(QObject *parent)
{
    objectParent = parent;
}
Manager::Manager(QObject *parent) : QObject(parent),
    spriteManager(new SpriteManager(this)),
    frameManager(new FrameManager(this))
{
    connect(this, SIGNAL(addSpriteToImageBank(QString)), spriteManager, SLOT(addSpriteObject(QString)) );
    connect(this, SIGNAL(addFrameToFrameBank()), frameManager, SLOT(addFrameObject()));
}
