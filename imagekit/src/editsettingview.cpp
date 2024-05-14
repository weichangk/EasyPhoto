/*
 * @Author: weick
 * @Date: 2024-03-23 11:24:18
 * @Last Modified by: weick
 * @Last Modified time: 2024-05-11 08:12:11
 */

#include "inc/editsettingview.h"
#include "inc/signals.h"
#include "../acore/inc/aapppath.h"
#include "../acore/inc/apainterhelper.h"
#include "../awidget/inc/avboxlayout.h"
#include "../awidget/inc/ahboxlayout.h"
#include "../awidget/inc/atabbar.h"
#include "../awidget/inc/atabwidget.h"
#include "../awidget/inc/awidget.h"
#include "../awidget/inc/apushbutton.h"
#include "../awidget/inc/alabel.h"
#include "../awidget/inc/acheckbox.h"
#include "../awidget/inc/alineedit.h"
#include "../awidget/inc/aslider.h"
#include "../awidget/inc/aradiobutton.h"
#include <QIntValidator>
#include <QFile>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QPainter>
#include <QTimer>
#include <QStandardPaths>
#include <QFileDialog>

namespace imageedit {
const static QString imageWatermarkConfigName = "imageWatermarkConfig.json";
const static QString textWatermarkConfigName = "textWatermarkConfig.json";

inline void cropEditvalidatorRangeChanged(QIntValidator *validator, int min, int max) {
    validator->setRange(min, max);
}

inline QRect imageWatermarkSettingItemBorderRect(QRect itemRect) {
    auto rc = itemRect.adjusted(1, 1, -1, -1);
    return rc;
}

inline QRect imageWatermarkSettingItemThumbnailRect(QRect itemRect) {
    auto rc = itemRect;
    return QRect(rc.x(), rc.y(), 100, 56);
}

inline QRect imageWatermarkSettingItemDeteleRect(QRect itemRect) {
    auto rc = itemRect;
    return QRect(rc.x() + rc.width() - 16 - 4, rc.y() + 4, 16, 16);
}

inline QRect imageWatermarkSettingItemNameRect(QRect itemRect) {
    auto rc = itemRect;
    return QRect(rc.x(), rc.y() + rc.height() - 24, rc.width(), 24);
}

inline QPixmap createImageWatermarkThumbnail(const QString &path) {
    return QPixmap(path).scaled(QSize(100, 56), Qt::KeepAspectRatio, Qt::SmoothTransformation);
}

inline QRect textWatermarkSettingItemBorderRect(QRect itemRect) {
    auto rc = itemRect.adjusted(1, 1, -1, -1);
    return rc;
}

inline QRect textWatermarkSettingItemDeteleRect(QRect itemRect) {
    auto rc = itemRect;
    return QRect(rc.x() + rc.width() - 16 - 4, rc.y() + 4, 16, 16);
}

QList<ImageWatermarkSettingData> getImageWatermarkSettingDatas() {
    QList<ImageWatermarkSettingData> datas;

    QDir baseDir(AAppPath::appProgramDataPath());
    QString cfgFile = baseDir.filePath(imageWatermarkConfigName);
    QFile f(cfgFile);

    if (!f.open(QFile::ReadOnly)) {
        qDebug() << "Failed to open" << cfgFile << "for reading.";
        return datas;
    }

    QJsonParseError jsonError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(f.readAll(), &jsonError);
    f.close();

    if (jsonError.error != QJsonParseError::NoError) {
        qDebug() << "Error parsing JSON:" << jsonError.errorString();
        return datas;
    }

    QJsonArray jsonArray = jsonDoc.object()["list"].toArray();

    for (const auto &item : jsonArray) {
        QJsonObject jsonObject = item.toObject();
        ImageWatermarkSettingData data;
        data.file_path = jsonObject["file_path"].toString();
        data.file_name = jsonObject["file_name"].toString();
        data.thumbnail = createImageWatermarkThumbnail(data.file_path);
        data.delete_icon = QPixmap(":/agui/res/image/delete1-24.png");
        datas.append(data);
    }

    return datas;
}

bool addImageWatermarkSettingData(const QList<ImageWatermarkSettingData> &newDatas, QList<ImageWatermarkSettingData> &datas) {
    QDir baseDir(AAppPath::appProgramDataPath());
    QString cfgFile = baseDir.filePath(imageWatermarkConfigName);
    QFile f(cfgFile);

    if (!f.open(QFile::ReadWrite | QFile::Text)) {
        qDebug() << "Failed to open" << cfgFile << "for writing.";
        return false;
    }

    QJsonParseError jsonError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(f.readAll(), &jsonError);
    f.close();

    if (jsonError.error != QJsonParseError::NoError && jsonError.error !=QJsonParseError::IllegalValue) {
        qDebug() << "Error parsing JSON:" << jsonError.errorString();
        return false;
    }

    QJsonObject jsonObj = jsonDoc.object();
    QJsonArray jsonArray = jsonObj["list"].toArray();

    foreach(const auto &newData, newDatas) {
        QJsonObject newDataObject;
        newDataObject["file_path"] = newData.file_path;
        newDataObject["file_name"] = newData.file_name;
        jsonArray.append(newDataObject);
    }

    jsonObj["list"] = jsonArray;

    jsonDoc.setObject(jsonObj);

    if (!f.open(QFile::WriteOnly | QFile::Truncate | QFile::Text)) {
        qDebug() << "Failed to open" << cfgFile << "for writing.";
        return false;
    }

    f.write(jsonDoc.toJson());
    f.close();

    for (const auto &item : jsonArray) {
        QJsonObject jsonObject = item.toObject();
        ImageWatermarkSettingData data;
        data.file_path = jsonObject["file_path"].toString();
        data.file_name = jsonObject["file_name"].toString();
        data.thumbnail = createImageWatermarkThumbnail(data.file_path);
        data.delete_icon = QPixmap(":/agui/res/image/delete1-24.png");
        datas.append(data);
    }

    return true;
}

bool deleteImageWatermarkSettingData(const QList<QString> &filePathsToDelete, QList<ImageWatermarkSettingData> &datas) {
    QDir baseDir(AAppPath::appProgramDataPath());
    QString cfgFile = baseDir.filePath(imageWatermarkConfigName);
    QFile f(cfgFile);

    if (!f.open(QFile::ReadWrite | QFile::Text)) {
        qDebug() << "Failed to open" << cfgFile << "for writing.";
        return false;
    }

    QJsonParseError jsonError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(f.readAll(), &jsonError);
    f.close();

    if (jsonError.error != QJsonParseError::NoError) {
        qDebug() << "Error parsing JSON:" << jsonError.errorString();
        return false;
    }

    QJsonObject jsonObj = jsonDoc.object();
    QJsonArray jsonArray = jsonObj["list"].toArray();

    for (int i = jsonArray.size() - 1; i >= 0; --i) {
        QJsonObject obj = jsonArray[i].toObject();
        QString filePath = obj["file_path"].toString();
        if (filePathsToDelete.contains(filePath)) {
            jsonArray.removeAt(i);
        }
    }

    jsonObj["list"] = jsonArray;
    jsonDoc.setObject(jsonObj);

    if (!f.open(QFile::WriteOnly | QFile::Truncate | QFile::Text)) {
        qDebug() << "Failed to open" << cfgFile << "for writing.";
        return false;
    }

    f.write(jsonDoc.toJson());
    f.close();

    for (const auto &item : jsonArray) {
        QJsonObject jsonObject = item.toObject();
        ImageWatermarkSettingData data;
        data.file_path = jsonObject["file_path"].toString();
        data.file_name = jsonObject["file_name"].toString();
        data.thumbnail = createImageWatermarkThumbnail(data.file_path);
        data.delete_icon = QPixmap(":/agui/res/image/delete1-24.png");
        datas.append(data);
    }

    return true;
}

QList<TextWatermarkSettingData> getTextWatermarkSettingDatas() {
    QList<TextWatermarkSettingData> datas;

    QDir baseDir(AAppPath::appProgramDataPath());
    QString cfgFile = baseDir.filePath(textWatermarkConfigName);
    QFile f(cfgFile);

    if (!f.open(QFile::ReadOnly)) {
        qDebug() << "Failed to open" << cfgFile << "for reading.";
        return datas;
    }

    QJsonParseError jsonError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(f.readAll(), &jsonError);
    f.close();

    if (jsonError.error != QJsonParseError::NoError) {
        qDebug() << "Error parsing JSON:" << jsonError.errorString();
        return datas;
    }

    QJsonArray jsonArray = jsonDoc.object()["list"].toArray();

    for (const auto &item : jsonArray) {
        QJsonObject jsonObject = item.toObject();
        TextWatermarkSettingData data;
        data.id = jsonObject["id"].toString();
        data.text = jsonObject["text"].toString();
        data.delete_icon = QPixmap(":/agui/res/image/delete1-24.png");
        datas.append(data);
    }

    return datas;
}

bool addTextWatermarkSettingData(const QList<TextWatermarkSettingData> &newDatas, QList<TextWatermarkSettingData> &datas) {
    QDir baseDir(AAppPath::appProgramDataPath());
    QString cfgFile = baseDir.filePath(textWatermarkConfigName);
    QFile f(cfgFile);

    if (!f.open(QFile::ReadWrite | QFile::Text)) {
        qDebug() << "Failed to open" << cfgFile << "for writing.";
        return false;
    }

    QJsonParseError jsonError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(f.readAll(), &jsonError);
    f.close();

    if (jsonError.error != QJsonParseError::NoError && jsonError.error !=QJsonParseError::IllegalValue) {
        qDebug() << "Error parsing JSON:" << jsonError.errorString();
        return false;
    }

    QJsonObject jsonObj = jsonDoc.object();
    QJsonArray jsonArray = jsonObj["list"].toArray();

    foreach(const auto &newData, newDatas) {
        QJsonObject newDataObject;
        newDataObject["id"] = newData.id;
        newDataObject["text"] = newData.text;
        jsonArray.append(newDataObject);
    }

    jsonObj["list"] = jsonArray;

    jsonDoc.setObject(jsonObj);

    if (!f.open(QFile::WriteOnly | QFile::Truncate | QFile::Text)) {
        qDebug() << "Failed to open" << cfgFile << "for writing.";
        return false;
    }

    f.write(jsonDoc.toJson());
    f.close();

    for (const auto &item : jsonArray) {
        QJsonObject jsonObject = item.toObject();
        TextWatermarkSettingData data;
        data.id = jsonObject["id"].toString();
        data.text = jsonObject["text"].toString();
        data.delete_icon = QPixmap(":/agui/res/image/delete1-24.png");
        datas.append(data);
    }

    return true;
}

bool deleteTextWatermarkSettingData(const QList<QString> &idsToDelete, QList<TextWatermarkSettingData> &datas) {
    QDir baseDir(AAppPath::appProgramDataPath());
    QString cfgFile = baseDir.filePath(textWatermarkConfigName);
    QFile f(cfgFile);

    if (!f.open(QFile::ReadWrite | QFile::Text)) {
        qDebug() << "Failed to open" << cfgFile << "for writing.";
        return false;
    }

    QJsonParseError jsonError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(f.readAll(), &jsonError);
    f.close();

    if (jsonError.error != QJsonParseError::NoError) {
        qDebug() << "Error parsing JSON:" << jsonError.errorString();
        return false;
    }

    QJsonObject jsonObj = jsonDoc.object();
    QJsonArray jsonArray = jsonObj["list"].toArray();

    for (int i = jsonArray.size() - 1; i >= 0; --i) {
        QJsonObject obj = jsonArray[i].toObject();
        QString id = obj["id"].toString();
        if (idsToDelete.contains(id)) {
            jsonArray.removeAt(i);
        }
    }

    jsonObj["list"] = jsonArray;
    jsonDoc.setObject(jsonObj);

    if (!f.open(QFile::WriteOnly | QFile::Truncate | QFile::Text)) {
        qDebug() << "Failed to open" << cfgFile << "for writing.";
        return false;
    }

    f.write(jsonDoc.toJson());
    f.close();

    for (const auto &item : jsonArray) {
        QJsonObject jsonObject = item.toObject();
        TextWatermarkSettingData data;
        data.id = jsonObject["id"].toString();
        data.text = jsonObject["text"].toString();
        data.delete_icon = QPixmap(":/agui/res/image/delete1-24.png");
        datas.append(data);
    }

    return true;
}

ImageWatermarkSettingItemDelegate::ImageWatermarkSettingItemDelegate(QObject *parent) :
    QStyledItemDelegate(parent) {
}

ImageWatermarkSettingItemDelegate::~ImageWatermarkSettingItemDelegate() {
}

bool ImageWatermarkSettingItemDelegate::eventFilter(QObject *object, QEvent *event) {
    int type = event->type();
    if (type == QEvent::MouseButtonPress || type == QEvent::MouseButtonRelease) {
        event_type_ = type;
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        if (mouseEvent) {
            QPoint pos = mouseEvent->pos();
            curpos_ = pos;
            QWidget *curWidget = static_cast<QWidget *>(object);
            curWidget->update();
        }
    }
    return QStyledItemDelegate::eventFilter(object, event);
}

void ImageWatermarkSettingItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    auto data = index.data(Qt::UserRole).value<ImageWatermarkSettingData>();
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::NoBrush);

    QRect rc = option.rect;
    bool pressed = event_type_ == QEvent::MouseButtonPress && rc.contains(curpos_);
    bool selected = option.state & QStyle::State_Selected;
    bool hover = option.state & QStyle::State_MouseOver;
    bool selected_or_hover = selected || hover;

    auto thumbnailRect = imageWatermarkSettingItemThumbnailRect(rc);
    APainterHelper::paintPixmap(painter, thumbnailRect, data.thumbnail, 1, 0, true);

    auto borderRect = imageWatermarkSettingItemBorderRect(rc);
    QPen pen(QColor("#2F2D2D"));
    pen.setWidth(1);
    painter->setPen(pen);
    painter->drawRoundedRect(borderRect, 0, 0);
    painter->setPen(Qt::NoPen);

    if (hover) {
        auto delIconRect = imageWatermarkSettingItemDeteleRect(rc);
        APainterHelper::paintPixmap(painter, delIconRect, data.delete_icon, 1, 0, true);
    }

    painter->setPen(QColor("#1F1F1F"));
    pen.setWidth(1);
    if (hover || pressed) {
        painter->drawRoundedRect(borderRect, 0, 0);
    }
    painter->setPen(Qt::NoPen);

    pen.setColor(QColor("#575859"));
    painter->setPen(pen);
    QFont font = painter->font();
    font.setPointSizeF(11);
    painter->setFont(font);
    QString fileName = data.file_name;
    auto nameRect = imageWatermarkSettingItemNameRect(rc);
    QFontMetricsF metrics(font);
    if (metrics.horizontalAdvance(fileName) > nameRect.width()) {
        fileName = metrics.elidedText(fileName, Qt::ElideMiddle, nameRect.width(), Qt::TextShowMnemonic);
    }
    painter->drawText(nameRect, Qt::PlainText, fileName);
    painter->setPen(Qt::NoPen);
}

