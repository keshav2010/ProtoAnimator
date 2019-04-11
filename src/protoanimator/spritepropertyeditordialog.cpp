#include "spritepropertyeditordialog.h"
#include "ui_spritepropertyeditordialog.h"
#include "spritemanager.h"
SpritePropertyEditorDialog::SpritePropertyEditorDialog(const QString &imagePath) :
    ui(new Ui::SpritePropertyEditorDialog),
    height(0),
    width(0)
{
    qDebug()<<"(SpritePropertyEditorDialog.cpp) constructor ";
    this->setAttribute(Qt::WA_DeleteOnClose);
    ui->setupUi(this);

    //the actual source
    originalSpritePixmap = new QPixmap(imagePath);

    //the one which is altered
    tempSpritePixmap = *originalSpritePixmap;

    ui->graphicsView->setScene(new QGraphicsScene(this));

    if(!tempSpritePixmap.isNull())
        ui->graphicsView->scene()->addPixmap(tempSpritePixmap);
    ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);

    QObject::connect(ui->graphicsView->scene(), &QGraphicsScene::changed, this, &SpritePropertyEditorDialog::updateScene);
    QObject::connect(this, &SpritePropertyEditorDialog::accepted, this, &SpritePropertyEditorDialog::saveSpriteToBank);//QObject::connect(this, &SpritePropertyEditorDialog::accepted, SpriteManager::getInstance(), &SpriteManager::addToBank);
    QObject::connect(ui->spinBox_height, SIGNAL(valueChanged(int)), this, SLOT(updateScene()));
    QObject::connect(ui->spinBox_width, SIGNAL(valueChanged(int)), this, SLOT(updateScene()));

    updateScaleUI();
}

SpritePropertyEditorDialog::~SpritePropertyEditorDialog()
{
    qDebug()<<"(~SpritePropertyEditor.cpp) : destructor call enter.";

    //NOTE : deleting this value, thus when the reference is passed on to each instance of
    //AnimatableSpriteItem, it should be initialized dynamically. (see saveSpriteToBank() fxn)
    if(originalSpritePixmap != nullptr){
        delete originalSpritePixmap;
        originalSpritePixmap= nullptr;
    }
    if(ui != nullptr){
        delete ui;
        ui=nullptr;
    }
    qDebug()<<"(~SpritePropertyEditor.cpp) : deleted ui, Exiting Destructor.";
}
void SpritePropertyEditorDialog::updateScene()
{
    if(height == ui->spinBox_height->value() && width == ui->spinBox_width->value()){
         return;
    }
    height = ui->spinBox_height->value();
    width = ui->spinBox_width->value();

    tempSpritePixmap = originalSpritePixmap->scaled(width, height);
    ui->graphicsView->scene()->clear();
    ui->graphicsView->scene()->addPixmap(tempSpritePixmap);
    ui->graphicsView->setSceneRect(tempSpritePixmap.rect());
}

//to reflect changes in image back into the Spinbox widgets
void SpritePropertyEditorDialog::updateScaleUI()
{
    if(tempSpritePixmap.isNull()){
        return;
    }

    height = tempSpritePixmap.height();
    width = tempSpritePixmap.width();

    ui->spinBox_width->setValue(width);
    ui->spinBox_height->setValue(height);
}

void SpritePropertyEditorDialog::saveSpriteToBank()
{
    //replace original by the new altered pixmap
    originalSpritePixmap->swap(tempSpritePixmap);
    SpriteManager::getInstance()->addToBank(originalSpritePixmap, ui->input_objectName->text().trimmed());
}
