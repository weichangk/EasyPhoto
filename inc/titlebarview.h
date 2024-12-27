#pragma once
#include "globalview.h"
#include "mvp/view.h"

using namespace qtmaterialmvp;

class TitlebarView : public QWidget, public View {
    Q_OBJECT
public:
    explicit TitlebarView(QWidget *parent = nullptr);
    ~TitlebarView() override {
    }

private:
    void createUi();
    void connectSig();
};