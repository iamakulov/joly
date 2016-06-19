#include "calculationaction.h"

CalculationAction::CalculationAction()
    : Action()
{

}

/**
 * @brief Launches the application that is represented by this action.
 */
void CalculationAction::launch() const
{

}

/**
 * @brief Returns an icon that represents the action.
 */
QIcon CalculationAction::getIcon() const
{
    return QIcon(":/images/equals.png");
}

/**
 * @brief Returns a text that represents the action.
 */
QString CalculationAction::getText() const
{
    return m_result;
}

/**
 * @brief Returns a formatted text to display in GlobalLine completer.
 */
QString CalculationAction::getFormattedText() const
{
    return getText();
}

/**
 * @brief Returns a kind of the action.
 */
Action::Kind CalculationAction::getKind() const
{
    return Action::Kind::Kind_Calculation;
}
