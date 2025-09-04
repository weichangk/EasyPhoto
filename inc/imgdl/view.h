#pragma once
#include "globalview.h"
#include "mvp/view.h"

using namespace QtmMvp;

class ImgDlView : public QWidget, public View {
    Q_OBJECT
public:
    explicit ImgDlView(QWidget *parent = nullptr);
    ~ImgDlView() override {
    }

private:
    void createUi();
    void connectSig();
};