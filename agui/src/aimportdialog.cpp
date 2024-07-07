/*
 * @Author: weick
 * @Date: 2024-07-06 09:10:37
 * @Last Modified by: weick
 * @Last Modified time: 2024-07-06 21:42:33
 */

#include "inc/aimportdialog.h"
#include "../awidget/inc/avboxlayout.h"

ImportWorker::ImportWorker(QObject *parent) :
    QThread(parent) {
}

ImportWorker::~ImportWorker() {
}

void ImportWorker::run() {
    if (do_work_) {
        do_work_();
    }
}

void ImportWorker::setDoWork(std::function<void()> work) {
    do_work_ = work;
}

AImportDialog::AImportDialog(QDialog *parent) :
    ABaseDialog(parent),
    progress_bar_(new AProgressBar(this)),
    cancel_btn_(new APushButton(this)),
    import_worker_(new ImportWorker(this)) {
    createUi();
    changeLanguage();
    sigConnect();
}

AImportDialog::~AImportDialog() {
    // import_worker_->quit();
    // import_worker_->wait();
}

void AImportDialog::setDoWork(std::function<void()> work) {
    import_worker_->setDoWork(work);
}

int AImportDialog::exec() {
    import_worker_->start();
    return ABaseDialog::exec();
}

void AImportDialog::createUi() {
    auto layout = new AVBoxLayout(this);
    progress_bar_->setRange(0, 0);
    layout->addWidget(progress_bar_);
    layout->addWidget(cancel_btn_);
}

void AImportDialog::changeLanguage() {
    cancel_btn_->setText(tr("Cancel"));
}

void AImportDialog::sigConnect() {
    connect(import_worker_, &ImportWorker::finished, this, &QDialog::accept);
}