QSize ImageWatermarkSettingItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {
    return size_;
}

void ImageWatermarkSettingItemDelegate::changeSizeHint(const QSize &size) {
    size_ = size;
}

TextWatermarkSettingItemDelegate::TextWatermarkSettingItemDelegate(QObject *parent) :
    QStyledItemDelegate(parent) {
}

TextWatermarkSettingItemDelegate::~TextWatermarkSettingItemDelegate() {
}

bool TextWatermarkSettingItemDelegate::eventFilter(QObject *object, QEvent *event) {
    int type = event->type();
    if (type == QEvent::MouseButtonPress || type == QEvent::MouseButtonRelease) {
        event_type_ = type;
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        if (mouseEvent) {
            QPoint pos = mouseEvent->pos();
            curpos_ = pos;
            QWidget *curWidget = static_cast<QWidget *>(object);
            curWidget->update();
        }
    }
    return QStyledItemDelegate::eventFilter(object, event);
}

void TextWatermarkSettingItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    auto data = index.data(Qt::UserRole).value<TextWatermarkSettingData>();
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::NoBrush);

    QRect rc = option.rect;
    bool pressed = event_type_ == QEvent::MouseButtonPress && rc.contains(curpos_);
    bool selected = option.state & QStyle::State_Selected;
    bool hover = option.state & QStyle::State_MouseOver;
    bool selected_or_hover = selected || hover;

    auto borderRect = textWatermarkSettingItemBorderRect(rc);
    QPen pen(QColor("#2F2D2D"));
    pen.setWidth(1);
    painter->setPen(pen);
    painter->drawRoundedRect(borderRect, 0, 0);
    painter->setPen(Qt::NoPen);

    if (hover) {
        auto delIconRect = textWatermarkSettingItemDeteleRect(rc);
        APainterHelper::paintPixmap(painter, delIconRect, data.delete_icon, 1, 0, true);
    }

    painter->setPen(QColor("#1F1F1F"));
    pen.setWidth(1);
    if (hover || pressed) {
        painter->drawRoundedRect(borderRect, 0, 0);
    }
    painter->setPen(Qt::NoPen);

    // pen.setColor(QColor("#575859"));
    // painter->setPen(pen);
    // QFont font = painter->font();
    // font.setPointSizeF(11);
    // painter->setFont(font);
    // QString fileName = data.file_name;
    // auto nameRect = imageWatermarkSettingItemNameRect(rc);
    // QFontMetricsF metrics(font);
    // if (metrics.horizontalAdvance(fileName) > nameRect.width()) {
    //     fileName = metrics.elidedText(fileName, Qt::ElideMiddle, nameRect.width(), Qt::TextShowMnemonic);
    // }
    // painter->drawText(nameRect, Qt::PlainText, fileName);
    // painter->setPen(Qt::NoPen);
}

