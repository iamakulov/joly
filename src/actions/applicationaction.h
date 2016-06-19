#ifndef APPLICATIONACTION_H
#define APPLICATIONACTION_H

#include "action.h"

/**
 * @brief The ApplicationAction class simulates the "launch application" action.
 * For detailed description for the class and uncommented methods, see the comment before Action class.
 */
class ApplicationAction : public Action
{
public:
    ApplicationAction();

    virtual void launch() const;
    virtual QIcon getIcon() const;
    virtual QString getText() const;
    virtual QString getFormattedText() const;
    virtual Kind getKind() const;

    inline void setInfo(const AppInfo &info)
    {
        m_info = info;
    }

private:
    AppInfo m_info;
};
#endif // APPLICATIONACTION_H
