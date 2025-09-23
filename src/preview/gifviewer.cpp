#include "preview/gifviewer.h"

GifViewer::GifViewer(QWidget *parent) :
    QWidget(parent) {
    createUi();
    connectSig();
}

void GifViewer::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    m_pPlayBtn->setGeometry((width() - m_pPlayBtn->width()) / 2, height() - (m_pPlayBtn->height()) / 2, width(), height());
}

void GifViewer::enterEvent(QEvent *event) {
    QWidget::enterEvent(event);
    m_pPlayBtn->setVisible(true);
}

void GifViewer::leaveEvent(QEvent *event) {
    QWidget::leaveEvent(event);
    m_pPlayBtn->setVisible(false);
}

void GifViewer::createUi() {
    setObjectName("GifViewer");
    setAttribute(Qt::WA_StyledBackground);

    m_pExitBtn = new IconButton(this);
    m_pExitBtn->setFixedSize(24, 24);
    m_pExitBtn->setIconSize(24, 24);
    m_pExitBtn->setFourPixmapPath(":/QtmImg/img/dark/icon/icon_state/icon24/icon24_delete.png");

    m_pPlayBtn = new IconButton(this);
    m_pPlayBtn->setFixedSize(24, 24);
    m_pPlayBtn->setIconSize(24, 24);
    m_pPlayBtn->setFourPixmapPath(":/QtmImg/img/dark/icon/icon_state/icon24/icon24_delete.png");
    m_pPlayBtn->setVisible(false);

    m_pGifLabel = new QLabel(this);
    m_pGifMovie = new QMovie(this);
    m_pGifLabel->setMovie(m_pGifMovie);
    // m_pGifLabel->setScaledContents(true);

    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    mainLayout->addWidget(m_pExitBtn, 0, Qt::AlignRight);
    mainLayout->addWidget(m_pGifLabel, 0, Qt::AlignCenter);
}

void GifViewer::connectSig() {
    connect(m_pExitBtn, &IconButton::clicked, this, &GifViewer::onExitBtnClicked);
    connect(m_pPlayBtn, &IconButton::clicked, this, &GifViewer::onPlayBtnClicked);
}

void GifViewer::start() {
    m_pGifMovie->start();
}

void GifViewer::stop() {
    m_pGifMovie->stop();
}

void GifViewer::preview(const QString &path) {
    m_pGifMovie->stop();
    m_pGifMovie->setFileName(path);
    m_pGifMovie->start();
}

void GifViewer::exit() {
    stop();
}

void GifViewer::onExitBtnClicked() {
    exit();
}

void GifViewer::onPlayBtnClicked() {
    if(m_pPlayBtn->fourPixmapPath().contains("start")) {
        m_pPlayBtn->setFourPixmapPath(":/QtmImg/img/dark/icon/icon_state/icon24/icon24_delete.png");
        stop();
    } else {
        m_pPlayBtn->setFourPixmapPath(":/QtmImg/img/dark/icon/icon_state/icon24/icon24_delete.png");
        start();
    }
}