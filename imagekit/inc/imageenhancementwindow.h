/*
 * @Author: weick 
 * @Date: 2024-06-04 08:00:42 
 * @Last Modified by:   weick 
 * @Last Modified time: 2024-06-04 08:00:42 
 */

#pragma once
#include "../awidget/inc/alabel.h"
#include "../awidget/inc/astackedwidget.h"
#include "../agui/inc/abasewidget.h"
#include "../agui/inc/atopbar.h"
#include "../agui/inc/aimportguide.h"
#include "imageenhancementfilelistview.h"
#include "imageenhancementpreviewview.h"
#include "imageenhancementsettingview.h"

namespace imageenhancement {
class ImageEnhancementWindow : public ABaseWidget {
    Q_OBJECT
public:
    explicit ImageEnhancementWindow(QWidget *parent = nullptr);
    ~ImageEnhancementWindow();
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
    ImageEnhancementFileListView *file_list_view_ = nullptr;
    ImageEnhancementPreviewView *preview_view_ = nullptr;
    ImageEnhancementSettingView *setting_view_ = nullptr;
};
} // namespace imageenhancement