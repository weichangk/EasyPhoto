#pragma once
#include "QtCore/qobject.h"

class LangMgr : public QObject
{
    Q_OBJECT
public:
    static LangMgr *getInstance();
    static void deleteInstance();
    void setLangBySystemLang();
    void changeLanguage(const QString &newLanguage);

Q_SIGNALS:
    void sigChangeLanguage();

private:
    LangMgr();
    ~LangMgr();
    LangMgr(const LangMgr &instance);
    const LangMgr &operator=(const LangMgr &instance);

private:
    static LangMgr *m_instance;
};
