#pragma once
#include "globalview.h"
#include "mvp/view.h"

using namespace qtmaterialmvp;

class BackgroungRemoverView : public QWidget, public View {
    Q_OBJECT
public:
    explicit BackgroungRemoverView(QWidget *parent = nullptr);
    ~BackgroungRemoverView() override {
    }

private:
    void createUi();
    void connectSig();
};