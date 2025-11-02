// ImageWorkWidget 实现文件
// 提供一个包含 ImageWorkspace 的复合控件，底部工具条用于：
//  打开图片 / 适应窗口 / 原始大小 / 放大 / 缩小 / 裁剪模式切换 / 导出裁剪结果
// 使用方式：
//   auto w = new ImageWorkWidget(parent);
//   布局后即可交互；支持直接拖动工具条按钮进行图像操作。
#include "imageworkwidget.h"
#include <QLabel>
#include <QStyle>
#include <QSpacerItem>
#include <QDebug>

ImageWorkWidget::ImageWorkWidget(QWidget *parent) : QWidget(parent) {
    setupUi();
    setupConnections();
}

void ImageWorkWidget::setupUi() {
    m_workspace = new ImageWorkspace(this);
    m_toolBar = new QToolBar(this);
    m_toolBar->setIconSize(QSize(16,16));
    m_toolBar->setMovable(false);
    m_toolBar->setFloatable(false);
    m_toolBar->setOrientation(Qt::Horizontal);

    // Actions
    m_actOpen = new QAction(tr("打开"), this);
    m_actFit = new QAction(tr("适应"), this);
    m_actReset = new QAction(tr("原始"), this);
    m_actZoomIn = new QAction(tr("放大"), this);
    m_actZoomOut = new QAction(tr("缩小"), this);
    m_actCropToggle = new QAction(tr("裁剪"), this);
    m_actCropToggle->setCheckable(true);
    m_actExportCrop = new QAction(tr("导出裁剪"), this);

    m_actScaleDisplay = new QAction("100%", this);
    m_actScaleDisplay->setEnabled(false); // 仅显示

    // 添加到工具条
    m_toolBar->addAction(m_actOpen);
    m_toolBar->addSeparator();
    m_toolBar->addAction(m_actFit);
    m_toolBar->addAction(m_actReset);
    m_toolBar->addSeparator();
    m_toolBar->addAction(m_actZoomIn);
    m_toolBar->addAction(m_actZoomOut);
    m_toolBar->addSeparator();
    m_toolBar->addAction(m_actCropToggle);
    m_toolBar->addAction(m_actExportCrop);
    m_toolBar->addSeparator();
    m_toolBar->addAction(m_actScaleDisplay);

    // 布局：工作区 + 底部工具条
    QVBoxLayout *v = new QVBoxLayout(this);
    v->setContentsMargins(0,0,0,0);
    v->setSpacing(0);
    v->addWidget(m_workspace);
    v->addWidget(m_toolBar);
    setLayout(v);
}

void ImageWorkWidget::setupConnections() {
    connect(m_actOpen, &QAction::triggered, this, &ImageWorkWidget::onOpenImage);
    connect(m_actFit, &QAction::triggered, this, &ImageWorkWidget::onFit);
    connect(m_actReset, &QAction::triggered, this, &ImageWorkWidget::onReset);
    connect(m_actZoomIn, &QAction::triggered, this, &ImageWorkWidget::onZoomIn);
    connect(m_actZoomOut, &QAction::triggered, this, &ImageWorkWidget::onZoomOut);
    connect(m_actCropToggle, &QAction::toggled, this, &ImageWorkWidget::onToggleCrop);
    connect(m_actExportCrop, &QAction::triggered, this, &ImageWorkWidget::onExportCrop);

    if (m_workspace) {
        connect(m_workspace, &ImageWorkspace::scaleFactorChanged, this, &ImageWorkWidget::updateScaleLabel);
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

void ImageWorkWidget::onToggleCrop(bool checked) {
    if (!m_workspace) return;
    m_workspace->setWorkspaceMode(checked?ImageWorkspace::ModeCrop:ImageWorkspace::ModeNone);
    // 切换后若进入裁剪模式，重置为整图裁剪；退出则清除
    if (checked) {
        m_workspace->resetCropRect();
    }
}

void ImageWorkWidget::onExportCrop() {
    if (!m_workspace) return;
    QPixmap cropped = m_workspace->getCroppedImage();
    if (cropped.isNull()) return;
    QString file = QFileDialog::getSaveFileName(this, tr("保存裁剪"), QString(), tr("PNG (*.png);;JPG (*.jpg)"));
    if (file.isEmpty()) return;
    cropped.save(file);
    emit croppedImageExported(file);
}

void ImageWorkWidget::updateScaleLabel(double scale) {
    int percent = qRound(scale * 100.0);
    m_actScaleDisplay->setText(QString::number(percent) + "%");
}