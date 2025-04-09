#include "downloader/view.h"

DownloaderView::DownloaderView(QWidget *parent) :
    QWidget(parent) {
    createUi();
    connectSig();
}

void DownloaderView::createUi() {
    setObjectName("DownloaderView");
    setAttribute(Qt::WA_StyledBackground);

    QLabel *label = new QLabel("DownloaderView", this);
    auto layout = new QVBoxLayout(this);
    layout->addWidget(label, 0, Qt::AlignCenter);
}

void DownloaderView::connectSig() {
}