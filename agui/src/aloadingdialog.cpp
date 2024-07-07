/*
 * @Author: weick
 * @Date: 2024-07-06 09:10:37
 * @Last Modified by: weick
 * @Last Modified time: 2024-07-06 21:42:33
 */

#include "inc/aloadingdialog.h"
#include "../awidget/inc/avboxlayout.h"

LoadingWorker::LoadingWorker(QObject *parent) :
    QThread(parent) {
}

LoadingWorker::~LoadingWorker() {
}

void LoadingWorker::run() {
    if (do_work_) {
        do_work_();
    }
}

void LoadingWorker::setDoWork(std::function<void()> work) {
    do_work_ = work;
}

ALoadingDialog::ALoadingDialog(QDialog *parent) :
    ABaseDialog(parent),
    progress_bar_(new AProgressBar(this)),
    cancel_btn_(new APushButton(this)),
    loading_worker_(new LoadingWorker(this)) {
    createUi();
    changeLanguage();
    sigConnect();
}

ALoadingDialog::~ALoadingDialog() {
    // Loading_worker_->quit();
    // Loading_worker_->wait();
}

void ALoadingDialog::setDoWork(std::function<void()> work) {
    loading_worker_->setDoWork(work);
}

int ALoadingDialog::exec() {
    loading_worker_->start();
    return ABaseDialog::exec();
}

void ALoadingDialog::createUi() {
    auto layout = new AVBoxLayout(this);
    progress_bar_->setRange(0, 0);
    layout->addWidget(progress_bar_);
    layout->addWidget(cancel_btn_);
}

void ALoadingDialog::changeLanguage() {
    cancel_btn_->setText(tr("Cancel"));
}

void ALoadingDialog::sigConnect() {
    connect(loading_worker_, &LoadingWorker::finished, this, &QDialog::accept);
}