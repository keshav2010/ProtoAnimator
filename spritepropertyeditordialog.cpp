#include "spritepropertyeditordialog.h"
#include "ui_spritepropertyeditordialog.h"
#include "spritemanager.h"
SpritePropertyEditorDialog::SpritePropertyEditorDialog(QPixmap *&sprite) :
    ui(new Ui::SpritePropertyEditorDialog),
    height(0),
    width(0)
{

    ui->setupUi(this);
    originalSpritePixmap = sprite;
    tempSpritePixmap = *sprite;

    ui->graphicsView->setScene(new QGraphicsScene(ui->graphicsView));
    if(!tempSpritePixmap.isNull())
        ui->graphicsView->scene()->addPixmap(tempSpritePixmap);
    ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);


    connect(ui->graphicsView->scene(), SIGNAL(changed(QList<QRectF>)), this, SLOT(updateScene()));
    connect(this,SIGNAL(accepted()), SpriteManager::getInstance() , SLOT(addToBank()));


    updateScaleUI();

    connect(ui->spinBox_height, SIGNAL(valueChanged(int)), this, SLOT(updateScene()));
    connect(ui->spinBox_width, SIGNAL(valueChanged(int)), this, SLOT(updateScene()));
    //connect(this, SIGNAL(accepted()), this, SLOT(updatePixmap()));
}

SpritePropertyEditorDialog::~SpritePropertyEditorDialog()
{
    delete ui;
    qDebug()<<" cleared SPRITEPROPERTYEDITOR";
}
/*
void SpritePropertyEditorDialog::editPixmap(QPixmap *&sprite)
{
    ui->graphicsView->scene()->clear();
    originalSpritePixmap = sprite;
    tempSpritePixmap = *sprite;
    ui->graphicsView->scene()->addPixmap(tempSpritePixmap);

    emit ui->spinBox_height->valueChanged(tempSpritePixmap.height());
    emit ui->spinBox_width->valueChanged(tempSpritePixmap.width());

}
*/

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

    //Scene will be updated by UI, it will never reflect back to UI components
    qDebug()<<" scene updated";
}

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

QString SpritePropertyEditorDialog::updatePixmap()
{
    if(ui->input_objectName->text().length() == 0){
        *originalSpritePixmap = QPixmap(); //construct a null pixmap
        return QString();
    }
    originalSpritePixmap->swap(tempSpritePixmap);
    return QString(ui->input_objectName->text().trimmed());//return name
}
