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
    explicit SpritePropertyEditorDialog(QWidget *parent = 0);
    ~SpritePropertyEditorDialog();
    void editPixmap(QPixmap  &sprite);
    AnimatableSpriteItem *animObject;
    QPixmap spritePixmap;

public slots:
    void buildObject();
    void updateSceneImage();
    void updateScaleUI();

private:
    int width, height;
    Ui::SpritePropertyEditorDialog *ui;
};

#endif // SPRITEPROPERTYEDITORDIALOG_H
