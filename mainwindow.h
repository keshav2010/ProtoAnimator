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
    QStatusBar *mStatusBar;

    //Actions
    QAction *actionLoadSprite;

    //essential Widgets and Objects
    QToolBar *mainToolBar;

    //Contains tool to alter content of Scene
    ServiceDockWidget *serviceWidget;

    //Contains tools for handling animation and multiple frames
    TimelineDockWidget *timelineWidget;
    // testing only
    QDockWidget *sampleRight;

    void setupToolBar();//helper
};

#endif // MAINWINDOW_H
