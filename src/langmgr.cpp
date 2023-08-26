#include "langmgr.h"
#include "qapplication.h"
#include "QtCore"

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
