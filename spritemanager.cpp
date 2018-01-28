#include "spritemanager.h"
#include "manager.h"
//parent : manager
SpriteManager::SpriteManager(QObject *parent) : QObject(parent)
{
    spritePixmap = new QPixmap;
    spriteEditorDialog = new SpritePropertyEditorDialog(spritePixmap);

    connect(this, SIGNAL(addSprite(QString)), this, SLOT(addSpriteObject(QString)));

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
}
