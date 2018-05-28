#include "spritemanager.h"
#include"framemanager.h"

//static data
QObject* SpriteManager::objectParent=0;
SpriteManager* SpriteManager::spriteManager=0;
bool SpriteManager::isAlreadyExist=false;

SpriteManager* SpriteManager::getInstance(){
    if(!isAlreadyExist){
        spriteManager = new SpriteManager(objectParent);
        isAlreadyExist=true;
    }
    return spriteManager;

}

void SpriteManager::setObjectParent(QObject *parent){
    objectParent=parent;
}
//----------------------------------------------------


//parent = manager
SpriteManager::SpriteManager(QObject *parent)
    : QObject(parent)
{
    qDebug()<<"(SpriteManager.cpp) constructor";
    spritePixmap=0;//    spritePixmap = new QPixmap;
    spriteEditorDialog=0; //    spriteEditorDialog = new SpritePropertyEditorDialog(spritePixmap);

    QObject::connect(this, &SpriteManager::addSprite, this, &SpriteManager::addSpriteObject);
}

/*
const QMap<QString, AnimatableSpriteItem*>* SpriteManager::getObjectGraph()
{
    return &objectGraph;
}
*/

SpriteManager::~SpriteManager()
{

    isAlreadyExist=false;
    if(spritePixmap)
        delete spritePixmap;
    if(spriteEditorDialog)
        delete spriteEditorDialog;
}

void SpriteManager::addSpriteObject(const QString &imagePath)
{
    //spritePixmap = new QPixmap(imagePath);
    spriteEditorDialog = new SpritePropertyEditorDialog(imagePath);
    spriteEditorDialog->show();
    spriteEditorDialog->updateScaleUI();
}

//adds final sprite object to spriteBank
//parameters supplied by spritePropertyEditorDialog


void SpriteManager::addToBank(QPixmap *spritePixmap, QString spriteName)
{
    if(spriteName.isEmpty() || spritePixmap == 0){
        delete spriteEditorDialog;
        return;
    }
    FrameManager::getInstance()->getCurrentActiveFrame()->addFrameItem(spriteName, spritePixmap);
    delete spriteEditorDialog;
}
/*
void SpriteManager::removeFromBank(const QString &spriteName)
{
    if(objectGraph[spriteName]){
        delete objectGraph[spriteName];
        objectGraph.remove(spriteName);
    }
}
*/
