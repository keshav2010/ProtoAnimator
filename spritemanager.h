#ifndef SPRITEMANAGER_H
#define SPRITEMANAGER_H

#include <QObject>
#include <QMap>
#include "animatable.h"
#include<QString>
#include<QImage>
#include<QPixmap>
#include<QImageReader>
#include<QDebug>
#include "spritepropertyeditordialog.h"
#include "animatablespriteitem.h"
class SpriteManager : public QObject
{
    Q_OBJECT
public:
    const QMap<QString, AnimatableSpriteItem*>* getObjectGraph();
    static void setObjectParent(QObject *parent=0);
    static QObject *objectParent;
    static SpriteManager* getInstance();

    ~SpriteManager();

signals:
    void addSprite(const QString &imagePath);

public slots:
    /*
     * loads an image from disk specified by path "imagePath"
     * and opens a image-editor dialog where user can input name for the image as well as
     * mark the center point over it, and thus returns it as an Object that can be inserted into
     * the objectGraph under the similar name.
     */
    void addSpriteObject(const QString &imagePath);

    void addToBank();
    void removeFromBank(const QString &spriteName);

private:

    static SpriteManager *spriteManager;
    static bool isAlreadyExist;

    explicit SpriteManager(QObject *parent = 0);

    QPixmap *spritePixmap;
    QMap<QString, AnimatableSpriteItem*> objectGraph;

    SpritePropertyEditorDialog *spriteEditorDialog;
};

#endif // SPRITEMANAGER_H
