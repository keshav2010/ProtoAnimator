#include "spritemanager.h"

//parent : manager
SpriteManager::SpriteManager(QObject *parent) : QObject(parent)
{
    connect(this, SIGNAL(addSprite(QString)), this, SLOT(addSpriteObject(QString)));

}

Animatable* SpriteManager::addSpriteObject(const QString &imagePath)
{
    spritePixmap.load(imagePath);
    spriteEditorDialog.editPixmap(spritePixmap);
}
