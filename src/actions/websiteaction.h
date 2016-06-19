#ifndef WEBSITEACTION_H
#define WEBSITEACTION_H

#include "action.h"

class WebsiteAction : public Action
{
public:
    WebsiteAction();

    virtual void launch() const;
    virtual QIcon getIcon() const;
    virtual QString getText() const;
    virtual QString getFormattedText() const;
    virtual Kind getKind() const;

    inline void setUrl(QUrl url)
    {
        m_url = url;
    }

private:
    QUrl m_url;
};

#endif // WEBSITEACTION_H
