/*
 * @Author: weick
 * @Date: 2024-03-23 10:56:22
 * @Last Modified by: weick
 * @Last Modified time: 2024-04-12 07:58:04
 */

#pragma once
#include "../awidget/inc/alabel.h"
#include "../awidget/inc/astackedlayout.h"
#include "../agui/inc/abasewidget.h"
#include "../agui/inc/atopbar.h"
#include "../agui/inc/aimportguide.h"
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
    void moveEvent(QMoveEvent *event) override;

private:
    ATopbar *topbar_ = nullptr;
    ALabel *logo_label_ = nullptr;
    ALabel *name_label_ = nullptr;
    AStackedLayout *stacked_layout_ = nullptr;
    AImportGuide *import_guide_ = nullptr;
    EditFileListView *file_list_view_ = nullptr;
    EditPreviewView *preview_view_ = nullptr;
    EditSettingView *setting_view_ = nullptr;
};
} // namespace imageedit