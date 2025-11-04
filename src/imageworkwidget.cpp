// ImageWorkWidget 实现文件
// 提供一个包含 ImageWorkspace 的复合控件，底部工具条用于：
//  打开图片 / 适应窗口 / 原始大小 / 放大 / 缩小 / 裁剪模式切换 / 导出裁剪结果
// 使用方式：
//   auto w = new ImageWorkWidget(parent);
//   布局后即可交互；支持直接拖动工具条按钮进行图像操作。
#include "imageworkwidget.h"
#include "core/theme.h"
#include "core/object.h"

#include <QLineEdit>
#include <QLabel>
#include <QStyle>
#include <QSpacerItem>
#include <QDebug>

#define SHOW_TESTTOOLBAR 0

ImageWorkWidget::ImageWorkWidget(QWidget *parent) : QWidget(parent) {
    setupUi();
    setupConnections();
}

void ImageWorkWidget::setupUi() {
    m_workspace = new ImageWorkspace(this);

    m_toolBar = new QWidget(this);
    m_toolBar->setFixedHeight(32);

    auto toolBarLayout = new QHBoxLayout(m_toolBar);
    toolBarLayout->setContentsMargins(0, 0, 0, 0);
    toolBarLayout->setSpacing(8);

    toolBarLayout->addStretch();

    m_FitBtn = new QtmWidget::IconButton(this);
    m_FitBtn->setFixedSize(24, 24);
    m_FitBtn->setIconSize(24, 24);
    m_FitBtn->setFourPixmapPath(QString(":/QtmImg/img/%1/v16/icon24/icon24_fit.svg").arg(QtmCore::Theme::currentTheme()));
    toolBarLayout->addWidget(m_FitBtn);

    m_ZoomOutBtn = new QtmWidget::IconButton(this);
    m_ZoomOutBtn->setFixedSize(24, 24);
    m_ZoomOutBtn->setIconSize(24, 24);
    m_ZoomOutBtn->setFourPixmapPath(QString(":/QtmImg/img/%1/v16/icon24/icon24_zoom_out.svg").arg(QtmCore::Theme::currentTheme()));
    toolBarLayout->addWidget(m_ZoomOutBtn);

    m_ZoomSlider = new QSlider(Qt::Horizontal, this);
    m_ZoomSlider->setFixedWidth(100);
    m_ZoomSlider->setRange(5, 500);
    m_ZoomSlider->setPageStep(1);
    toolBarLayout->addWidget(m_ZoomSlider);

    m_ZoomInBtn = new QtmWidget::IconButton(this);
    m_ZoomInBtn->setFixedSize(24, 24);
    m_ZoomInBtn->setIconSize(24, 24);
    m_ZoomInBtn->setFourPixmapPath(QString(":/QtmImg/img/%1/v16/icon24/icon24_zoom_enlarge.svg").arg(QtmCore::Theme::currentTheme()));
    toolBarLayout->addWidget(m_ZoomInBtn);

    m_ZoomCbb = new QComboBox(this);
    m_ZoomCbb->setFixedSize(70, 24);
    for (int i = 5; i <= 500; i+=5)
    {
        m_ZoomCbb->addItem(QString("%1%").arg(i), i);
    }
    toolBarLayout->addWidget(m_ZoomCbb);

    toolBarLayout->addStretch();

    //
    m_testToolBar = new QToolBar(this);
    m_testToolBar->setIconSize(QSize(16,16));
    m_testToolBar->setMovable(false);
    m_testToolBar->setFloatable(false);
    m_testToolBar->setOrientation(Qt::Horizontal);

    // Actions
    m_actOpen = new QAction(tr("打开"), this);
    m_actFit = new QAction(tr("适应"), this);
    m_actReset = new QAction(tr("原始"), this);
    m_actZoomIn = new QAction(tr("放大"), this);
    m_actZoomOut = new QAction(tr("缩小"), this);
    m_actCropToggle = new QAction(tr("裁剪"), this);
    m_actCropToggle->setCheckable(true);
    m_actExportCrop = new QAction(tr("导出裁剪"), this);
    m_actResizeToggle = new QAction(tr("调整大小"), this);
    m_actResizeToggle->setCheckable(true);
    m_actExportResize = new QAction(tr("导出调整"), this);
    m_actCenterImage = new QAction(tr("居中"), this);
    m_actToggleFill = new QAction(tr("拉伸"), this);
    m_actToggleFill->setCheckable(true);

    m_actScaleDisplay = new QAction("100%", this);
    m_actScaleDisplay->setEnabled(false); // 仅显示

    m_actImageSizeDisplay = new QAction("0 × 0", this);
    m_actImageSizeDisplay->setEnabled(false); // 仅显示

    // 添加到工具条
    m_testToolBar->addAction(m_actOpen);
    m_testToolBar->addSeparator();
    m_testToolBar->addAction(m_actFit);
    m_testToolBar->addAction(m_actReset);
    m_testToolBar->addSeparator();
    m_testToolBar->addAction(m_actZoomIn);
    m_testToolBar->addAction(m_actZoomOut);
    m_testToolBar->addSeparator();
    m_testToolBar->addAction(m_actCropToggle);
    m_testToolBar->addAction(m_actExportCrop);
    m_testToolBar->addSeparator();
    m_testToolBar->addAction(m_actResizeToggle);
    m_testToolBar->addAction(m_actCenterImage);
    m_testToolBar->addAction(m_actToggleFill);
    m_testToolBar->addAction(m_actExportResize);
    m_testToolBar->addSeparator();
    m_testToolBar->addAction(m_actScaleDisplay);
    m_testToolBar->addAction(m_actImageSizeDisplay);

    // 布局：工作区 + 底部工具条
    QVBoxLayout *v = new QVBoxLayout(this);
    v->setContentsMargins(0,0,0,0);
    v->setSpacing(0);
    v->addWidget(m_workspace);
    v->addWidget(m_testToolBar);
    v->addWidget(m_toolBar);
    setLayout(v);

#if !SHOW_TESTTOOLBAR
    m_testToolBar->setVisible(false);
#else
    m_toolBar->setVisible(false);
#endif
}

