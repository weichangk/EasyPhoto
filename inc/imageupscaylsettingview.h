#pragma once
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QSlider>

namespace imageupscayl {
class ImageUpscaylSettingView : public QWidget {
    Q_OBJECT
public:
    explicit ImageUpscaylSettingView(QWidget *parent = nullptr);
    ~ImageUpscaylSettingView();

protected:
    void createUi();
    void sigConnect();

private:
    QLabel *model_lab_ = nullptr;
    QPushButton *model_btn_ = nullptr;

    QLabel *fmt_lab_ = nullptr;
    QPushButton *png_fmt_btn_ = nullptr;
    QPushButton *jpg_fmt_btn_ = nullptr;
    QPushButton *webp_fmt_btn_ = nullptr;

    QLabel *scale_lab_ = nullptr;
    QSlider *scale_slider_ = nullptr;

    QLabel *compression_lab_ = nullptr;
    QSlider *compression_slider_ = nullptr;

    QLabel *output_folder_lab_ = nullptr;
    QPushButton *output_folder_btn_ = nullptr;

    QLabel *reset_lab_ = nullptr;
    QPushButton *reset_btn_ = nullptr;
};
} // namespace imageupscayl