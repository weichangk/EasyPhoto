/*
 * @Author: weick
 * @Date: 2024-03-23 11:13:49
 * @Last Modified by: weick
 * @Last Modified time: 2024-06-03 07:50:47
 */

#include "inc/image2gifpreviewview.h"
#include "inc/signals.h"
#include "../awidget/inc/alabel.h"
#include "../awidget/inc/awidget.h"
#include "../awidget/inc/avboxlayout.h"
#include "../awidget/inc/ahboxlayout.h"
#include <QTimer>
#include <QEvent>
#include <QMouseEvent>
#include <QPoint>
#include <QMessageBox>

namespace image2gif {
Image2GifPreviewView::Image2GifPreviewView(QWidget *parent) :
    ABaseWidget(parent) {
    createUi();
    sigConnect();
    changeLanguage();
}

Image2GifPreviewView::~Image2GifPreviewView() {
}

void Image2GifPreviewView::createUi() {
    auto mainLay = new AVBoxLayout(this);
    preview_widget_ = new AWidget(this);
    mainLay->addWidget(preview_widget_, 1);
    preview_pixmap_label_ = new ALabel(preview_widget_);
    preview_pixmap_label_->installEventFilter(this);
    preview_pixmap_label_->setScaledContents(false);
    auto preview_pixmap_label_layout = new AHBoxLayout();
    preview_pixmap_label_layout->addStretch();
    preview_pixmap_label_layout->addWidget(preview_pixmap_label_);
    preview_pixmap_label_layout->addStretch();
    auto preview_widget_layout = new AVBoxLayout(preview_widget_);
    preview_widget_layout->addStretch();
    preview_widget_layout->addLayout(preview_pixmap_label_layout);
    preview_widget_layout->addStretch();

    preview_movie_ = new QMovie();

    preview_button_ = new APreviewButton();
    preview_button_->installEventFilter(this);
    preview_button_->setFixedSize(96, 96);
    preview_button_->setIconSize(QSize(96, 96));
    preview_button_->setNormalIcon(QPixmap(":/agui/res/image/loading-96.png"));
}

void Image2GifPreviewView::changeLanguage() {
}

void Image2GifPreviewView::sigConnect() {
    connect(SIGNALS, &Signals::sigListItemDataSelected, this, &Image2GifPreviewView::preViewDataSelected);
    connect(preview_button_, &APreviewButton::sigClicked, this, &Image2GifPreviewView::slotPreviewButtonClicked);
    connect(SIGNALS, &Signals::sigPreviewEnd, this, &Image2GifPreviewView::slotPreviewEnd);
    connect(preview_movie_, &QMovie::finished, this, &Image2GifPreviewView::slotPreviewMovieFinished);
}

bool Image2GifPreviewView::eventFilter(QObject *watched, QEvent *event) {
    if (watched == preview_pixmap_label_ || watched == preview_button_) {
        if (event->type() == QEvent::Enter) {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
            if (mouseEvent) {
                QPoint localPoint(0, 0);
                QPoint pos = preview_pixmap_label_->mapToGlobal(localPoint) + QPoint((preview_pixmap_label_->width() - preview_button_->width()) / 2, (preview_pixmap_label_->height() - preview_button_->height()) / 2);
                preview_button_->move(pos);
                preview_button_->setVisible(true);
            }
        }
        else if (event->type() == QEvent::Leave) {
            preview_button_->setVisible(false);
        }
    }
    return ABaseWidget::eventFilter(watched, event);
}
void Image2GifPreviewView::preViewDataSelected(Data *data) {
    if (data == nullptr) {
        return;
    }
    loadSelectedPixmap(data->file_path);
    updateSelectedPixmapSize();
}

void Image2GifPreviewView::loadSelectedPixmap(const QString &path) {
    if (path.isEmpty()) {
        return;
    }
    QPixmap pixmap(path);
    if (pixmap.isNull()) {
        return;
    }
    preview_pixmap_ = pixmap;
    // preview_pixmap_label_->setPixmap(pixmap);
}

void Image2GifPreviewView::updateSelectedPixmapSize() {
    if (preview_pixmap_.isNull()) {
        return;
    }

    QSize labelSize = preview_widget_->size();
    QSize pixmapSize = preview_pixmap_.size();

    if (pixmapSize.width() > labelSize.width() || pixmapSize.height() > labelSize.height()) {
        preview_pixmap_ = preview_pixmap_.scaled(labelSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    }

    preview_pixmap_label_->setPixmap(preview_pixmap_);
}

void Image2GifPreviewView::slotPreviewButtonClicked() {
    preview_button_->setVisible(false);
    if (preview_movie_->state() == QMovie::Running) {
        preview_pixmap_label_->setMovie(nullptr);
        preview_movie_->stop();
    } else {
        emit SIGNALS -> sigPreviewStart();
    }
}

void Image2GifPreviewView::slotPreviewEnd(bool state, const QString &filePath, const QString &error) {
    if (state) {
        preview_movie_->setFileName(filePath);
        preview_pixmap_label_->setMovie(preview_movie_);
        preview_movie_->start();
    } else {
        QMessageBox::information(this, "Message Box", "预览失败!", QMessageBox::StandardButton::Ok);
    }
}

void Image2GifPreviewView::slotPreviewMovieFinished() {

}
} // namespace image2gif