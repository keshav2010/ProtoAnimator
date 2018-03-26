#include "spritemanager.h"
#include "manager.h"


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
    spritePixmap=0;//    spritePixmap = new QPixmap;
    spriteEditorDialog=0; //    spriteEditorDialog = new SpritePropertyEditorDialog(spritePixmap);

    QObject::connect(this, &SpriteManager::addSprite, this, &SpriteManager::addSpriteObject);
}

const QMap<QString, AnimatableSpriteItem*>* SpriteManager::getObjectGraph()
{
    return &objectGraph;
}

SpriteManager::~SpriteManager()
{

    isAlreadyExist=false;
    if(spritePixmap)
        delete spritePixmap;
    if(spriteEditorDialog)
        delete spriteEditorDialog;
    //delete spriteManager;
}

void SpriteManager::addSpriteObject(const QString &imagePath)
{
    spritePixmap = new QPixmap(imagePath);
    spriteEditorDialog = new SpritePropertyEditorDialog(spritePixmap);
    spriteEditorDialog->show();
    spriteEditorDialog->updateScaleUI();
}

//adds final sprite object to spriteBank
void SpriteManager::addToBank()
{
    QString spriteName = spriteEditorDialog->updatePixmap();
    if(spriteName.isEmpty()){
        delete spriteEditorDialog;
        delete spritePixmap;
        return;
    }
    if(objectGraph[spriteName]){ //already exist, delete old value
        qDebug()<<" this element already exist";
        delete objectGraph[spriteName];
        objectGraph.remove(spriteName);
    }
    objectGraph.insert(QString(spriteName), new AnimatableSpriteItem(0));
    objectGraph[QString(spriteName)]->setName(spriteName);
    objectGraph[QString(spriteName)]->setSpritePixmap(*spritePixmap);
    qDebug()<<"spritemanager.cpp : added image to bank";
    qDebug()<<"spritemanager.cpp >> Total Elements : "<<objectGraph.size();

    qDebug()<<">>>>>>>>(spriteManager.cpp) Now updating the current frame again (need attention)";

    qDebug()<<" *****  removing items first \n";

    //emit signal to update the frame so it can scan entire object graph again
    //FrameManager::getInstance()->getCurrentActiveFrame()->addFrameItem(objectGraph[spriteName], spriteName);
    //commented out above line since now all frame get data from spriteBank instead of saving local data

    delete spriteEditorDialog;
    delete spritePixmap;

    qDebug()<<" (spriteManager.cpp) setting frame to : "<<FrameManager::getInstance()->getCurrentActiveFrameByID();
    emit FrameManager::getInstance()->setNewActiveFrame(FrameManager::getInstance()->getCurrentActiveFrame());
}

void SpriteManager::removeFromBank(const QString &spriteName)
{
    if(objectGraph[spriteName]){
        delete objectGraph[spriteName];
        objectGraph.remove(spriteName);
    }
}
