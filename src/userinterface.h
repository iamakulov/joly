#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <QQuickWidget>
#include <QQmlApplicationEngine>

class ActionsProvider;
class QQuickImageProvider;

class UserInterface : public QQuickWidget
{
    Q_OBJECT
public:
    explicit UserInterface(QWidget *parent = 0);

    void addImageProvider(QString name, QQuickImageProvider *provider);
    void setActionProvider(ActionsProvider *actionsProvider);

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
    const QString m_interfaceSource = "../../Joly/src/ui/Window.qml";
};

#endif // USERINTERFACE_H
