/*
 * @Author: weick
 * @Date: 2024-03-23 11:23:05
 * @Last Modified by: weick
 * @Last Modified time: 2024-03-31 08:18:35
 */

#pragma once
#include "../agui/inc/abasewidget.h"
#include "../agui/inc/alistview.h"
#include "inc/models.h"
#include <QStyledItemDelegate>

class ATabBar;
class ATabWidget;
class AWidget;
class ALabel;
class APushButton;
class ACheckBox;
class ALineEdit;
class ASlider;
class ARadioButton;
class QIntValidator;
namespace imageedit {
class ImageWatermarkSettingItemDelegate : public QStyledItemDelegate {
    Q_OBJECT
public:
    explicit ImageWatermarkSettingItemDelegate(QObject *parent = nullptr);
    ~ImageWatermarkSettingItemDelegate();

    bool eventFilter(QObject *object, QEvent *event) override;
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void changeSizeHint(const QSize &size);

private:
    QSize size_ = QSize(kImageWatermarkSettingItemWidth, kImageWatermarkSettingItemHeight);
    int event_type_ = QEvent::None;
    QPoint curpos_;
};

class TextWatermarkSettingItemDelegate : public QStyledItemDelegate {
    Q_OBJECT
public:
    explicit TextWatermarkSettingItemDelegate(QObject *parent = nullptr);
    ~TextWatermarkSettingItemDelegate();

    bool eventFilter(QObject *object, QEvent *event) override;
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void changeSizeHint(const QSize &size);

    QWidget *createEditor(QWidget *parent,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor,
                      QAbstractItemModel *model,
                      const QModelIndex &index) const override;
    void updateEditorGeometry(QWidget *editor,
                              const QStyleOptionViewItem &option,
                              const QModelIndex &index) const override;

private:
    QSize size_ = QSize(kTextWatermarkSettingItemWidth, kTextWatermarkSettingItemHeight);
    int event_type_ = QEvent::None;
    QPoint curpos_;
};

class EditSettingView : public ABaseWidget {
    Q_OBJECT
public:
    explicit EditSettingView(QWidget *parent = nullptr);
    ~EditSettingView();

protected:
    void createUi() override;
    void changeLanguage() override;
    void sigConnect() override;

private:
    void preViewDataSelected(Data *data);
    void selectRectChanged(const QRect &rect);
    void cropWidthEditingConfirm(const QString &text);
    void cropHeightEditingConfirm(const QString &text);
    void resetCrop();
    void alignCenter();
    void equalRatioChanged(int state);

    void rotateAngleEditingConfirm(const QString &text);
    void resetRotate();
    void rotateRight90();
    void rotateLeft90();
    void rotateHorizontalFlip();
    void rotateVerticalFlip();

    void luminanceChanged();
    void contrastChanged();
    void saturationChanged();
    void resetEffect();

    void pictureAlphaChanged();
    void changeImageWatermarkSettingData(const QList<ImageWatermarkSettingData> &datas);
    void loadImageWatermarkSettingData();
    void addImageWatermarkPictureOpenFileDialog();
    void imageWatermarkListItemClicked(const QModelIndex &index);
    void addImageWatermarkPicture(const QList<ImageWatermarkSettingData> &datas);
    void deleteImageWatermarkPicture(const QList<QString> &filePathsToDelete);
    void alphaWidgetVisible(bool visible);
    void imageWatermarkSettingListViewAdjustHeight(int listCount);
    void changeTextWatermarkSettingData(const QList<TextWatermarkSettingData> &datas);
    void loadTextWatermarkSettingData();
    void addEmptyTextWatermark();
    void textWatermarkListItemClicked(const QModelIndex &index);
    void addTextWatermarkSettingItem(const QList<TextWatermarkSettingData> &datas);
    void deleteTextWatermarkSettingItem(const QList<QString> &idsToDelete);
    void fontWidgetVisible(bool visible);
    void textWatermarkSettingListViewAdjustHeight(int listCount);
private:
    Data *data_ = nullptr;
    QRect select_rect_;

    ATabBar *tab_bar_;
    ATabWidget *tab_widget_;

    AWidget *crop_setting_widget_;
    ALabel *original_ratio_label_;
    ALabel *original_ratio_value_label_;
    ACheckBox *equal_ratio_checkbox_;
    ALabel *crop_ratio_label_;
    ALineEdit *crop_ratio_width_edit_;
    ALineEdit *crop_ratio_height_edit_;
    APushButton *crop_align_center_button_;
    APushButton *crop_reset_button_;

    QIntValidator *crop_w_edit_validator_;
    QIntValidator *crop_h_edit_validator_;

    AWidget *rotate_setting_widget_;
    APushButton *rotate_right90_button_;
    APushButton *rotate_left90_button_;
    APushButton *rotate_horizontal_flip_button_;
    APushButton *rotate_vertical_flip_button_;
    ALabel *rotate_angle_label_;
    ALineEdit *rotate_angle_edit_;
    APushButton *rotate_reset_button_;

    QIntValidator *rotate_angle_edit_validator_;

    AWidget *effect_setting_widget_;
    ALabel *luminance_label_;
    ASlider *luminance_slider_;
    ALabel *luminance_value_;
    ALabel *contrast_label_;
    ASlider *contrast_slider_;
    ALabel *contrast_value_;
    ALabel *saturation_label_;
    ASlider *saturation_slider_;
    ALabel *saturation_value_;
    APushButton *effect_reset_button_;

    AWidget *watermark_setting_widget_;
    ALabel *picture_label_;
    APushButton *picture_add_button_;
    AListView<ImageWatermarkSettingData> *image_watermark_setting_list_view_;
    ALabel *picture_alpha_label_;
    ASlider *picture_alpha_slider_;
    ALabel *picture_alpha_value_;
    APushButton *clear_button_;
    ALabel *text_label_;
    APushButton *text_add_button_;
    AListView<TextWatermarkSettingData> *text_watermark_setting_list_view_;
    APushButton *export_button_;
};
} // namespace imageedit