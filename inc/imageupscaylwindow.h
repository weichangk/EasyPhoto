/*
 * @Author: weick 
 * @Date: 2024-06-04 08:00:42 
 * @Last Modified by: weick
 * @Last Modified time: 2024-07-23 07:43:25
 */

#pragma once
#include "../awidget/inc/apushbutton.h"
#include "../awidget/inc/alabel.h"
#include "../awidget/inc/astackedwidget.h"
#include "../agui/inc/abasewidget.h"
#include "../agui/inc/atopbar.h"
#include "../agui/inc/aimportguide.h"
#include "imageupscaylfilelistview.h"
#include "imageupscaylpreviewview.h"
#include "imageupscaylsettingview.h"

namespace imageupscayl {
class ImageUpscaylWindow : public ABaseWidget {
    Q_OBJECT
public:
    explicit ImageUpscaylWindow(QWidget *parent = nullptr);
    ~ImageUpscaylWindow();
    void changeFileListData(QList<Data> datas);
    void setFileListCurrentIndex(int index);
    int fileListCurrentIndex();
    
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
    AStackedWidget *stacked_widget_ = nullptr;
    AStackedWidget *left_stacked_widget_ = nullptr;
    AImportGuide *import_guide_ = nullptr;
    APushButton *setting_button_ = nullptr;
    APushButton *file_list_button_ = nullptr;
    APushButton *upscayl_button_ = nullptr;
    ImageUpscaylSettingView *setting_view_ = nullptr;
    ImageUpscaylFileListView *file_list_view_ = nullptr;
    ImageUpscaylPreviewView *preview_view_ = nullptr;
};
} // namespace imageupscayl