#pragma once
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QRadioButton>
#include <QSlider>

namespace imageupscayl {
class ImageUpscaylStepView : public QWidget {
    Q_OBJECT
public:
    explicit ImageUpscaylStepView(QWidget *parent = nullptr);
    ~ImageUpscaylStepView();

protected:
    void createUi();
    void sigConnect();

private:
    QLabel *step1_lab_ = nullptr;
    QPushButton *select_image_btn_ = nullptr;
    QPushButton *select_folder_btn_ = nullptr;
    QLabel *step2_lab_ = nullptr;
    QLabel *select_model_lab_ = nullptr;
    QComboBox *select_model_cmb_ = nullptr;
    QLabel *step3_lab_ = nullptr;
    QLabel *select_scale_lab_ = nullptr;
    QSlider *select_scale_sld_ = nullptr;
    QLabel *step4_lab_ = nullptr;
    QLabel *select_output_folder_lab_ = nullptr;
    QPushButton *select_output_folder_btn_ = nullptr;
    QLabel *step5_lab_ = nullptr;
    QPushButton *upscayl_btn_ = nullptr;
};
} // namespace imageupscayl