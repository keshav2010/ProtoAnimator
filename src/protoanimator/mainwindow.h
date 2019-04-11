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
#include<QAction>
#include "timelinedockwidget.h"
#include "sceneitemsdockwidget.h"
#include "servicedockwidget.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();

signals:
    void addSprite(const QString &spritePath);
public slots:
    void showSpriteSelector();
    void showMovieExportDialog();

private:
    Ui::MainWindow *ui;
    QStatusBar *mStatusBar;

    //Actions
    QAction actionLoadSprite;
    QAction actionExportVideo;

    //essential Widgets and Objects
    QToolBar *mainToolBar;

    //Contains tool to alter content of Scene
    ServiceDockWidget *serviceWidget;

    //Contains tools for handling animation and multiple frames
    TimelineDockWidget *timelineWidget;

    SceneItemsDockWidget *sceneItemWidget;

    void setupToolBar();
};

#endif // MAINWINDOW_H
