#include "userinterface.h"
#include <QQuickImageProvider>
#include <QQmlContext>
#include <QQuickItem>
#include <QTimer>
#include <QPropertyAnimation>
#include "actionsprovider.h"

UserInterface::UserInterface(QWidget *parent) :
    QQuickWidget(parent)
{
    setWindowOpacity(0);
    setResizeMode(QQuickWidget::SizeRootObjectToView);

    // Sharing some data and methods between C++ and QML parts
    m_engine.rootContext()->setContextProperty("userInterface", this);
}

void UserInterface::addImageProvider(QString name, QQuickImageProvider *provider)
{
    m_engine.addImageProvider(QLatin1String(name.toLatin1()), provider);
}

void UserInterface::setActionProvider(ActionsProvider *actionsProvider)
{
    m_actionsProvider = actionsProvider;
    m_engine.rootContext()->setContextProperty("actionsModel", m_actionsProvider->getModel());
}

void UserInterface::show()
{
    if (!m_isLoaded) {
        loadInterface();
        m_isLoaded = true;
    }

    QMetaObject::invokeMethod(rootObject(), "showFullScreen");
}

void UserInterface::hide()
{
    qobject_cast<QQuickWindow*>(rootObject())->grabWindow().save("2.png");
    QMetaObject::invokeMethod(rootObject(), "hide");
}

void UserInterface::loadInterface()
{
    m_engine.load(m_interfaceSource);

    QQuickItem *searchField = rootObject()->findChild<QQuickItem*>("searchField");
    Q_ASSERT(searchField != nullptr);
    connect(searchField, SIGNAL(input(QString)), m_actionsProvider, SLOT(requestPossibleActions(QString)));

    QQuickItem *completer = rootObject()->findChild<QQuickItem*>("completer");
    Q_ASSERT(completer != nullptr);
    connect(completer, SIGNAL(launchAction(int)), SLOT(launchAction(int)));
}

void UserInterface::launchAction(int actionId)
{
    Action::byId(actionId)->launch();
}

QObject *UserInterface::rootObject()
{
    Q_ASSERT(m_engine.rootObjects().length() == 1);
    return m_engine.rootObjects().first();
}
