#pragma once
#include "globalview.h"
#include "mvp/view.h"

using namespace qtmaterialmvp;

class CroppingView : public QWidget, public View {
    Q_OBJECT
public:
    explicit CroppingView(QWidget *parent = nullptr);
    ~CroppingView() override {
    }

private:
    void createUi();
    void connectSig();
};