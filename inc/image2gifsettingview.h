#pragma once
#include "control/lineedit.h"

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QIntValidator>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QRadioButton>

namespace image2gif {
class Image2GifSettingView : public QWidget {
    Q_OBJECT
public:
    explicit Image2GifSettingView(QWidget *parent = nullptr);
    ~Image2GifSettingView();

protected:
    void createUi();
    void sigConnect();

private:
    void init();
    void setWHEditEnabled(bool enable);
    void slotExportButtonClicked();
    void slotResolutionComboCurrentTextChanged(const QString &text);
    void slotWEditingConfirm(const QString &text);
    void slotHEditingConfirm(const QString &text);
    void slotFpsComboCurrentTextChanged(const QString &text);
    void slotQualityComboCurrentTextChanged(const QString &text);
    void slotRepeatRadioToggled(bool checked);
    
private:
    QLabel *resolution_label_;
    QComboBox *resolution_combo_;
    QLabel *size_label_;
    LineEdit *w_edit_;
    LineEdit *h_edit_;
    QIntValidator *w_edit_validator_;
    QIntValidator *h_edit_validator_;
    QLabel *fps_label_;
    QComboBox *fps_combo_;
    QLabel *quality_label_;
    QComboBox *quality_combo_;
    QRadioButton *repeat_radio_;
    QPushButton *export_button_;
};
} // namespace image2gif