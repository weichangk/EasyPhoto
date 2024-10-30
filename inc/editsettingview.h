#pragma once
#include "inc/models.h"
#include "control/listview.h"
#include "control/lineedit.h"
#include "component/topbarwidget.h"

#include <QWidget>
#include <QStyledItemDelegate>
#include <QTabWidget>
#include <QLabel>
#include <QPushButton>
#include <QCheckBox>
#include <QSlider>
#include <QRadioButton>
#include <QIntValidator>

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

Q_SIGNALS:
    void sigEditCommitData(const TextWatermarkSettingData &data);

private:
    QSize size_ = QSize(kTextWatermarkSettingItemWidth, kTextWatermarkSettingItemHeight);
    int event_type_ = QEvent::None;
    QPoint curpos_;
};

class EditSettingView : public QWidget {
    Q_OBJECT
public:
    explicit EditSettingView(QWidget *parent = nullptr);
    ~EditSettingView();

protected:
    void createUi();
    void sigConnect();

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
    void textWatermarkSettingItemEditCommitData(const TextWatermarkSettingData &data);
private:
    Data *data_ = nullptr;
    QRect select_rect_;

    TopbarWidget *tab_bar_;
    QTabWidget *tab_widget_;

    QWidget *crop_setting_widget_;
    QLabel *original_ratio_label_;
    QLabel *original_ratio_value_label_;
    QCheckBox *equal_ratio_checkbox_;
    QLabel *crop_ratio_label_;
    LineEdit *crop_ratio_width_edit_;
    LineEdit *crop_ratio_height_edit_;
    QPushButton *crop_align_center_button_;
    QPushButton *crop_reset_button_;

    QIntValidator *crop_w_edit_validator_;
    QIntValidator *crop_h_edit_validator_;

    QWidget *rotate_setting_widget_;
    QPushButton *rotate_right90_button_;
    QPushButton *rotate_left90_button_;
    QPushButton *rotate_horizontal_flip_button_;
    QPushButton *rotate_vertical_flip_button_;
    QLabel *rotate_angle_label_;
    LineEdit *rotate_angle_edit_;
    QPushButton *rotate_reset_button_;

    QIntValidator *rotate_angle_edit_validator_;

    QWidget *effect_setting_widget_;
    QLabel *luminance_label_;
    QSlider *luminance_slider_;
    QLabel *luminance_value_;
    QLabel *contrast_label_;
    QSlider *contrast_slider_;
    QLabel *contrast_value_;
    QLabel *saturation_label_;
    QSlider *saturation_slider_;
    QLabel *saturation_value_;
    QPushButton *effect_reset_button_;

    QWidget *watermark_setting_widget_;
    QLabel *picture_label_;
    QPushButton *picture_add_button_;
    ListView<ImageWatermarkSettingData> *image_watermark_setting_list_view_;
    QLabel *picture_alpha_label_;
    QSlider *picture_alpha_slider_;
    QLabel *picture_alpha_value_;
    QPushButton *clear_button_;
    QLabel *text_label_;
    QPushButton *text_add_button_;
    ListView<TextWatermarkSettingData> *text_watermark_setting_list_view_;
    QPushButton *export_button_;
};
} // namespace imageedit