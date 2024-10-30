#pragma once
#include "inc/models.h"
#include "inc/editcropview.h"

#include <QWidget>
#include <QLabel>
#include <QPixmap>

namespace imageedit {
class EditPreviewView : public QWidget {
    Q_OBJECT
public:
    explicit EditPreviewView(QWidget *parent = nullptr);
    ~EditPreviewView();

protected:
    void createUi();
    void sigConnect();
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

    void luminanceChanged(int value);
    void contrastChanged(int value);
    void saturationChanged(int value);
    void effectReset(int luminance, int contrast, int saturation);
private:
    Data *data_ = nullptr;

    QLabel *input_preview_label_;
    QWidget *input_preview_widget_;
    QLabel *input_preview_pixmap_label_;
    QLabel *output_preview_label_;
    QWidget *output_preview_widget_;
    QLabel *output_preview_pixmap_label_;
    EditCropView *crop_view_;

    QPixmap input_pixmap_;
};
} // namespace imageedit