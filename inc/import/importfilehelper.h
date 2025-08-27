#pragma once
#include "task/asynctask.h"
#include "task/itaskcallback.h"
#include "task/taskfactory.h"
#include "widget/progressdialog.h"
#include "conversion/model.h"

#include <QObject>
#include <QVariant>

using namespace QtmTask;
using namespace QtmWidget;

struct SImportFileData {
    QList<QString> filePaths;
};
Q_DECLARE_METATYPE(SImportFileData)

template <typename T>
struct SImportFileResult {
    T value;
    int elapsed;
};
Q_DECLARE_METATYPE(SImportFileResult<QList<SConversionData>>)

class ImportFileCallbackBase : public QObject {
    Q_OBJECT

signals:
    void sigStarted();
    void sigProgress(int percent, const QString &msg);
    void sigSucceeded(const QVariant &result);
    void sigFailed(const QString &error);
    void sigCanceled();
    void sigFinished();
};

template <typename T>
class ImportFileCallback : public ImportFileCallbackBase, public ITaskCallback<T> {
private:
    void onStarted() override {
        emit sigStarted();
    }
    void onProgress(int percent, const std::string &msg) override {
        QString message = QString::fromStdString(msg);
        emit sigProgress(percent, message);
    }
    void onSucceeded(const T &result) override {
        emit sigSucceeded(QVariant::fromValue(result));
    }
    void onFailed(const std::string &error) override {
        QString errorMsg = QString::fromStdString(error);
        emit sigFailed(errorMsg);
    }
    void onCanceled() override {
        emit sigCanceled();
    }
    void onFinished() override {
        emit sigFinished();
    }
};

class ImportFileHelper : public QObject {
    Q_OBJECT

Q_SIGNALS:
    void sigStarted();
    void sigProgress(int percent, const QString &msg);
    void sigSucceeded(const QVariant &result);
    void sigFailed(const QString &error);
    void sigCanceled();
    void sigFinished();

public:
    ImportFileHelper() {}

    template <typename I, typename O>
    void start(typename AsyncTask<I, O>::TaskFunc func, typename AsyncTask<I, O>::Data data) {
        auto callback = std::make_shared<ImportFileCallback<O>>();
        auto task = TaskFactory::instance()->createTask<I, O>(func, callback, data);

        auto dialog = new ProgressDialog(nullptr);
        dialog->setCancelVisible(true);
        dialog->setTitleText(tr("Add Files"));
        dialog->setRange(0, data.value.filePaths.size());
        connect(dialog, &ProgressDialog::canceled, this, [task]() {
            task->cancel();
        });
        connect(callback.get(), &ImportFileCallback<O>::sigStarted, this, &ImportFileHelper::sigStarted);
        connect(callback.get(), &ImportFileCallback<O>::sigCanceled, this, &ImportFileHelper::sigCanceled);
        connect(callback.get(), &ImportFileCallback<O>::sigSucceeded, this, &ImportFileHelper::sigSucceeded);
        connect(callback.get(), &ImportFileCallback<O>::sigFailed, this, &ImportFileHelper::sigFailed);
        connect(callback.get(), &ImportFileCallback<O>::sigFinished, this, [this, dialog]() {
            dialog->accept();
            sigFinished();
        });
        connect(callback.get(), &ImportFileCallback<O>::sigProgress, this, [this, dialog](int percent, const QString &msg) {
            dialog->setProgress(percent);
            dialog->setMessage(msg);
            emit sigProgress(percent, msg);
        });

        task->start();
        dialog->exec();
        if (task->isRunning()) {
            task->cancel();
        }
    }
};