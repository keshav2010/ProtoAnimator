#include "spritemanager.h"

//parent : manager
SpriteManager::SpriteManager(QObject *parent) : QObject(parent)
{

    connect(this, SIGNAL(addSprite(QString)), this, SLOT(addSpriteObject(QString)));

}

SpriteManager::~SpriteManager()
{
    delete spritePixmap;
}

Animatable* SpriteManager::addSpriteObject(const QString &imagePath)
{
    if(spritePixmap!=0)
        delete spritePixmap;

    spritePixmap = new QPixmap(imagePath);
    spritePixmap->load(imagePath);
    spriteEditorDialog.editPixmap(spritePixmap);
    spriteEditorDialog.show();
}
