#include "spritemanager.h"
#include "manager.h"
//parent : manager
SpriteManager::SpriteManager(QObject *parent) : QObject(parent)
{
    spritePixmap = new QPixmap;
    spriteEditorDialog = new SpritePropertyEditorDialog(spritePixmap);

    connect(this, SIGNAL(addSprite(QString)), this, SLOT(addSpriteObject(QString)));
    connect(spriteEditorDialog, SIGNAL(accepted()), this, SLOT(addToBank()));
}

SpriteManager::~SpriteManager()
{
    delete spritePixmap;
    delete spriteEditorDialog;
}

void SpriteManager::addSpriteObject(const QString &imagePath)
{

    spritePixmap->load(imagePath);
    spriteEditorDialog->show();
    spriteEditorDialog->updateScaleUI();
}

void SpriteManager::addToBank()
{
    QString spriteName = spriteEditorDialog->updatePixmap();
    if(spriteName.isEmpty())
        return;

    if(objectGraph[spriteName]){ //already exist, delete old value
        delete objectGraph[spriteName];
        objectGraph.remove(spriteName);
    }
    objectGraph[spriteName] = new AnimatableSpriteItem(0);
    objectGraph[spriteName]->setPixmap(*spritePixmap);
}

void SpriteManager::removeFromBank(const QString &spriteName)
{
    if(objectGraph[spriteName]){
        delete objectGraph[spriteName];
        objectGraph.remove(spriteName);
    }
}
