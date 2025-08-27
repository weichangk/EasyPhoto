#pragma once
#include "globalview.h"
#include "mvp/view.h"

using namespace QtmMvp;

class InpaintingView : public QWidget, public View {
    Q_OBJECT
public:
    explicit InpaintingView(QWidget *parent = nullptr);
    ~InpaintingView() override {
    }

private:
    void createUi();
    void connectSig();
};