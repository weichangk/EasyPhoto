#include "mainview.h"

MainView::MainView(QWidget *parent) :
    QWidget(parent) {
    createUi();
    connectSig();
}

void MainView::createUi() {
    setMinimumSize(1096, 680);
    setFixedSize(1096, 680);
    // setWindowFlags(Qt::FramelessWindowHint);
}

void MainView::connectSig() {
}