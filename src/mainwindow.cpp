#include "inc/mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent) {
    createUi();
    sigConnect();
}

MainWindow::~MainWindow() {
}

void MainWindow::createUi() {
    setFixedSize(900, 600);
}

void MainWindow::sigConnect() {
}
