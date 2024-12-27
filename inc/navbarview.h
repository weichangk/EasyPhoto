#pragma once
#include "globalview.h"
#include "mvp/view.h"

using namespace qtmaterialmvp;

class NavbarView : public QWidget, public View {
    Q_OBJECT
public:
    explicit NavbarView(QWidget *parent = nullptr);
    ~NavbarView() override {
    }

private:
    void createUi();
    void connectSig();
};