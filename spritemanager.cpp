#include "spritemanager.h"
#include"framemanager.h"

//static data
QObject* SpriteManager::objectParent=0;
SpriteManager* SpriteManager::spriteManager=0;
bool SpriteManager::isAlreadyExist=false;

SpriteManager* SpriteManager::getInstance(){
    if(!isAlreadyExist){
        isAlreadyExist=true;
        spriteManager = new SpriteManager(objectParent);
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
    qDebug()<<"(~SpriteManager.cpp) destructor called";
    isAlreadyExist=false;
    qDebug()<<"(~SpriteManager.cpp) attempting to delete spritePixmap "<<(spritePixmap!=nullptr);
    if(spritePixmap!=nullptr){
        delete spritePixmap;
        spritePixmap = nullptr;
        qDebug()<<"(~SpriteManager.cpp) >> deleted pixmap";
    }
    qDebug()<<"(~SpriteManager.cpp) attempting to delete spriteEditorDialog "<<(spriteEditorDialog!=nullptr);
    if(spriteEditorDialog!=nullptr){
        delete spriteEditorDialog;
        spriteEditorDialog = nullptr;
        qDebug()<<"(~SpriteManager.cpp) > deleting spriteEditorDialog ";
    }
}

void SpriteManager::addSpriteObject(const QString &imagePath)
{
    qDebug()<<"(SpriteManager.cpp > addSpriteObject(imagePath) : function call enter";

    spriteEditorDialog = new SpritePropertyEditorDialog(imagePath);
    spriteEditorDialog->show();
    spriteEditorDialog->updateScaleUI();
}

void SpriteManager::addToBank(QPixmap *spritePixmap, QString spriteName)
{
    if(spriteName.isEmpty() || spritePixmap == 0){
        delete spriteEditorDialog;
        spriteEditorDialog=nullptr;
        return;
    }
    qDebug()<<"(SpriteManager.cpp) : supplying data to frame ";
    //get current active frame and pass on the information
    FrameManager::getInstance()->getCurrentActiveFrame()->addFrameItem(spriteName, spritePixmap);
    delete spriteEditorDialog;
    spriteEditorDialog = nullptr;
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
