#include "actionsmodel.h"
#include <QDebug>

template <typename T>
typename QLinkedList<T>::Iterator getIteratorAt(QLinkedList<T> &list, int index)
{
    auto it = list.begin();
    for (int i = 0; i < index && it != list.end(); ++i)
        ++it;

    return it;
}

template <typename T>
typename QLinkedList<T>::ConstIterator constGetIteratorAt(const QLinkedList<T> &list, int index)
{
    auto it = list.constBegin();
    for (int i = 0; i < index && it != list.constEnd(); ++i)
        ++it;

    return it;
}



ActionsModel::ActionsModel(QObject *parent) :
    QAbstractListModel(parent)
{
    connect(this, SIGNAL(rowsInserted(QModelIndex,int,int)), SIGNAL(countChanged()));
    connect(this, SIGNAL(rowsRemoved(QModelIndex,int,int)), SIGNAL(countChanged()));
}

/**
 * @brief Overrides QAbstractItemModel::data() method. See its documentation for more details.
 */
QVariant ActionsModel::data(const QModelIndex &index, int role) const
{
    // Checking for index validity
    int row = index.row();
    if (!( 0 <= row && row < rowCount() ))
        return QVariant();

    // Getting necessary action
    auto it = constGetIteratorAt(m_actions, row);
    Q_ASSERT(it != m_actions.constEnd());
    ActionPointer action = *it;

    // Returning the role
    if (role == IdRole)
        return action->id();
    else if (role == TextRole)
        return action->getText();
    else if (role == FormattedTextRole)
        return action->getFormattedText();
    else
        return QVariant();
}

/**
 * @brief Overrides QAbstractItemModel::rowCount() method. See its documentation for more details.
 */
int ActionsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_actions.size();
}

/**
 * @brief Adds a new section of actions to the model.
 * @param sectionKind The kind of the section.
 * @param actions Actions in the section.
 *
 * The section is being inserted not to the end of all previous actions, but according to its order in Action::Kind enum.
 * This means that, for example, the Action::Kind_FileSystemEntry section will always be inserted after Action::Kind_Application section,
 * or into the beginning if Action::Kind_Application section is not present.
 */
void ActionsModel::addSection(Action::Kind sectionKind, const QList<ActionPointer> &actions)
{
    m_sectionSizes[sectionKind] = actions.length();

    // Sum up sizes of all previous sections
    int previousCount = 0;
    for (int currentSection = 0; currentSection != sectionKind; ++currentSection) {
        previousCount += m_sectionSizes[currentSection];
    }

    int startingPosition = previousCount;
    int finishingPosition = previousCount + actions.length() - 1;

    // Call beginInsertRows() with necessary positions
    beginInsertRows(QModelIndex(), startingPosition, finishingPosition);

    // Insert to the list at necessary position
    auto insertBefore = getIteratorAt(m_actions, startingPosition);
    if (insertBefore == m_actions.end()) {

        // ...Appending all elements
        for (auto action : actions) {
            m_actions.append(action);
        }

    }
    else {

        // ...Inserting element-by-element to specified position
        for (auto action : actions) {
            // We save iterator for inserted element...
            auto insertedIterator = m_actions.insert(insertBefore, action);
            // ...and, later, insert after it, i.e. before the element following it.
            insertBefore = insertedIterator + 1;
        }

    }

    endInsertRows();
}

/**
 * @brief Removes all actions from the model.
 */
void ActionsModel::clear()
{
    if (m_actions.size() == 0)
        return;

    beginRemoveRows(QModelIndex(), 0, m_actions.size() - 1);

    while (!m_actions.isEmpty())
        delete m_actions.takeLast();

    m_sectionSizes.clear();

    endRemoveRows();
}

/**
 * @brief Overrides QAbstractItemModel::roleNames() method. See its documentation for more details.
 *
 * The method is used in the view (QML/QtQuick part of the application).
 */
QHash<int, QByteArray> ActionsModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[IdRole] = "actionId";
    roles[TextRole] = "text";
    roles[FormattedTextRole] = "formattedText";
    return roles;
}
