#pragma once
#include "globalview.h"
#include "mvp/view.h"

using namespace qtmaterialmvp;

class EffectsView : public QWidget, public View {
    Q_OBJECT
public:
    explicit EffectsView(QWidget *parent = nullptr);
    ~EffectsView() override {
    }

private:
    void createUi();
    void connectSig();
};