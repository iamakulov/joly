#include "qmlactioniconprovider.h"
#include <QDebug>
#include "actionsmodel.h"

QmlActionIconProvider::QmlActionIconProvider() :
    QQuickImageProvider(QQmlImageProviderBase::Pixmap)
{
}

/**
 * @brief Returns an action icon converted to QPixmap with the size #iconSize.
 * @param id String representation of action id.
 * @param size [output] Size of returned image.
 * @param requestedSize Not used. Usually is QSize(-1, -1).
 * @return Converted action icon.
 */
QPixmap QmlActionIconProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
{
    Q_UNUSED(requestedSize);

    int iconSize = 64;
    if (size)
        *size = QSize(iconSize, iconSize);

    bool conversionWasOk = true;
    int actionId = id.toULongLong(&conversionWasOk);
    Q_ASSERT(conversionWasOk);

    ActionPointer action = Action::byId(actionId);

    QPixmap pixmap = action->getIcon().pixmap(*size);
    return pixmap;
}
