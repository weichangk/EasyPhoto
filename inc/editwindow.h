#pragma once
#include "editfilelistview.h"
#include "editpreviewview.h"
#include "editsettingview.h"
#include "component/topbarwidget.h"
#include "component/importguidewidget.h"

#include <QWidget>
#include <QLabel>
#include <QStackedWidget>

namespace imageedit {
class EditWindow : public QWidget {
    Q_OBJECT
public:
    explicit EditWindow(QWidget *parent = nullptr);
    ~EditWindow();
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
    EditFileListView *file_list_view_ = nullptr;
    EditPreviewView *preview_view_ = nullptr;
    EditSettingView *setting_view_ = nullptr;
};
} // namespace imageedit