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
    explicit SpritePropertyEditorDialog(const QString &imagePath);
    ~SpritePropertyEditorDialog();
    AnimatableSpriteItem *animObject;
    QPixmap *originalSpritePixmap;
    QPixmap tempSpritePixmap;

public slots:
    void updateScene();
    void updateScaleUI();
    void saveSpriteToBank();

private:
    Ui::SpritePropertyEditorDialog *ui;
    int width, height;

};

#endif // SPRITEPROPERTYEDITORDIALOG_H
