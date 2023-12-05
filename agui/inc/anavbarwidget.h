/*
 * @Author: weick
 * @Date: 2023-12-05 22:52:40
 * @Last Modified by:   weick
 * @Last Modified time: 2023-12-05 22:52:40
 */

#pragma once
#include "agui_global.h"
#include "abasewidget.h"
#include "aicontextwidget.h"
#include <QMap>

class AGUI_EXPORT ANavbarWidget : public ABaseWidget {
    Q_OBJECT
public:
    ANavbarWidget(QMap<int, QVariantList> data, QWidget *parent = 0);
    ~ANavbarWidget();

Q_SIGNALS:
    void sigClicked(int index);

protected:
    void createUi() override;
    void changeLanguage() override;
    void sigConnect() override;

private:
    void exclusive(AIconTextWidget *widget);

private:
    // QVariantList: icon text
    QMap<int, QVariantList> m_Data;
};