QSize TextWatermarkSettingItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {
    return size_;
}

void TextWatermarkSettingItemDelegate::changeSizeHint(const QSize &size) {
    size_ = size;
}

QWidget *TextWatermarkSettingItemDelegate::createEditor(QWidget *parent,
                                                        const QStyleOptionViewItem &option,
                                                        const QModelIndex &index) const {
    QLineEdit *editor = new QLineEdit(parent);
    editor->setMaxLength(kTextWatermarkSettingItemEditWidth);
    return editor;
}

void TextWatermarkSettingItemDelegate::setEditorData(QWidget *editor,
                                                     const QModelIndex &index) const {
    // QString value = index.model()->data(index, Qt::EditRole).toString();
    auto data = index.data(Qt::UserRole).value<TextWatermarkSettingData>();
    QLineEdit *lineEdit = static_cast<QLineEdit *>(editor);
    lineEdit->setText(data.text);
}

void TextWatermarkSettingItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                                    const QModelIndex &index) const {
    QLineEdit *lineEdit = static_cast<QLineEdit *>(editor);
    QString value = lineEdit->text();
    model->setData(index, value, Qt::UserRole);
}

void TextWatermarkSettingItemDelegate::updateEditorGeometry(QWidget *editor,
                                                            const QStyleOptionViewItem &option,
                                                            const QModelIndex &index) const {
    editor->setGeometry(option.rect);
}

