#ifndef QMLBACKGROUNDPROVIDER_H
#define QMLBACKGROUNDPROVIDER_H

#include <QQuickImageProvider>
#include <QPixmap>

/**
 * @brief The QmlBackgroundProvider class provides a screenshot of the whole desktop without Joly.
 * It is achieved by taking a screenshot before showing the interface.
 * For more details, see the documentation of the QQuickImageProvider class.
 */
class QmlBackgroundProvider : public QQuickImageProvider
{
public:
    QmlBackgroundProvider();

    virtual QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize);

private slots:
    void takeScreenshot();

private /*variables*/:
    QImage m_screenshot;
    QSize m_size;
};

#endif // QMLBACKGROUNDPROVIDER_H
