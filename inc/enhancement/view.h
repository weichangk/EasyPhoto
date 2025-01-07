#pragma once
#include "globalview.h"
#include "mvp/view.h"

using namespace qtmaterialmvp;

class EnhancementView : public QWidget, public View {
    Q_OBJECT
public:
    explicit EnhancementView(QWidget *parent = nullptr);
    ~EnhancementView() override {
    }

private:
    void createUi();
    void connectSig();
};