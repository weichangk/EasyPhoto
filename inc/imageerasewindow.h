#pragma once
#include "imageerasefilelistview.h"
#include "imageerasepreviewview.h"
#include "imageerasesettingview.h"
#include "component/topbarwidget.h"
#include "component/importguidewidget.h"

#include <QWidget>
#include <QLabel>
#include <QStackedWidget>

namespace imageerase {
class ImageEraseWindow : public QWidget {
    Q_OBJECT
public:
    explicit ImageEraseWindow(QWidget *parent = nullptr);
    ~ImageEraseWindow();
    void changeFileListData(QList<Data> datas);
    void setFileListCurrentIndex(int index);
    int fileListCurrentIndex();
    
protected:
    void createUi();
    void sigConnect();
    void paintEvent(QPaintEvent *event) override;
    void moveEvent(QMoveEvent *event) override;

private:
    TopbarWidget *topbar_ = nullptr;
    QLabel *logo_label_ = nullptr;
    QLabel *name_label_ = nullptr;
    QStackedWidget *stacked_widget_ = nullptr;
    ImportGuideWidget *import_guide_ = nullptr;
    ImageEraseFileListView *file_list_view_ = nullptr;
    ImageErasePreviewView *preview_view_ = nullptr;
    ImageEraseSettingView *setting_view_ = nullptr;
};
} // namespace imageedit