EditSettingView::EditSettingView(QWidget *parent) :
    ABaseWidget(parent) {
    createUi();
    sigConnect();
    changeLanguage();
    loadImageWatermarkSettingData();
    loadTextWatermarkSettingData();
}

EditSettingView::~EditSettingView() {
}

void EditSettingView::createUi() {
    auto mainLayout = new AVBoxLayout(this);
    tab_widget_ = new ATabWidget(this);
    tab_bar_ = new ATabBar(tab_widget_);

    crop_setting_widget_ = new AWidget(this);
    rotate_setting_widget_ = new AWidget(this);
    effect_setting_widget_ = new AWidget(this);
    watermark_setting_widget_ = new AWidget(this);

    tab_widget_->addTab(crop_setting_widget_, "Crop");
    tab_widget_->addTab(rotate_setting_widget_, "Rotate");
    tab_widget_->addTab(effect_setting_widget_, "Effect");
    tab_widget_->addTab(watermark_setting_widget_, "Watermark");

    // crop
    crop_w_edit_validator_ = new QIntValidator(this);
    crop_h_edit_validator_ = new QIntValidator(this);
    cropEditvalidatorRangeChanged(crop_w_edit_validator_, kCropRectMinW, 1920);
    cropEditvalidatorRangeChanged(crop_h_edit_validator_, kCropRectMinH, 1080);

    original_ratio_label_ = new ALabel(crop_setting_widget_);
    original_ratio_value_label_ = new ALabel(crop_setting_widget_);
    equal_ratio_checkbox_ = new ACheckBox(crop_setting_widget_);
    crop_ratio_label_ = new ALabel(crop_setting_widget_);
    crop_ratio_width_edit_ = new ALineEdit(crop_setting_widget_);
    crop_ratio_height_edit_ = new ALineEdit(crop_setting_widget_);
    crop_ratio_width_edit_->setValidator(crop_w_edit_validator_);
    crop_ratio_height_edit_->setValidator(crop_h_edit_validator_);
    crop_align_center_button_ = new APushButton(crop_setting_widget_);
    crop_reset_button_ = new APushButton(crop_setting_widget_);
    auto crop_layout = new AVBoxLayout(crop_setting_widget_);
    auto original_ratio_layout = new AHBoxLayout();
    original_ratio_layout->addWidget(original_ratio_label_);
    original_ratio_layout->addWidget(original_ratio_value_label_);
    original_ratio_layout->addStretch();
    crop_layout->addLayout(original_ratio_layout);
    crop_layout->addWidget(equal_ratio_checkbox_);
    crop_layout->addWidget(crop_ratio_label_);
    auto crop_ratio_layout = new AHBoxLayout();
    crop_ratio_layout->addWidget(crop_ratio_width_edit_);
    ALabel *x_label = new ALabel(crop_setting_widget_);
    x_label->setText("x");
    crop_ratio_layout->addWidget(x_label);
    crop_ratio_layout->addWidget(crop_ratio_height_edit_);
    crop_ratio_layout->addStretch();
    crop_layout->addLayout(crop_ratio_layout);
    crop_layout->addWidget(crop_align_center_button_);
    crop_layout->addWidget(crop_reset_button_);
    crop_layout->addStretch();
    equal_ratio_checkbox_->setVisible(false);

    // rotate
    rotate_angle_edit_validator_ = new QIntValidator(this);
    rotate_angle_edit_validator_->setRange(-360, 360);

    rotate_right90_button_ = new APushButton(rotate_setting_widget_);
    rotate_left90_button_ = new APushButton(rotate_setting_widget_);
    rotate_horizontal_flip_button_ = new APushButton(rotate_setting_widget_);
    rotate_vertical_flip_button_ = new APushButton(rotate_setting_widget_);
    rotate_angle_label_ = new ALabel(rotate_setting_widget_);
    rotate_angle_edit_ = new ALineEdit(rotate_setting_widget_);
    rotate_angle_edit_->setValidator(rotate_angle_edit_validator_);
    rotate_reset_button_ = new APushButton(rotate_setting_widget_);
    auto rotate_layout = new AVBoxLayout(rotate_setting_widget_);
    auto rotate_button_layout = new AHBoxLayout();
    rotate_button_layout->addWidget(rotate_right90_button_);
    rotate_button_layout->addWidget(rotate_left90_button_);
    rotate_button_layout->addWidget(rotate_horizontal_flip_button_);
    rotate_button_layout->addWidget(rotate_vertical_flip_button_);
    rotate_button_layout->addStretch();
    rotate_layout->addLayout(rotate_button_layout);
    auto rotate_angle_layout = new AHBoxLayout();
    rotate_angle_layout->addWidget(rotate_angle_label_);
    rotate_angle_layout->addWidget(rotate_angle_edit_);
    rotate_angle_layout->addStretch();
    rotate_layout->addLayout(rotate_angle_layout);
    rotate_layout->addWidget(rotate_reset_button_);
    rotate_layout->addStretch();

    // effect
    luminance_label_ = new ALabel(effect_setting_widget_);
    luminance_slider_ = new ASlider(effect_setting_widget_);
    luminance_value_ = new ALabel(effect_setting_widget_);
    luminance_slider_->setOrientation(Qt::Horizontal);
    luminance_slider_->setRange(kLuminanceRangeMin, kLuminanceRangeMax);
    contrast_label_ = new ALabel(effect_setting_widget_);
    contrast_slider_ = new ASlider(effect_setting_widget_);
    contrast_value_ = new ALabel(effect_setting_widget_);
    contrast_slider_->setOrientation(Qt::Horizontal);
    contrast_slider_->setRange(kContrastRangeMin, kContrastRangeMax);
    saturation_label_ = new ALabel(effect_setting_widget_);
    saturation_slider_ = new ASlider(effect_setting_widget_);
    saturation_value_ = new ALabel(effect_setting_widget_);
    saturation_slider_->setOrientation(Qt::Horizontal);
    saturation_slider_->setRange(kSaturationRangeMin, kSaturationRangeMax);
    auto effect_layout = new AVBoxLayout(effect_setting_widget_);
    auto luminance_layout = new AHBoxLayout();
    luminance_layout->addWidget(luminance_label_);
    luminance_layout->addWidget(luminance_slider_);
    luminance_layout->addWidget(luminance_value_);
    luminance_layout->addStretch();
    effect_layout->addLayout(luminance_layout);
    auto contrast_layout = new AHBoxLayout();
    contrast_layout->addWidget(contrast_label_);
    contrast_layout->addWidget(contrast_slider_);
    contrast_layout->addWidget(contrast_value_);
    contrast_layout->addStretch();
    effect_layout->addLayout(contrast_layout);
    auto saturation_layout = new AHBoxLayout();
    saturation_layout->addWidget(saturation_label_);
    saturation_layout->addWidget(saturation_slider_);
    saturation_layout->addWidget(saturation_value_);
    saturation_layout->addStretch();
    effect_layout->addLayout(saturation_layout);
    effect_reset_button_ = new APushButton(effect_setting_widget_);
    effect_layout->addWidget(effect_reset_button_);
    effect_layout->addStretch();

    // watermark
    picture_label_ = new ALabel(watermark_setting_widget_);
    picture_add_button_ = new APushButton(watermark_setting_widget_);
    text_label_ = new ALabel(watermark_setting_widget_);
    text_add_button_ = new APushButton(watermark_setting_widget_);
    auto watermark_layout = new AVBoxLayout(watermark_setting_widget_);
    auto picture_layout = new AHBoxLayout();
    picture_layout->addWidget(picture_label_);
    picture_layout->addStretch();
    picture_layout->addWidget(picture_add_button_);
    watermark_layout->addLayout(picture_layout);
    image_watermark_setting_list_view_ = new AListView<ImageWatermarkSettingData>(this);
    image_watermark_setting_list_view_->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    image_watermark_setting_list_view_->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    image_watermark_setting_list_view_->setResizeMode(QListView::Adjust);
    image_watermark_setting_list_view_->setViewMode(QListView::IconMode);
    image_watermark_setting_list_view_->setDragEnabled(false);
    image_watermark_setting_list_view_->setSelectionMode(QAbstractItemView::NoSelection);
    image_watermark_setting_list_view_->setSpacing(kImageWatermarkSettingItemSpacing);
    auto imakeWatermarkItemDelegate = new ImageWatermarkSettingItemDelegate(this);
    image_watermark_setting_list_view_->setItemDelegate(imakeWatermarkItemDelegate);
    image_watermark_setting_list_view_->viewport()->installEventFilter(imakeWatermarkItemDelegate);
    watermark_layout->addWidget(image_watermark_setting_list_view_);
    picture_alpha_label_ = new ALabel(watermark_setting_widget_);
    picture_alpha_slider_ = new ASlider(watermark_setting_widget_);
    picture_alpha_slider_->setOrientation(Qt::Horizontal);
    picture_alpha_slider_->setRange(kPictureAlphaRangeMin, kPictureAlphaRangeMax);
    picture_alpha_value_ = new ALabel(watermark_setting_widget_);
    auto picture_alpha_layout = new AHBoxLayout();
    picture_alpha_layout->addWidget(picture_alpha_label_);
    picture_alpha_layout->addWidget(picture_alpha_slider_);
    picture_alpha_layout->addWidget(picture_alpha_value_);
    picture_alpha_layout->addStretch();
    watermark_layout->addLayout(picture_alpha_layout);

    auto text_layout = new AHBoxLayout();
    text_layout->addWidget(text_label_);
    text_layout->addStretch();
    text_layout->addWidget(text_add_button_);
    watermark_layout->addLayout(text_layout);
    text_watermark_setting_list_view_ = new AListView<TextWatermarkSettingData>(this);
    text_watermark_setting_list_view_->setEditTriggers(QAbstractItemView::DoubleClicked);
    text_watermark_setting_list_view_->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    text_watermark_setting_list_view_->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    text_watermark_setting_list_view_->setResizeMode(QListView::Adjust);
    text_watermark_setting_list_view_->setViewMode(QListView::IconMode);
    text_watermark_setting_list_view_->setDragEnabled(false);
    text_watermark_setting_list_view_->setSelectionMode(QAbstractItemView::NoSelection);
    text_watermark_setting_list_view_->setSpacing(kTextWatermarkSettingItemSpacing);
    auto textWatermarkItemDelegate = new TextWatermarkSettingItemDelegate(this);
    text_watermark_setting_list_view_->setItemDelegate(textWatermarkItemDelegate);
    text_watermark_setting_list_view_->viewport()->installEventFilter(textWatermarkItemDelegate);
    watermark_layout->addWidget(text_watermark_setting_list_view_);
    clear_button_ = new APushButton(watermark_setting_widget_);
    watermark_layout->addWidget(clear_button_);
    watermark_layout->addStretch();

    export_button_ = new APushButton(this);
    export_button_->setFixedHeight(32);
    mainLayout->addWidget(tab_widget_, 1);
    mainLayout->addWidget(export_button_);
}

