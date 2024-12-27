#pragma once
#include "globalview.h"
#include "mvp/view.h"

using namespace qtmaterialmvp;

class MainView : public QWidget, public View {
    Q_OBJECT
public:
    explicit MainView(QWidget *parent = nullptr);
    ~MainView() override {
    }

private:
    void createUi();
    void connectSig();
};