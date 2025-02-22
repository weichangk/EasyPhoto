#pragma once
#include "globalview.h"
#include "mvp/view.h"

using namespace qtmaterialmvp;

class HomeView : public QWidget, public View {
    Q_OBJECT
public:
    explicit HomeView(QWidget *parent = nullptr);
    ~HomeView() override {
    }

private:
    void createUi();
    void connectSig();
};