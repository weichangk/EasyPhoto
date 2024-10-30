#pragma once
#include "imageupscaylfilelistview.h"
#include "imageupscaylpreviewview.h"
#include "imageupscaylsettingview.h"
#include "component/topbarwidget.h"
#include "component/importguidewidget.h"

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QStackedWidget>

namespace imageupscayl {
class ImageUpscaylWindow : public QWidget {
    Q_OBJECT
public:
    explicit ImageUpscaylWindow(QWidget *parent = nullptr);
    ~ImageUpscaylWindow();
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
    QStackedWidget *left_stacked_widget_ = nullptr;
    ImportGuideWidget *import_guide_ = nullptr;
    QPushButton *setting_button_ = nullptr;
    QPushButton *file_list_button_ = nullptr;
    QPushButton *upscayl_button_ = nullptr;
    ImageUpscaylSettingView *setting_view_ = nullptr;
    ImageUpscaylFileListView *file_list_view_ = nullptr;
    ImageUpscaylPreviewView *preview_view_ = nullptr;
};
} // namespace imageupscayl