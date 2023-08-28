#include "langmgr.h"
#include "qapplication.h"
#include "QtCore/qtranslator.h"
#include "QtCore/qlocale.h"

LangMgr* LangMgr::m_instance = new (std::nothrow) LangMgr();

LangMgr *LangMgr::getInstance()
{
    return m_instance;
}

void LangMgr::deleteInstance()
{
    if (m_instance)
    {
        delete m_instance;
        m_instance = nullptr;
    }
}

LangMgr::LangMgr()
{
}

LangMgr::~LangMgr()
{
}

void LangMgr::setLangBySystemLang()
{
    QTranslator translator;
    QLocale locale = QLocale::system();
    QString langCode = locale.name();
    if (translator.load(":/translations/app_" + langCode))
    {
        qApp->installTranslator(&translator);
    }
}

void LangMgr::changeLanguage(const QString &newLanguage)
{
    // 切换应用程序语言的逻辑
    // 发出多语言切换信号
    emit sigChangeLanguage();
}
