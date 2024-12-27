#pragma once
#include "globalview.h"
#include "mvp/view.h"

using namespace qtmaterialmvp;

class FuncAreaView : public QWidget, public View {
    Q_OBJECT
public:
    explicit FuncAreaView(QWidget *parent = nullptr);
    ~FuncAreaView() override {
    }

private:
    void createUi();
    void connectSig();
};