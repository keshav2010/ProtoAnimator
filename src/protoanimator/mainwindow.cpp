#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QHBoxLayout>
#include<QPainter>
#include<QDebug>
#include<QToolBar>
#include <QFileDialog>
#include"sceneitemsdockwidget.h"
#include "timelineview.h"
#include "movieexportdialog.h"

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
    actionLoadSprite.setIcon(QIcon(":/icons/icon_loadSprite"));
    actionLoadSprite.setText(tr("Load Sprite"));

    actionExportVideo.setIcon(QIcon(":/icons/icon_exportVideo"));
    actionExportVideo.setText(tr("Export As Video"));

    // DockWidgets init.
    serviceWidget = new ServiceDockWidget(this);
    timelineWidget = new TimelineDockWidget(this);
    sceneItemWidget = new SceneItemsDockWidget(this);

    //main toolBar
    setupToolBar();

    //add components to main-Window in their respective field
    addDockWidget(Qt::LeftDockWidgetArea, serviceWidget);
    addDockWidget(Qt::BottomDockWidgetArea, timelineWidget);
    addDockWidget(Qt::RightDockWidgetArea,  sceneItemWidget);

    setCentralWidget(FramesEditor::getInstance());

    serviceWidget->setTimelineModel( timelineWidget->getTimelineView()->getModel());

    //connections for slot-signal
    QObject::connect(&actionExportVideo, &QAction::triggered,
                     this, &MainWindow::showMovieExportDialog);

    QObject::connect(this, &MainWindow::addSprite,
                     SpriteManager::getInstance(), &SpriteManager::addSpriteObject);

    QObject::connect(&actionLoadSprite, &QAction::triggered,
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
    mainToolBar->addAction(&actionExportVideo);
    mainToolBar->addAction(&actionLoadSprite);
    mainToolBar->addAction(ui->actionExit);
    addToolBar(mainToolBar);
}


//------LOT FUNCTIONS-----

void MainWindow::showSpriteSelector()
{
    const QString fileFilter = "Image Files (*.png *.jpg *jpeg *bmp)";

    QFileDialog spriteSelector(this);
    spriteSelector.setWindowTitle("Open Image");
    spriteSelector.setFileMode(QFileDialog::FileMode::ExistingFile);
    spriteSelector.setNameFilter(fileFilter);

    if(spriteSelector.exec()) //exec() will hold execution unless some value is returned (upon exiting the file browser)
    {
        QString fileName = spriteSelector.selectedFiles().at(0);
        qDebug()<<" Opened Image Browser "<<fileName;
        emit addSprite(fileName); //add selected file in sprite-bank
    }
}

void MainWindow::showMovieExportDialog()
{
    MovieExportDialog d;
    d.show();
    d.exec();
}
