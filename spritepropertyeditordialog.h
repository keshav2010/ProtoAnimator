#ifndef SPRITEPROPERTYEDITORDIALOG_H
#define SPRITEPROPERTYEDITORDIALOG_H

#include <QDialog>
#include<QImage>
#include "spritepropertyeditordialog.h"
#include"animatable.h"
#include"animatablespriteitem.h"
#include<QDebug>
namespace Ui {
class SpritePropertyEditorDialog;
}

class SpritePropertyEditorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SpritePropertyEditorDialog(QPixmap *&sprite);
    ~SpritePropertyEditorDialog();
    AnimatableSpriteItem *animObject;
    QPixmap *originalSpritePixmap;
    QPixmap tempSpritePixmap;

public slots:
    void buildObject();
    void updateScene();
    void updateScaleUI();
    void updatePixmap();

private:
    int width, height;
    Ui::SpritePropertyEditorDialog *ui;
};

#endif // SPRITEPROPERTYEDITORDIALOG_H
