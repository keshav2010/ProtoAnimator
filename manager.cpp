#include "manager.h"
//parent : mainWindow

//static data
bool Manager::isAlreadyExist=false;
Manager* Manager::manager = 0;
QObject* Manager::objectParent = 0;

Manager::~Manager()
{
    isAlreadyExist=false;
    delete manager;
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
Manager::Manager(QObject *parent) : QObject(parent)
{
    SpriteManager::setObjectParent(this);
    FrameManager::setObjectParent(this);
    connect(this, SIGNAL(addSpriteToImageBank(QString)), SpriteManager::getInstance(), SLOT(addSpriteObject(QString)) );
    connect(this, SIGNAL(addFrameToFrameBank()), FrameManager::getInstance(), SLOT(addFrameObject()));
}
