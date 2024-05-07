/*
 * @Author: weick
 * @Date: 2024-03-23 11:13:21
 * @Last Modified by: weick
 * @Last Modified time: 2024-04-02 07:53:39
 */

#pragma once
#include "../agui/inc/abasewidget.h"
#include "inc/models.h"

class ALabel;
class AWidget;
namespace imageedit {
class EditCropView;
class EditPreviewView : public ABaseWidget {
    Q_OBJECT
public:
    explicit EditPreviewView(QWidget *parent = nullptr);
    ~EditPreviewView();

protected:
    void createUi() override;
    void changeLanguage() override;
    void sigConnect() override;
    void showEvent(QShowEvent *event) override;
    void hideEvent(QHideEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void moveEvent(QMoveEvent *event) override;

private:
    void preViewDataSelected(Data *data);
    void updateCropViewGeometry();
    void loadInputPixmap(const QString &path);
    void updateInputPixmapSize();
    void selectRectChanged(const QRect &rect);
    void selectRectChangedEnd(const QRect &rect);
    void setCropViewSelectionRect(const QRect &rect);
    void cropUseAspectRatio(bool use);

    void rotateAngleChanged(int angle);

private:
    Data *data_ = nullptr;

    ALabel *input_preview_label_;
    AWidget *input_preview_widget_;
    ALabel *input_preview_pixmap_label_;
    ALabel *output_preview_label_;
    AWidget *output_preview_widget_;
    ALabel *output_preview_pixmap_label_;
    EditCropView *crop_view_;

    QPixmap input_pixmap_;
};
} // namespace imageedit