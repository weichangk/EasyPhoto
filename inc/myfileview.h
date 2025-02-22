#pragma once
#include "globalview.h"
#include "mvp/view.h"

using namespace qtmaterialmvp;

class MyFileView : public QWidget, public View {
    Q_OBJECT
public:
    explicit MyFileView(QWidget *parent = nullptr);
    ~MyFileView() override {
    }

private:
    void createUi();
    void connectSig();
};