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


//parent : manager
SpriteManager::SpriteManager(QObject *parent)
    : QObject(parent)
{
    spritePixmap=0;//    spritePixmap = new QPixmap;
    spriteEditorDialog=0; //    spriteEditorDialog = new SpritePropertyEditorDialog(spritePixmap);

    connect(this, SIGNAL(addSprite(QString)), this, SLOT(addSpriteObject(QString)));
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
    delete spriteManager;
}

void SpriteManager::addSpriteObject(const QString &imagePath)
{
    spritePixmap = new QPixmap(imagePath);
    spriteEditorDialog = new SpritePropertyEditorDialog(spritePixmap);
    spriteEditorDialog->show();
    spriteEditorDialog->updateScaleUI();
}

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
    objectGraph[QString(spriteName)]->setSpritePixmap(*spritePixmap);
    qDebug()<<"added image to bank";
    qDebug()<<" >> Total Elements : "<<objectGraph.size();
    delete spriteEditorDialog;
    delete spritePixmap;
}

void SpriteManager::removeFromBank(const QString &spriteName)
{
    if(objectGraph[spriteName]){
        delete objectGraph[spriteName];
        objectGraph.remove(spriteName);
    }
}
