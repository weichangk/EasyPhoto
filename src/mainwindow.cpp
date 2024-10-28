/*
 * @Author: weick
 * @Date: 2023-12-05 23:03:42
 * @Last Modified by:   weick
 * @Last Modified time: 2023-12-05 23:03:42
 */

#include "inc/mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    ABaseWidget(parent) {
    createUi();
    sigConnect();
    changeLanguage();
}

MainWindow::~MainWindow() {
}

void MainWindow::createUi() {
    setFixedSize(900, 600);
}

void MainWindow::changeLanguage() {
}

void MainWindow::sigConnect() {
}
