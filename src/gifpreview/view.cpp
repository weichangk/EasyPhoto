#include "gifpreview/view.h"
#include "message/funcchangemessage.h"
#include "funcenum.h"

GifPreviewView::GifPreviewView(QWidget *parent) :
    QWidget(parent) {
    createUi();
    connectSig();
}

void GifPreviewView::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    m_pPlayBtn->setGeometry((width() - m_pPlayBtn->width()) / 2, height() - (m_pPlayBtn->height()) / 2, width(), height());
}

void GifPreviewView::enterEvent(QEvent *event) {
    QWidget::enterEvent(event);
    m_pPlayBtn->setVisible(true);
}

void GifPreviewView::leaveEvent(QEvent *event) {
    QWidget::leaveEvent(event);
    m_pPlayBtn->setVisible(false);
}

void GifPreviewView::createUi() {
    setObjectName("GifPreviewView");
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

void GifPreviewView::connectSig() {
    connect(m_pExitBtn, &IconButton::clicked, this, &GifPreviewView::onExitBtnClicked);
    connect(m_pPlayBtn, &IconButton::clicked, this, &GifPreviewView::onPlayBtnClicked);
}

void GifPreviewView::start() {
    m_pGifMovie->start();
}

void GifPreviewView::stop() {
    m_pGifMovie->stop();
}

void GifPreviewView::preview(const QString &path) {
    m_pGifMovie->stop();
    m_pGifMovie->setFileName(path);
    m_pGifMovie->start();
}

void GifPreviewView::exit() {
    stop();
}

void GifPreviewView::onExitBtnClicked() {
    exit();
    FuncChangeMessage msg(EFunc::FuncUndo);
    presenter()->sendMessage(&msg);
}

void GifPreviewView::onPlayBtnClicked() {
    if(m_pPlayBtn->fourPixmapPath().contains("start")) {
        m_pPlayBtn->setFourPixmapPath(":/QtmImg/img/dark/icon/icon_state/icon24/icon24_delete.png");
        stop();
    } else {
        m_pPlayBtn->setFourPixmapPath(":/QtmImg/img/dark/icon/icon_state/icon24/icon24_delete.png");
        start();
    }
}