void EditSettingView::changeLanguage() {
    original_ratio_label_->setText("Original ratio");
    original_ratio_value_label_->setText("1:1");
    equal_ratio_checkbox_->setText("Equal ratio");
    crop_ratio_label_->setText("Crop ratio");
    crop_ratio_width_edit_->setText("1");
    crop_ratio_height_edit_->setText("1");
    crop_align_center_button_->setText("Align center");
    crop_reset_button_->setText("Reset");

    rotate_angle_label_->setText("Angle");
    rotate_angle_edit_->setText("0");
    rotate_reset_button_->setText("Reset");

    luminance_label_->setText("Luminance");
    contrast_label_->setText("Contrast");
    saturation_label_->setText("Saturation");

    picture_label_->setText("Picture");
    picture_alpha_label_->setText("Alpha");
    text_label_->setText("Text");
    clear_button_->setText("Clear");

    export_button_->setText("Export");
}

void EditSettingView::sigConnect() {
    connect(Signals::getInstance(), &Signals::sigListItemDataSelected, this, &EditSettingView::preViewDataSelected);
    connect(Signals::getInstance(), &Signals::sigSelectRectPreview2Setting, this, &EditSettingView::selectRectChanged);
    connect(crop_ratio_width_edit_, &ALineEdit::sigEditingConfirm, this, &EditSettingView::cropWidthEditingConfirm);
    connect(crop_ratio_height_edit_, &ALineEdit::sigEditingConfirm, this, &EditSettingView::cropHeightEditingConfirm);
    connect(crop_reset_button_, &APushButton::clicked, this, &EditSettingView::resetCrop);
    connect(crop_align_center_button_, &APushButton::clicked, this, &EditSettingView::alignCenter);
    connect(equal_ratio_checkbox_, &ACheckBox::stateChanged, this, &EditSettingView::equalRatioChanged);

    connect(rotate_angle_edit_, &ALineEdit::sigEditingConfirm, this, &EditSettingView::rotateAngleEditingConfirm);
    connect(rotate_reset_button_, &APushButton::clicked, this, &EditSettingView::resetRotate);
    connect(rotate_right90_button_, &APushButton::clicked, this, &EditSettingView::rotateRight90);
    connect(rotate_left90_button_, &APushButton::clicked, this, &EditSettingView::rotateLeft90);
    connect(rotate_horizontal_flip_button_, &APushButton::clicked, this, &EditSettingView::rotateHorizontalFlip);
    connect(rotate_vertical_flip_button_, &APushButton::clicked, this, &EditSettingView::rotateVerticalFlip);

    connect(luminance_slider_, &ASlider::valueChanged, this, &EditSettingView::luminanceChanged);
    connect(contrast_slider_, &ASlider::valueChanged, this, &EditSettingView::contrastChanged);
    connect(saturation_slider_, &ASlider::valueChanged, this, &EditSettingView::saturationChanged);
    connect(effect_reset_button_, &APushButton::clicked, this, &EditSettingView::resetEffect);

    connect(picture_add_button_, &APushButton::clicked, this, &EditSettingView::addImageWatermarkPictureOpenFileDialog);
    connect(image_watermark_setting_list_view_, &QListView::clicked, this, &EditSettingView::imageWatermarkListItemClicked);
    connect(picture_alpha_slider_, &ASlider::valueChanged, this, &EditSettingView::pictureAlphaChanged);
    connect(text_add_button_, &APushButton::clicked, this, &EditSettingView::addEmptyTextWatermark);
    connect(text_watermark_setting_list_view_, &QListView::clicked, this, &EditSettingView::textWatermarkListItemClicked);
    
}

