#pragma once
#include <QWidget>
#include <QPointer>
#include <QToolBar>
#include <QAction>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QPixmap>
#include "imageworkspace.h"

// ImageWorkWidget: 对 ImageWorkspace 进行包装，在底部提供工具条操作图片浏览与裁剪。
// 工具条包含：打开图片、适应窗口、原始大小、放大、缩小、裁剪模式开关、导出裁剪结果。
class ImageWorkWidget : public QWidget {
    Q_OBJECT
public:
    explicit ImageWorkWidget(QWidget *parent = nullptr);
    ImageWorkspace* workspace() const { return m_workspace; }

signals:
    void imageLoaded(const QString &path);
    void croppedImageExported(const QString &path);
    void resizedImageExported(const QString &path); // Resize 导出完成

private slots:
    void onOpenImage();
    void onFit();
    void onReset();
    void onZoomIn();
    void onZoomOut();
    void onToggleCrop(bool checked);
    void onExportCrop();
    void onToggleResize(bool checked);
    void onExportResize();
    void onCenterImage();   // Resize 模式：居中图片
    void onToggleFill(bool checked); // 切换拉伸填满模式

    void updateScaleLabel(double scale); // 响应缩放因子更新
    void updateImageSizeLabel(const QSize &size); // 响应图片大小更新

private:
    void setupUi();
    void setupConnections();

    QPointer<ImageWorkspace> m_workspace;
    QToolBar *m_toolBar; // 底部工具条
    QWidget *m_toolContainer; // 用于放置工具条并可自定义样式

    QAction *m_actOpen;
    QAction *m_actFit;
    QAction *m_actReset;
    QAction *m_actZoomIn;
    QAction *m_actZoomOut;
    QAction *m_actCropToggle; // checkable
    QAction *m_actExportCrop;
    QAction *m_actResizeToggle; // checkable
    QAction *m_actExportResize;
    QAction *m_actCenterImage;  // Resize 模式：居中图片
    QAction *m_actToggleFill;   // Resize 模式：切换拉伸填满（checkable）

    QAction *m_actScaleDisplay; // 仅显示当前缩放比
    QAction *m_actImageSizeDisplay; // 仅显示图片实际大小
};