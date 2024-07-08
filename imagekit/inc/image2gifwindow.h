/*
 * @Author: weick 
 * @Date: 2024-06-03 07:30:58 
 * @Last Modified by: weick
 * @Last Modified time: 2024-07-06 16:37:27
 */

#pragma once
#include "../awidget/inc/alabel.h"
#include "../awidget/inc/apushbutton.h"
#include "../awidget/inc/astackedwidget.h"
#include "../agui/inc/abasewidget.h"
#include "../agui/inc/atopbar.h"
#include "../agui/inc/aimportguide.h"
#include "image2giffilelistview.h"
#include "image2gifpreviewview.h"
#include "image2gifsettingview.h"

namespace image2gif {
class Image2GifWindow : public ABaseWidget {
    Q_OBJECT
public:
    explicit Image2GifWindow(QWidget *parent = nullptr);
    ~Image2GifWindow();
    void changeFileListData(QList<Data> datas);
    void setFileListCurrentIndex(int index);
    int fileListCurrentIndex();
    
protected:
    void createUi() override;
    void changeLanguage() override;
    void sigConnect() override;
    void paintEvent(QPaintEvent *event) override;
    void moveEvent(QMoveEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    ATopbar *topbar_ = nullptr;
    ALabel *logo_label_ = nullptr;
    ALabel *name_label_ = nullptr;
    AStackedWidget *stacked_widget_ = nullptr;
    AImportGuide *import_guide_ = nullptr;
    Image2GifFileListView *file_list_view_ = nullptr;
    Image2GifPreviewView *preview_view_ = nullptr;
    Image2GifSettingView *setting_view_ = nullptr;
};
} // namespace image2gif