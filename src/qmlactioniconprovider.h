#ifndef QMLACTIONICONPROVIDER_H
#define QMLACTIONICONPROVIDER_H

#include <QQuickImageProvider>

/**
 * @brief The QmlActionIconProvider class provides action icons for the QML part of the application.
 * For more details, see the documentation of the QQuickImageProvider class.
 */
class QmlActionIconProvider : public QQuickImageProvider
{
public:
    QmlActionIconProvider();

    virtual QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize);
};

#endif // QMLACTIONICONPROVIDER_H
