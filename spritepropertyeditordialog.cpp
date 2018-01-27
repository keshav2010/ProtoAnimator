#include "spritepropertyeditordialog.h"
#include "ui_spritepropertyeditordialog.h"

SpritePropertyEditorDialog::SpritePropertyEditorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SpritePropertyEditorDialog)
{

    ui->setupUi(this);
    ui->graphicsView->setScene(new QGraphicsScene(ui->graphicsView));
    ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);


    connect(ui->graphicsView->scene(), SIGNAL(changed(QList<QRectF>)), this, SLOT(updateSceneImage()));
    connect(this,SIGNAL(accepted()), this, SLOT(buildObject()));


    updateScaleUI();

    connect(ui->spinBox_height, SIGNAL(valueChanged(int)), this, SLOT(updateSceneImage()));
    connect(ui->spinBox_width, SIGNAL(valueChanged(int)), this, SLOT(updateSceneImage()));

}

SpritePropertyEditorDialog::~SpritePropertyEditorDialog()
{
    delete ui;
    qDebug()<<" cleared SPRITEPROPERTYEDITOR";
}

void SpritePropertyEditorDialog::editPixmap(QPixmap &sprite)
{
    spritePixmap = sprite;
    ui->graphicsView->scene()->addPixmap(spritePixmap);
    show();
}


//returns a pointer to AnimatableSpriteItem object with no-parent set on it, thus parent need to be set
//explicitly to avoid possible memory leak
//this problem can be easily avoided by implementing Singleton
//pattern for management classes like Manager, SpriteManager and FrameManager
void SpritePropertyEditorDialog::buildObject()
{
    if(ui->input_objectName->text().size() == 0 ||
            ui->spinBox_height->value()==0 ||
            ui->spinBox_width->value()==0){
        return;
    }
    animObject = new AnimatableSpriteItem();
    animObject->setPixmap(spritePixmap);
}

void SpritePropertyEditorDialog::updateSceneImage()
{
    height = ui->spinBox_height->value();
    width = ui->spinBox_width->value();

    spritePixmap = spritePixmap.scaled(width, height);
    updateScaleUI();
    ui->graphicsView->repaint();
    qDebug()<<" scene updated";
}

void SpritePropertyEditorDialog::updateScaleUI()
{
    height = spritePixmap.height();
    width = spritePixmap.width();

    ui->spinBox_width->setValue(width);
    ui->spinBox_height->setValue(height);
}
