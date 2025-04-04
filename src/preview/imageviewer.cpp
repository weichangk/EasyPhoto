#include "preview/imageviewer.h"
#include <QDebug>

ImageViewer::ImageViewer(QWidget *parent) :
    QGraphicsView(parent),
    m_scene(new QGraphicsScene(this)),
    m_pixmapItem(new QGraphicsPixmapItem()),
    m_scaleFactor(1.0),
    m_isPanning(false) {
    setScene(m_scene);
    m_scene->addItem(m_pixmapItem);

    setDragMode(QGraphicsView::NoDrag);
    setRenderHint(QPainter::Antialiasing);
    setRenderHint(QPainter::SmoothPixmapTransform);
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
}

void ImageViewer::loadImage(const QString &filePath) {
    QPixmap pixmap(filePath);
    if (pixmap.isNull()) {
        qDebug() << "Failed to load image!";
        return;
    }
    m_pixmapItem->setPixmap(pixmap);
    m_scene->setSceneRect(pixmap.rect());
    setFitView();
}

void ImageViewer::setFitView() {
    fitInView(m_pixmapItem, Qt::KeepAspectRatio);
    m_scaleFactor = 1.0;
}

void ImageViewer::resetView() {
    resetTransform();
    m_scaleFactor = 1.0;
}

void ImageViewer::zoomIn() {
    scale(1.2, 1.2);
    m_scaleFactor *= 1.2;
}

void ImageViewer::zoomOut() {
    scale(1 / 1.2, 1 / 1.2);
    m_scaleFactor *= 1 / 1.2;
}

void ImageViewer::wheelEvent(QWheelEvent *event) {
    if (event->angleDelta().y() > 0) {
        zoomIn();
    } else {
        zoomOut();
    }
}

void ImageViewer::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        m_isPanning = true;
        m_lastMousePos = event->pos();
        setCursor(Qt::ClosedHandCursor);
    }
    QGraphicsView::mousePressEvent(event);
}

void ImageViewer::mouseMoveEvent(QMouseEvent *event) {
    if (m_isPanning) {
        QPointF delta = mapToScene(event->pos()) - mapToScene(m_lastMousePos);
        translate(delta.x(), delta.y());
        m_lastMousePos = event->pos();
    }
    QGraphicsView::mouseMoveEvent(event);
}

void ImageViewer::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        m_isPanning = false;
        setCursor(Qt::ArrowCursor);
    }
    QGraphicsView::mouseReleaseEvent(event);
}
