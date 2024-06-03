/*
 * @Author: weick 
 * @Date: 2024-06-03 07:30:58 
 * @Last Modified by: weick
 * @Last Modified time: 2024-06-03 07:58:07
 */

#pragma once
#include "../awidget/inc/alabel.h"
#include "../awidget/inc/astackedwidget.h"
#include "../agui/inc/abasewidget.h"
#include "../agui/inc/atopbar.h"
#include "../agui/inc/aimportguide.h"
#include "imageerasefilelistview.h"
#include "imageerasepreviewview.h"
#include "imageerasesettingview.h"

namespace imageerase {
class ImageEraseWindow : public ABaseWidget {
    Q_OBJECT
public:
    explicit ImageEraseWindow(QWidget *parent = nullptr);
    ~ImageEraseWindow();
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
    AImportGuide *import_guide_ = nullptr;
    ImageEraseFileListView *file_list_view_ = nullptr;
    ImageErasePreviewView *preview_view_ = nullptr;
    ImageEraseSettingView *setting_view_ = nullptr;
};
} // namespace imageedit