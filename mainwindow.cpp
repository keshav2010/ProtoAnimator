#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QHBoxLayout>
#include<QPainter>
#include<QDebug>
#include<QToolBar>
#include <QFileDialog>

#include "timelineview.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mStatusBar(new QStatusBar(this)),
    mainToolBar(new QToolBar("Tool Bar", this))
{

    qDebug()<<"(MainWindow.cpp) constructor";
    ui->setupUi(this);

    FramesEditor::setParent(this);
    SpriteManager::setObjectParent(this);
    FrameManager::setObjectParent(this);


    setStatusBar(mStatusBar);

    //initialise all Actions here
    actionLoadSprite = new QAction(QIcon(":/icons/icon_loadSprite"),"Load Sprite",this);

    // DockWidgets init.
    serviceWidget = new ServiceDockWidget(this);
    sampleRight = new QDockWidget(this);
    timelineWidget = new TimelineDockWidget(this);

    //main toolBar
    setupToolBar();

    sampleRight->setFeatures(QDockWidget::DockWidgetMovable);

    //add components to main-Window in their respective field
    addDockWidget(Qt::LeftDockWidgetArea, serviceWidget);
    addDockWidget(Qt::RightDockWidgetArea, sampleRight);
    addDockWidget(Qt::BottomDockWidgetArea, timelineWidget);

    setCentralWidget(FramesEditor::getInstance());

    serviceWidget->setTimelineModel( timelineWidget->getTimelineView()->getModel());

    //connections for slot-signal
    QObject::connect(this, &MainWindow::addSprite,
                     SpriteManager::getInstance(), &SpriteManager::addSpriteObject);

    QObject::connect(actionLoadSprite, &QAction::triggered,
                     this, &MainWindow::showSpriteSelector);

    QObject::connect(ui->actionExit, &QAction::triggered,
                     this, &MainWindow::close);
}
MainWindow::~MainWindow()
{
    qDebug()<<"(~MainWindow.cpp) : Destructor called";
    if(ui != nullptr){
        delete ui;
        ui=nullptr;
    }
    qDebug()<<"  (~MainWindow.cpp) : ui deleted !";
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
