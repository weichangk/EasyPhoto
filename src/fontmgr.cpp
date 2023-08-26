#include "fontmgr.h"
#include "qapplication.h"
#include "QtGui"
#include "QtCore"

void FontMgr::setFontToApp(const QString &family, int pointSize)
{
    QFont font(family, pointSize);
    qApp->setFont(font);
}

void FontMgr::setFontFamilyToAppByFile(const QString &fileName)
{
    int fontId = QFontDatabase::addApplicationFont(fileName);
    QStringList fontList = QFontDatabase::applicationFontFamilies(fontId);
    Q_ASSERT(!fontList.isEmpty());
    QFont f;
    f.setFamily(fontList[0]);
    qApp->setFont(f);
}
