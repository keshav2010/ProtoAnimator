#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QPushButton>
#include "animatable.h"
#include "frameseditor.h"
#include "frame.h"
#include <QPaintDevice>
#include<QHBoxLayout>
#include<QDockWidget>
#include<QVBoxLayout>
#include "servicedockwidget.h"
#include "timelinedockwidget.h"
#include "manager.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
signals:
    void addSprite(const QString &spritePath);
public slots:
    void showSpriteSelector();

private:
    Ui::MainWindow *ui;

    //The Manager : instance not required anymore, singleton pattern applied to Manager class
    //Manager *manager;

    //Actions
    QAction *actionLoadSprite;

    //essential Widgets and Objects
    QToolBar *mainToolBar;

    //FramesEditor *frameEditor;

    //Dock Widgets
    ServiceDockWidget *serviceWidget; //Contains tool to alter content of Scene
    TimelineDockWidget *timelineWidget; //Contains tools for handling animation and multiple frames
    QDockWidget *sampleRight;// testing only
    QStatusBar *mStatusBar;
    //helper functions
    void setupToolBar();
};

#endif // MAINWINDOW_H
