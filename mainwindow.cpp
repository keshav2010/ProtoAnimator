#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QHBoxLayout>
#include<QPainter>
#include<QDebug>
#include<QToolBar>
#include <QFileDialog>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    frameEditor(new FramesEditor(parent)),
    mStatusBar(new QStatusBar(this)),
    mainToolBar(new QToolBar("Tool Bar", this))
{


    ui->setupUi(this);
    Manager::setParent(this);

    setStatusBar(mStatusBar);

    //initialise all Actions here
    actionLoadSprite = new QAction(QIcon(":/icons/icon_loadSprite"),"Load Sprite",this);

    //additional DockWidgets init.
    serviceWidget = new ServiceDockWidget(this);
    sampleRight = new QDockWidget(this);

    //main toolBar setup
    setupToolBar();

    sampleRight->setFeatures(QDockWidget::DockWidgetMovable);

    //add components to main-Window in their respective field
    addDockWidget(Qt::LeftDockWidgetArea, serviceWidget);
    addDockWidget(Qt::RightDockWidgetArea, sampleRight);
    setCentralWidget(frameEditor);

    //connections for slot-signal
    connect(serviceWidget->getAddFrameButton(), SIGNAL(clicked(bool)), Manager::getInstance(), SIGNAL(addFrameToFrameBank()));
    connect(this, SIGNAL(addSprite(QString)), Manager::getInstance(), SIGNAL(addSpriteToImageBank(QString)));
    connect(actionLoadSprite, SIGNAL(triggered(bool)), this,SLOT(showSpriteSelector()));
    connect(ui->actionExit, SIGNAL(triggered(bool)), this, SLOT(close()));

}
MainWindow::~MainWindow()
{
    delete ui;
}

//helper functions
void MainWindow::setupToolBar()
{
    mainToolBar->addAction(actionLoadSprite);
    mainToolBar->addAction(ui->actionExit);
    addToolBar(mainToolBar);
}


//slots implemented below
void MainWindow::showSpriteSelector()
{
    const QString fileFilter = "Image Files (*.png *.jpg *jpeg *bmp)";

    QFileDialog spriteSelector(this);
    spriteSelector.setWindowTitle("Open Image");
    spriteSelector.setFileMode(QFileDialog::FileMode::ExistingFile);
    spriteSelector.setNameFilter(fileFilter);

    if(spriteSelector.exec()){
        qDebug()<<" Opened Image Browser";
        QString fileName = spriteSelector.selectedFiles().at(0);
        qDebug()<<fileName;
        emit addSprite(fileName); //add selected file in sprite-bank
    }
}
