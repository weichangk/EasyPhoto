#pragma once
#include "globalview.h"
#include "mvp/view.h"

using namespace qtmaterialmvp;

class CompressionView : public QWidget, public View {
    Q_OBJECT
public:
    explicit CompressionView(QWidget *parent = nullptr);
    ~CompressionView() override {
    }

private:
    void createUi();
    void connectSig();
};