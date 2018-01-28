#ifndef MANAGER_H
#define MANAGER_H

#include <QObject>
#include "spritemanager.h"
#include "framemanager.h"
/*
 * Manager plays the central role as it manages both
 * frame manager data (AKA FrameBank) as well as sprite manager data (AKA SpriteBank) and also establish
 * communication between both these data banks that store frames and sprites respectively.
 *
 * Manager thus acts as an interface and UI based classes (such as framesEditor, MainWindow, etc)
 * will thus access data from either of banks via this Manager class
 *
 * ONLY SINGLE-INSTANCE OF MANAGER CLASS CAN EXISTS (singleton pattern included)
 */
class Manager : public QObject
{
    Q_OBJECT
public:
    ~Manager();
    static Manager *getInstance();//explicit Manager(QObject *parent = nullptr);
    static void setParent(QObject *parent=0);
    static QObject *objectParent;

signals:
    void addSpriteToImageBank(const QString &spritePath);
    void addFrameToFrameBank();
    void addSpriteToImageBankAsObject(const AnimatableSpriteItem *objectData);

public slots:

private:
    static Manager *manager;
    static bool isAlreadyExist;

    explicit Manager(QObject *parent = 0);//singleton
    FrameManager *frameManager;
    SpriteManager *spriteManager;
};

#endif // MANAGER_H