void ImageWorkWidget::setupConnections() {
    connect(m_FitBtn, &QtmWidget::IconButton::clicked, this, &ImageWorkWidget::onFit);
    connect(m_ZoomInBtn, &QtmWidget::IconButton::clicked, this, &ImageWorkWidget::onZoomIn);
    connect(m_ZoomOutBtn, &QtmWidget::IconButton::clicked, this, &ImageWorkWidget::onZoomOut);
    connect(m_ZoomSlider, &QSlider::valueChanged, this, &ImageWorkWidget::onZoomToPercent);
    connect(m_ZoomCbb, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &ImageWorkWidget::onZoomCbbIndexChanged);

    //
    connect(m_actOpen, &QAction::triggered, this, &ImageWorkWidget::onOpenImage);
    connect(m_actFit, &QAction::triggered, this, &ImageWorkWidget::onFit);
    connect(m_actReset, &QAction::triggered, this, &ImageWorkWidget::onReset);
    connect(m_actZoomIn, &QAction::triggered, this, &ImageWorkWidget::onZoomIn);
    connect(m_actZoomOut, &QAction::triggered, this, &ImageWorkWidget::onZoomOut);
    connect(m_actCropToggle, &QAction::toggled, this, &ImageWorkWidget::onToggleCrop);
    connect(m_actExportCrop, &QAction::triggered, this, &ImageWorkWidget::onExportCrop);
    connect(m_actResizeToggle, &QAction::toggled, this, &ImageWorkWidget::onToggleResize);
    connect(m_actExportResize, &QAction::triggered, this, &ImageWorkWidget::onExportResize);
    connect(m_actCenterImage, &QAction::triggered, this, &ImageWorkWidget::onCenterImage);
    connect(m_actToggleFill, &QAction::toggled, this, &ImageWorkWidget::onToggleFill);
    if (m_workspace) {
        connect(m_workspace, &ImageWorkspace::scaleFactorChanged, this, &ImageWorkWidget::updateScaleLabel);
        connect(m_workspace, &ImageWorkspace::imageSizeChanged, this, &ImageWorkWidget::updateImageSizeLabel);
    }
}

void ImageWorkWidget::onOpenImage() {
    QString file = QFileDialog::getOpenFileName(this, tr("选择图片"), QString(), tr("Images (*.png *.jpg *.jpeg *.bmp *.webp)"));
    if (file.isEmpty()) return;
    if (m_workspace) {
        m_workspace->loadImage(file);
        emit imageLoaded(file);
    }
}

void ImageWorkWidget::onFit() { if (m_workspace) m_workspace->setFitView(); }
void ImageWorkWidget::onReset() { if (m_workspace) m_workspace->resetView(); }
void ImageWorkWidget::onZoomIn() { if (m_workspace) m_workspace->zoomIn(); }
void ImageWorkWidget::onZoomOut() { if (m_workspace) m_workspace->zoomOut(); }
void ImageWorkWidget::onZoomToPercent(int percent) { if (m_workspace) m_workspace->zoomToPercent(percent); }

