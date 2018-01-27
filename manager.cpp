#include "manager.h"
//parent : mainWindow

bool Manager::isAlreadyExist=false;
Manager* Manager::manager = Q_NULLPTR;

Manager::~Manager()
{
    isAlreadyExist=false;
}

//improvement required, currently manager class is **assummed** to be initialized in
//mainWindow first and thus based on my personal coding style or lazyness, im just avoiding any special
//checks or function call to explicitly set parent of this manager class.
Manager *Manager::getInstance(QObject *parent)
{
    if( !isAlreadyExist){
        manager = new Manager(parent);
        isAlreadyExist=true;
    }
    return manager;
}
Manager::Manager(QObject *parent) : QObject(parent),
    spriteManager(new SpriteManager(this)),
    frameManager(new FrameManager(this))
{
    connect(this, SIGNAL(addSpriteToImageBank(QString)), spriteManager, SLOT(addSpriteObject(QString)) );
    connect(this, SIGNAL(addFrameToFrameBank()), frameManager, SLOT(addFrameObject()));

}
