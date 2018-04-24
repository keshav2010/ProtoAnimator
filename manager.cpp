#include "manager.h"
//parent : mainWindow

//static data
bool Manager::isAlreadyExist=false;
Manager* Manager::manager = 0;
QObject* Manager::objectParent = 0;


Manager::Manager(QObject *parent) : QObject(parent)
{
    SpriteManager::setObjectParent(this);
    FrameManager::setObjectParent(this);

    //switched frame
    QObject::connect(FrameManager::getInstance(), &FrameManager::setNewActiveFrame,
                        FrameManager::getInstance(), &FrameManager::loadFrameDataInFrame);

    //added new frame
    QObject::connect(this, &Manager::addFrameToFrameBank,
                     FrameManager::getInstance(), &FrameManager::addFrameObject);

}

Manager::~Manager(){
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
