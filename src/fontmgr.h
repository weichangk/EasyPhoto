#pragma once

class QString;
class FontMgr
{
public:
    static void setFontToApp(const QString &family, int pointSize);
    static void setFontFamilyToAppByFile(const QString &fileName);
};