void EditSettingView::preViewDataSelected(Data *data) {
    data_ = data;

    original_ratio_value_label_->setText(QString("%1:%2").arg(data_->origin_crop_rect.width()).arg(data_->origin_crop_rect.height()));
    cropEditvalidatorRangeChanged(crop_w_edit_validator_, kCropRectMinW, data_->origin_crop_rect.width());
    cropEditvalidatorRangeChanged(crop_h_edit_validator_, kCropRectMinH, data_->origin_crop_rect.height());
    equal_ratio_checkbox_->setChecked(data_->is_equal_ratio_crop_);

    rotate_angle_edit_->setText(QString::number(data_->rotate_angle));

    luminance_value_->setText(QString::number(data_->luminance));
    luminance_slider_->setValue(data_->luminance);
    contrast_value_->setText(QString::number(data_->contrast));
    contrast_slider_->setValue(data_->contrast);
    saturation_value_->setText(QString::number(data_->saturation));
    saturation_slider_->setValue(data_->saturation);
    picture_alpha_slider_->setValue(data_->image_watermark_datas.count() == 0 ? 0 : data_->image_watermark_datas.first().alpha);
}

void EditSettingView::selectRectChanged(const QRect &rect) {
    select_rect_ = rect;
    crop_ratio_width_edit_->setText(QString::number(rect.width()));
    crop_ratio_height_edit_->setText(QString::number(rect.height()));
}

