#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <QQmlApplicationEngine>

class ActionsProvider;
class QQuickImageProvider;

class UserInterface : public QObject
{
    Q_OBJECT
public:
    explicit UserInterface(QObject *parent = nullptr);

    void addImageProvider(QString name, QQuickImageProvider *provider);
    void setActionsProvider(ActionsProvider *actionsProvider);

public slots:
    void show();
    void hide();

private slots:
    void loadInterface();
    void launchAction(int actionId);

private /*methods*/:
    QObject *rootObject();

private /*variables*/:
    ActionsProvider *m_actionsProvider;
    QQmlApplicationEngine m_engine;

    bool m_isLoaded = false;
    const QString m_interfaceSource = "../../Joly/src/ui/Root.qml";
};

#endif // USERINTERFACE_H
