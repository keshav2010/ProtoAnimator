#include "spritepropertyeditordialog.h"
#include "ui_spritepropertyeditordialog.h"

SpritePropertyEditorDialog::SpritePropertyEditorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SpritePropertyEditorDialog)
{

    ui->setupUi(this);
    ui->graphicsView->setScene(new QGraphicsScene(ui->graphicsView));
    ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);


    connect(ui->graphicsView->scene(), SIGNAL(changed(QList<QRectF>)), this, SLOT(updateScene()));
    connect(this,SIGNAL(accepted()), this, SLOT(buildObject()));


    updateScaleUI();

    connect(ui->spinBox_height, SIGNAL(valueChanged(int)), this, SLOT(updateScene()));
    connect(ui->spinBox_width, SIGNAL(valueChanged(int)), this, SLOT(updateScene()));
    connect(this, SIGNAL(accepted()), this, SLOT(updatePixmap()));
}

SpritePropertyEditorDialog::~SpritePropertyEditorDialog()
{
    delete ui;
    qDebug()<<" cleared SPRITEPROPERTYEDITOR";
}

void SpritePropertyEditorDialog::editPixmap(QPixmap *&sprite)
{
    ui->graphicsView->scene()->clear();
    originalSpritePixmap = sprite;
    tempSpritePixmap = *sprite;
    ui->graphicsView->scene()->addPixmap(tempSpritePixmap);

    emit ui->spinBox_height->valueChanged(tempSpritePixmap.height());
    emit ui->spinBox_width->valueChanged(tempSpritePixmap.width());

}


void SpritePropertyEditorDialog::buildObject()
{
    if(ui->input_objectName->text().size() == 0 ||
            ui->spinBox_height->value()==0 ||
            ui->spinBox_width->value()==0){
        return;
    }
    //animObject = new AnimatableSpriteItem();
    //animObject->setPixmap(*spritePixmap);
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

    //Scene will be updated by UI, it will never reflect back to UI components
    qDebug()<<" scene updated";
}

void SpritePropertyEditorDialog::updateScaleUI()
{
    height = tempSpritePixmap.height();
    width = tempSpritePixmap.width();

    ui->spinBox_width->setValue(width);
    ui->spinBox_height->setValue(height);
}

void SpritePropertyEditorDialog::updatePixmap()
{

}