void ImageWorkWidget::onToggleCrop(bool checked) {
    if (!m_workspace) return;
    m_workspace->setWorkspaceMode(checked?ImageWorkspace::ModeCrop:ImageWorkspace::ModeNone);
    // 切换后若进入裁剪模式，重置为整图裁剪；退出则清除
    if (checked) {
        m_workspace->resetCropRect();
    }
}

void ImageWorkWidget::onToggleResize(bool checked) {
    if (!m_workspace) return;
    m_workspace->setWorkspaceMode(checked?ImageWorkspace::ModeResize:ImageWorkspace::ModeNone);
}

void ImageWorkWidget::onExportCrop() {
    if (!m_workspace) return;
    QPixmap cropped = m_workspace->getCroppedImage();
    if (cropped.isNull()) return;
    QString file = QFileDialog::getSaveFileName(this, tr("保存裁剪"), QString(), tr("PNG (*.png);;JPG (*.jpg);;WEBP (*.webp);;BMP (*.bmp)"));
    if (file.isEmpty()) return;
    
    // 根据后缀决定保存格式
    QString suffix = QFileInfo(file).suffix().toLower();
    if (suffix.isEmpty()) {
        file += ".png";
        suffix = "png";
    }
    bool ok = false;
    if (suffix == "jpg" || suffix == "jpeg") {
        ok = cropped.save(file, "JPG", 95);
    } else if (suffix == "webp") {
        ok = cropped.save(file, "WEBP", 90);
    } else if (suffix == "bmp") {
        ok = cropped.save(file, "BMP");
    } else { // png / others
        ok = cropped.save(file, "PNG");
    }
    if (ok) emit croppedImageExported(file);
}

void ImageWorkWidget::onExportResize() {
    if (!m_workspace) return;
    if (m_workspace->workspaceMode() != ImageWorkspace::ModeResize) return; // 仅在 Resize 模式
    QImage img = m_workspace->getResizeResultImage();
    if (img.isNull()) return;
    QString file = QFileDialog::getSaveFileName(this, tr("保存调整结果"), QString(), tr("PNG (*.png);;JPG (*.jpg);;WEBP (*.webp);;BMP (*.bmp)"));
    if (file.isEmpty()) return;

    // 根据后缀决定保存格式；默认 PNG 保留透明
    QString suffix = QFileInfo(file).suffix().toLower();
    if (suffix.isEmpty()) {
        file += ".png";
        suffix = "png";
    }
    bool ok = false;
    if (suffix == "jpg" || suffix == "jpeg") {
        QImage opaque = img.convertToFormat(QImage::Format_RGB32);
        ok = opaque.save(file, "JPG", 95);
    } else if (suffix == "webp") {
        ok = img.save(file, "WEBP", 90);
    } else if (suffix == "bmp") {
        ok = img.save(file, "BMP");
    } else { // png / others
        ok = img.save(file, "PNG");
    }
    if (ok) emit resizedImageExported(file);
}

void ImageWorkWidget::onCenterImage() {
    if (m_workspace) m_workspace->centerImageInCanvas();
}

void ImageWorkWidget::onToggleFill(bool checked) {
    if (m_workspace) m_workspace->toggleFillMode();
}

void ImageWorkWidget::onZoomCbbIndexChanged(int index) {
    if (index < 0) return;
    QString text = m_ZoomCbb->itemText(index);
    text.chop(1); // 去掉 %
    bool ok = false;
    int percent = text.toInt(&ok);
    if (ok) {
        onZoomToPercent(percent);
    }
}

void ImageWorkWidget::updateScaleLabel(double scale) {
    int percent = qRound(scale * 100.0);
    m_actScaleDisplay->setText(QString::number(percent) + "%");

    QtmCore::blockSignalsFunc(m_ZoomCbb, [&]() {
        m_ZoomCbb->setEditable(true);
        m_ZoomCbb->lineEdit()->setReadOnly(true);
        m_ZoomCbb->lineEdit()->setText(QString::number(percent) + "%");
    });
    QtmCore::blockSignalsFunc(m_ZoomSlider, [&]() {
        if(percent < m_ZoomSlider->minimum()) percent = m_ZoomSlider->minimum();
        if(percent > m_ZoomSlider->maximum()) percent = m_ZoomSlider->maximum();
        m_ZoomSlider->setValue(percent);
    });
}

void ImageWorkWidget::updateImageSizeLabel(const QSize &size) {
    m_actImageSizeDisplay->setText(QString("%1 × %2").arg(size.width()).arg(size.height()));
}