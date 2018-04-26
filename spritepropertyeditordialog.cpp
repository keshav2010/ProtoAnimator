#include "spritepropertyeditordialog.h"
#include "ui_spritepropertyeditordialog.h"
#include "spritemanager.h"
SpritePropertyEditorDialog::SpritePropertyEditorDialog(const QString &imagePath) :
    ui(new Ui::SpritePropertyEditorDialog),
    height(0),
    width(0)
{
    qDebug()<<"********* SPRITEPROPERTYEDITOR Initialized";
    this->setAttribute(Qt::WA_DeleteOnClose);
    ui->setupUi(this);
    originalSpritePixmap = new QPixmap(imagePath);//the actual source
    tempSpritePixmap = *originalSpritePixmap;//the one which is altered

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
    delete originalSpritePixmap;
    delete ui;
    qDebug()<<"spritePropertyEditorDialog.cpp :  cleared SPRITEPROPERTYEDITOR";
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
