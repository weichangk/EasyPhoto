#pragma once
#include "globalview.h"
#include "mvp/view.h"

using namespace qtmaterialmvp;

class ConversionView : public QWidget, public View {
    Q_OBJECT
public:
    explicit ConversionView(QWidget *parent = nullptr);
    ~ConversionView() override {
    }

private:
    void createUi();
    void connectSig();
};