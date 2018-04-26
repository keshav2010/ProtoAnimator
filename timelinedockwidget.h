#ifndef TIMELINEDOCKWIDGET_H
#define TIMELINEDOCKWIDGET_H
/*
 * TimelineDockWidget will obtain following information from frameManager
 * 1. Current Active Frame
 * 2. Total Number of Frames
 */
#include<QFrame>
#include<QHBoxLayout>
#include<QWidget>
#include<QVBoxLayout>
#include<QDockWidget>
#include<QPushButton>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QSpinBox>
#include<QAbstractListModel>
class TimelineDockWidget :  public QDockWidget
{
protected:
    //sub frames
    QFrame *timelineFrame;
    QFrame *animationControlFrame;
    //main dockWidget frame
    QFrame *mainFrame;
    QHBoxLayout *framesHLayout;


    QPushButton *btn_runAnimation;
    QPushButton *btn_pauseAnimation;
    QPushButton *btn_restartAnimation;
    QVBoxLayout *buttonsVLayout;

    QSpinBox *spinbox_frameSelector;
    QHBoxLayout *spinboxHLayout;

    QSpinBox *spinbox_frameRateSelector;

public slots:
    void runAnim(int startFromFrame = 0);
    void pauseAnim();
    void restartAnim();
    void updateFrameSelectorRange(int upperBoundOfRange);
signals:
    void pressedRunAnimation();
    void pressedPauseAnimation();
    void pressedRestartAnimation();

public:
    TimelineDockWidget(QWidget *parent);

};

//might move this to another seperate file along with the delegate
class TimelineModel : public QAbstractListModel
{
    Q_OBJECT
public:
    TimelineModel(QObject *parent = Q_NULLPTR);

    int rowCount(const QModelIndex &parent=QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    bool setData(const QModelIndex &index, const QVariant &value, int role);
    bool insertRows(int row, int count, const QModelIndex &parent);
    bool removeRows(int row, int count, const QModelIndex &parent);
    //source of data : frameManager's frameBank
};
#endif // TIMELINEDOCKWIDGET_H
