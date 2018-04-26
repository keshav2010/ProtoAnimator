#ifndef MANAGER_H
#define MANAGER_H

#include <QObject>
#include "spritemanager.h"
#include "framemanager.h"

class Manager : public QObject
{
    Q_OBJECT
public:
    ~Manager();
    static Manager *getInstance();//explicit Manager(QObject *parent = nullptr);
    static void setParent(QObject *parent=0);
    static QObject *objectParent;

signals:
    void addFrameToFrameBank();

public slots:


private:
    static Manager *manager;
    static bool isAlreadyExist;

    explicit Manager(QObject *parent = 0);//singleton
};

#endif // MANAGER_H
