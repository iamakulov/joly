#include "qmlbackgroundprovider.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QScreen>

QmlBackgroundProvider::QmlBackgroundProvider() :
    QQuickImageProvider(QQmlImageProviderBase::Image)
{
    takeScreenshot();
}

/**
 * @brief Returns a desktop screenshot taken before.
 * @param id Unused.
 * @param size [output] The size of the returned image.
 * @param requestedSize Unused.
 */
QImage QmlBackgroundProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
    Q_UNUSED(id);
    Q_UNUSED(requestedSize);

    if (size)
        *size = m_size;

    return m_screenshot;
}

/**
 * @brief Takes a screenshot of the desktop and saves it and its size.
 */
void QmlBackgroundProvider::takeScreenshot()
{
    QScreen *firstScreen = QApplication::screens().first();
    WId desktopWindowId = QApplication::desktop()->winId();

    m_screenshot = firstScreen->grabWindow(desktopWindowId).toImage();
    m_size = m_screenshot.size();
}
