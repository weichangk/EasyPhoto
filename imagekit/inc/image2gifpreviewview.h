/*
 * @Author: weick 
 * @Date: 2024-06-03 07:33:48 
 * @Last Modified by: weick
 * @Last Modified time: 2024-06-03 07:35:31
 */

#pragma once
#include "../awidget/inc/awidget.h"
#include "../awidget/inc/alabel.h"
#include "../awidget/inc/apushbutton.h"
#include "../agui/inc/abasewidget.h"
#include "../agui/inc/apreviewbutton.h"
#include "inc/models.h"

namespace image2gif {
class Image2GifPreviewView : public ABaseWidget {
    Q_OBJECT
public:
    explicit Image2GifPreviewView(QWidget *parent = nullptr);
    ~Image2GifPreviewView();

protected:
    void createUi() override;
    void changeLanguage() override;
    void sigConnect() override;
    bool eventFilter(QObject *watched, QEvent *event) override;

private:
    void preViewDataSelected(Data *data);
    void loadSelectedPixmap(const QString &path);
    void updateSelectedPixmapSize();
    void slotPreviewButtonClicked();

private:
    Data *data_ = nullptr;

    AWidget *preview_widget_;
    ALabel *preview_pixmap_label_;
    QPixmap preview_pixmap_;
    QMovie *preview_movie_;
    APreviewButton *preview_button_ = nullptr;
};
} // namespace image2gif