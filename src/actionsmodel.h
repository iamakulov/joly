#ifndef ACTIONSMODEL_H
#define ACTIONSMODEL_H

#include <QAbstractListModel>
#include <QLinkedList>
#include "action.h"
#include "qmlactioniconprovider.h"

/**
 * @brief The ActionsModel class provides the model (in terms of Qt's Model-View-Delegate) for actions list.
 *
 * The model is non-editable and resizable.
 * Normally, there should be only one instance of the model, and it is provided by the ActionsProvider class.
 *
 * To be precise, this class isn't a model, it's rather something between the model and the view,
 * because it knows about the view structure and architecture
 * and adapts data retrieved from the actual model (ActionsProvider) for the view.
 */
class ActionsModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int count READ rowCount() NOTIFY countChanged)

public:
    enum ActionRoles {
        IdRole = Qt::UserRole + 1,
        TextRole,
        FormattedTextRole
    };

    explicit ActionsModel(QObject *parent = 0);

    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    void addSection(Action::Kind sectionKind, const QList<ActionPointer> &actions);
    void clear();

//    QIcon getIconForActionNumber(int actionNumber);

signals:
    void countChanged();

public slots:

protected:
    virtual QHash<int, QByteArray> roleNames() const override;

private /*variables*/:
    /* We use QLinkedList here instead of QList because inserting items to model
     * must happen much more ofter than getting an item in it,
     * and QLinkedList must give a performance improvement. */
    QLinkedList<ActionPointer> m_actions;    ///< List of all actions in the model
    QMap<int, int> m_sectionSizes;  ///< Sizes of sections in the model
};

#endif // ACTIONSMODEL_H
