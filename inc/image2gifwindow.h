#pragma once
#include "image2giffilelistview.h"
#include "image2gifpreviewview.h"
#include "image2gifsettingview.h"
#include "component/topbarwidget.h"
#include "component/importguidewidget.h"

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QStackedWidget>

namespace image2gif {
class Image2GifWindow : public QWidget {
    Q_OBJECT
public:
    explicit Image2GifWindow(QWidget *parent = nullptr);
    ~Image2GifWindow();
    void changeFileListData(QList<Data> datas);
    void setFileListCurrentIndex(int index);
    int fileListCurrentIndex();
    
protected:
    void createUi();
    void sigConnect();
    void paintEvent(QPaintEvent *event) override;
    void moveEvent(QMoveEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    TopbarWidget *topbar_ = nullptr;
    QLabel *logo_label_ = nullptr;
    QLabel *name_label_ = nullptr;
    QStackedWidget *stacked_widget_ = nullptr;
    ImportGuideWidget *import_guide_ = nullptr;
    Image2GifFileListView *file_list_view_ = nullptr;
    Image2GifPreviewView *preview_view_ = nullptr;
    Image2GifSettingView *setting_view_ = nullptr;
};
} // namespace image2gif