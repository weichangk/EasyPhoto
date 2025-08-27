#pragma once
#include "globalview.h"
#include "mvp/view.h"

using namespace QtmMvp;

class DownloaderView : public QWidget, public View {
    Q_OBJECT
public:
    explicit DownloaderView(QWidget *parent = nullptr);
    ~DownloaderView() override {
    }

private:
    void createUi();
    void connectSig();
};