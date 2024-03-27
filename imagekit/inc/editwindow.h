/*
 * @Author: weick
 * @Date: 2024-03-23 10:56:22
 * @Last Modified by: weick
 * @Last Modified time: 2024-03-24 12:59:13
 */

#pragma once
#include "../awidget/inc/alabel.h"
#include "../agui/inc/abasewidget.h"
#include "../agui/inc/atopbar.h"
#include "editfilelistview.h"
#include "editpreviewview.h"
#include "editsettingview.h"

namespace imageedit {
class EditWindow : public ABaseWidget {
    Q_OBJECT
public:
    explicit EditWindow(QWidget *parent = nullptr);
    ~EditWindow();
    void changeFileListData(QList<Data> datas);

protected:
    void createUi() override;
    void changeLanguage() override;
    void sigConnect() override;
    void paintEvent(QPaintEvent *event) override;

private:
    ATopbar *topbar_ = 0;
    ALabel *logo_label_ = 0;
    ALabel *name_label_ = 0;
    EditFileListView *file_list_view_;
    EditPreviewView *preview_view_;
    EditSettingView *setting_view_;
};
} // namespace imageedit