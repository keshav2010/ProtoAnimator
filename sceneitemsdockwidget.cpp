#include "sceneitemsdockwidget.h"
#include<QDebug>
#include<QItemDelegate>
SceneItemsDockWidget::SceneItemsDockWidget(QWidget *parent)
{

    this->setFeatures(QDockWidget::DockWidgetMovable);
    setWindowTitle(tr("Frame Items"));

    this->frameWidget = new QFrame(this);
    this->frameWidget->setMinimumWidth(150);

    sceneItemListView.setModel(&listModel);
    viewLayout.addWidget(&sceneItemListView);

    frameWidget->setLayout(&viewLayout);
    setWidget(frameWidget);
}

SceneItemsDockWidget::~SceneItemsDockWidget()
{
}

ItemListModel::ItemListModel(QObject *parent):
    QAbstractListModel(parent)
{

}

int ItemListModel::rowCount(const QModelIndex &parent) const
{
    return 2;
}

QVariant ItemListModel::data(const QModelIndex &index, int role) const
{
    if(role==Qt::DisplayRole)
        return QString("sample");
    return QVariant();
}

ItemListModel::~ItemListModel()
{

}
