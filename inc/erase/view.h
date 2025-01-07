#pragma once
#include "globalview.h"
#include "mvp/view.h"

using namespace qtmaterialmvp;

class EraseView : public QWidget, public View {
    Q_OBJECT
public:
    explicit EraseView(QWidget *parent = nullptr);
    ~EraseView() override {
    }

private:
    void createUi();
    void connectSig();
};