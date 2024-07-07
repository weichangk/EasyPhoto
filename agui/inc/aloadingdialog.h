/*
 * @Author: weick
 * @Date: 2024-07-06 09:10:17
 * @Last Modified by: weick
 * @Last Modified time: 2024-07-06 21:45:36
 */

#pragma once
#include "agui_global.h"
#include "abasedialog.h"
#include "../awidget/inc/apushbutton.h"
#include "../awidget/inc/aprogressbar.h"
#include <QThread>

class LoadingWorker : public QThread {
    Q_OBJECT
public:
    explicit LoadingWorker(QObject *parent = nullptr);
    ~LoadingWorker();
    void run() override;
    void setDoWork(std::function<void()> work);

private:
    std::function<void()> do_work_ = nullptr;
};

class AGUI_EXPORT ALoadingDialog : public ABaseDialog {
    Q_OBJECT

public:
    explicit ALoadingDialog(QDialog *parent = nullptr);
    ~ALoadingDialog();
    void setDoWork(std::function<void()> work);

public:
    int exec() override;

protected:
    void createUi() override;
    void changeLanguage() override;
    void sigConnect() override;

private:
    AProgressBar *progress_bar_ = nullptr;
    APushButton *cancel_btn_ = nullptr;
    LoadingWorker *loading_worker_ = nullptr;
};