void EditSettingView::cropWidthEditingConfirm(const QString &text) {
    if (text.toInt() < kCropRectMinW) {
        crop_ratio_width_edit_->setText(QString::number(kCropRectMinW));
    }
    int w = crop_ratio_width_edit_->text().toInt();
    data_->crop_rect.setWidth(w);
    select_rect_.setWidth(w);
    emit Signals::getInstance()->sigSelectRectSetting2Preview(select_rect_);
}

void EditSettingView::cropHeightEditingConfirm(const QString &text) {
    if (text.toInt() < kCropRectMinH) {
        crop_ratio_height_edit_->setText(QString::number(kCropRectMinH));
    }
    int h = crop_ratio_height_edit_->text().toInt();
    data_->crop_rect.setHeight(h);
    select_rect_.setHeight(h);
    emit Signals::getInstance()->sigSelectRectSetting2Preview(select_rect_);
}

void EditSettingView::resetCrop() {
    data_->crop_rect = data_->origin_crop_rect;
    
    crop_ratio_width_edit_->setText(QString::number(data_->crop_rect.width()));
    crop_ratio_height_edit_->setText(QString::number(data_->crop_rect.height()));

    select_rect_ = data_->crop_rect;
    emit Signals::getInstance()->sigSelectRectSetting2Preview(select_rect_);
}

void EditSettingView::alignCenter() {
    int x = (data_->origin_crop_rect.width() - select_rect_.width()) / 2;
    int y = (data_->origin_crop_rect.height() - select_rect_.height()) / 2;
    QRect r = QRect(x, y, select_rect_.width(), select_rect_.height());
    data_->crop_rect = r;
    select_rect_ = r;
    emit Signals::getInstance()->sigSelectRectSetting2Preview(select_rect_);
}

void EditSettingView::equalRatioChanged(int state) {
    data_->is_equal_ratio_crop_ = equal_ratio_checkbox_->isChecked();
    emit Signals::getInstance()->sigEqualRatioCropSetting2Preview(data_->is_equal_ratio_crop_);
}

void EditSettingView::rotateAngleEditingConfirm(const QString &text) {
    int angle = rotate_angle_edit_->text().toInt();
    data_->rotate_angle = angle;
    emit Signals::getInstance()->sigRotateAngleSetting2Preview(data_->rotate_angle);
}

void EditSettingView::resetRotate() {
    data_->rotate_angle = kRotateAngleDefaultValue;
    rotate_angle_edit_->setText(QString::number(data_->rotate_angle));
    emit Signals::getInstance()->sigRotateAngleSetting2Preview(data_->rotate_angle);
}

void EditSettingView::rotateRight90() {
    data_->rotate_angle = 90;
    rotate_angle_edit_->setText(QString::number(data_->rotate_angle));
    emit Signals::getInstance()->sigRotateAngleSetting2Preview(data_->rotate_angle);
}

void EditSettingView::rotateLeft90() {
    data_->rotate_angle = -90;
    rotate_angle_edit_->setText(QString::number(data_->rotate_angle));
    emit Signals::getInstance()->sigRotateAngleSetting2Preview(data_->rotate_angle);
}

void EditSettingView::rotateHorizontalFlip() {
    data_->rotate_angle = 180;
    rotate_angle_edit_->setText(QString::number(data_->rotate_angle));
    emit Signals::getInstance()->sigRotateAngleSetting2Preview(data_->rotate_angle);
}

void EditSettingView::rotateVerticalFlip() {
    data_->rotate_angle = 270;
    rotate_angle_edit_->setText(QString::number(data_->rotate_angle));
    emit Signals::getInstance()->sigRotateAngleSetting2Preview(data_->rotate_angle);
}

void EditSettingView::luminanceChanged() {
    data_->luminance = luminance_slider_->value();
    luminance_value_->setText(QString::number(data_->luminance));
    emit Signals::getInstance()->sigLuminanceSetting2Preview(data_->luminance);
}

void EditSettingView::contrastChanged() {
    data_->contrast = contrast_slider_->value();
    contrast_value_->setText(QString::number(data_->contrast));
    emit Signals::getInstance()->sigContrastSetting2Preview(data_->contrast);
}

void EditSettingView::saturationChanged() {
    data_->saturation = saturation_slider_->value();
    saturation_value_->setText(QString::number(data_->saturation));
    emit Signals::getInstance()->sigSaturationSetting2Preview(data_->saturation);
}

void EditSettingView::resetEffect() {
    data_->luminance = kLuminanceDefaultValue;
    data_->contrast = kContrastDefaultValue;
    data_->saturation = kSaturationDefaultValue;
    luminance_slider_->setValue(data_->luminance);
    contrast_slider_->setValue(data_->contrast);
    saturation_slider_->setValue(data_->saturation);
    luminance_value_->setText(QString::number(data_->luminance));
    contrast_value_->setText(QString::number(data_->contrast));
    saturation_value_->setText(QString::number(data_->saturation));
    emit Signals::getInstance()->sigEffectResetSetting2Preview(data_->luminance, data_->contrast, data_->saturation);
}

void EditSettingView::pictureAlphaChanged() {
    for (auto &item : data_->image_watermark_datas) {
        item.alpha = picture_alpha_slider_->value();
    }
    picture_alpha_value_->setText(QString::number(picture_alpha_slider_->value()));
}

void EditSettingView::changeImageWatermarkSettingData(const QList<ImageWatermarkSettingData> &datas) {
    image_watermark_setting_list_view_->chageData(datas);
    imageWatermarkSettingListViewAdjustHeight(datas.count());
    alphaWidgetVisible(datas.count() > 0);
}

void EditSettingView::loadImageWatermarkSettingData() {
    QTimer::singleShot(0, [=]() {
        auto datas = getImageWatermarkSettingDatas();
        changeImageWatermarkSettingData(datas);
    });
}

void EditSettingView::addImageWatermarkPictureOpenFileDialog() {
    QString title = "选择图片";
    QString directory = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
    QStringList selectedFiles = QFileDialog::getOpenFileNames(this, title, directory, "All Files (*)");
    if (!selectedFiles.isEmpty()) {
        QList<ImageWatermarkSettingData> datas;
        foreach(const QString &file, selectedFiles) {
            ImageWatermarkSettingData data;
            data.file_path = file;
            data.file_name = QFileInfo(file).fileName();
            datas.append(data);
        }
        addImageWatermarkPicture(datas);
    }
}

void EditSettingView::imageWatermarkListItemClicked(const QModelIndex &index) {
    auto data = index.data(Qt::UserRole).value<ImageWatermarkSettingData>();
    QRect rc = image_watermark_setting_list_view_->visualRect(index);
    int posx = image_watermark_setting_list_view_->mapFromGlobal(QCursor::pos()).x();
    int posy = image_watermark_setting_list_view_->mapFromGlobal(QCursor::pos()).y();
    QRect delIconRect = imageWatermarkSettingItemDeteleRect(rc);
    if (posx >= delIconRect.x() && posx <= delIconRect.x() + delIconRect.width()
        && posy >= delIconRect.y() && posy <= delIconRect.y() + delIconRect.height()) {
        deleteImageWatermarkPicture(QList<QString>() << data.file_path);
        return;
    }
    // emit Signals::getInstance()->sigxxx(data.file_path);
}

void EditSettingView::addImageWatermarkPicture(const QList<ImageWatermarkSettingData> &datas) {
    QTimer::singleShot(0, [=]() {
        QList<ImageWatermarkSettingData> newDatas;
        if (addImageWatermarkSettingData(datas, newDatas)) {
            changeImageWatermarkSettingData(newDatas);
        }
    });
}

void EditSettingView::deleteImageWatermarkPicture(const QList<QString> &filePathsToDelete) {
    QTimer::singleShot(0, [=]() {
        QList<ImageWatermarkSettingData> newDatas;
        if (deleteImageWatermarkSettingData(filePathsToDelete, newDatas)) {
            changeImageWatermarkSettingData(newDatas);
        }
    });
}

void EditSettingView::alphaWidgetVisible(bool visible) {
    picture_alpha_label_->setVisible(visible);
    picture_alpha_slider_->setVisible(visible);
    picture_alpha_value_->setVisible(visible);
}

void EditSettingView::imageWatermarkSettingListViewAdjustHeight(int listCount) {
    image_watermark_setting_list_view_->setFixedHeight(100);
    listCount = listCount > 4 ? 4 : listCount;
    int row = listCount / 2 + (listCount % 2 > 0 ? 1 : 0);
    image_watermark_setting_list_view_->setFixedHeight(row * (kImageWatermarkSettingItemSpacing + kImageWatermarkSettingItemHeight) + 4);
}

void EditSettingView::changeTextWatermarkSettingData(const QList<TextWatermarkSettingData> &datas) {
    text_watermark_setting_list_view_->chageData(datas);
    textWatermarkSettingListViewAdjustHeight(datas.count());
    fontWidgetVisible(datas.count() > 0);
}

void EditSettingView::loadTextWatermarkSettingData() {
    QTimer::singleShot(0, [=]() {
        auto datas = getTextWatermarkSettingDatas();
        changeTextWatermarkSettingData(datas);
    });
}

void EditSettingView::addEmptyTextWatermark() {
    TextWatermarkSettingData data{QUuid::createUuid().toString(), "mask"};
    addTextWatermarkSettingItem(QList<TextWatermarkSettingData>() << data);
}

void EditSettingView::textWatermarkListItemClicked(const QModelIndex &index) {
    auto data = index.data(Qt::UserRole).value<TextWatermarkSettingData>();
    QRect rc = text_watermark_setting_list_view_->visualRect(index);
    int posx = text_watermark_setting_list_view_->mapFromGlobal(QCursor::pos()).x();
    int posy = text_watermark_setting_list_view_->mapFromGlobal(QCursor::pos()).y();
    QRect delIconRect = textWatermarkSettingItemDeteleRect(rc);
    if (posx >= delIconRect.x() && posx <= delIconRect.x() + delIconRect.width()
        && posy >= delIconRect.y() && posy <= delIconRect.y() + delIconRect.height()) {
        deleteTextWatermarkSettingItem(QList<QString>() << data.id);
        return;
    }
    // emit Signals::getInstance()->sigxxx(data.file_path);
}

void EditSettingView::addTextWatermarkSettingItem(const QList<TextWatermarkSettingData> &datas) {
    QTimer::singleShot(0, [=]() {
        QList<TextWatermarkSettingData> newDatas;
        if (addTextWatermarkSettingData(datas, newDatas)) {
            changeTextWatermarkSettingData(newDatas);
        }
    });
}

void EditSettingView::deleteTextWatermarkSettingItem(const QList<QString> &idsToDelete) {
    QTimer::singleShot(0, [=]() {
        QList<TextWatermarkSettingData> newDatas;
        if (deleteTextWatermarkSettingData(idsToDelete, newDatas)) {
            changeTextWatermarkSettingData(newDatas);
        }
    });
}

void EditSettingView::fontWidgetVisible(bool visible) {
}

void EditSettingView::textWatermarkSettingListViewAdjustHeight(int listCount) {
    int row = listCount > 4 ? 4 : listCount;
    text_watermark_setting_list_view_->setFixedHeight(row * (kTextWatermarkSettingItemSpacing + kTextWatermarkSettingItemHeight) + 4);
}

} // namespace imageedit