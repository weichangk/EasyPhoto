#pragma once
#include "globalview.h"
#include "mvp/view.h"

using namespace QtmMvp;

class ThumbMkView : public QWidget, public View {
    Q_OBJECT
public:
    explicit ThumbMkView(QWidget *parent = nullptr);
    ~ThumbMkView() override {
    }

private:
    void createUi();
    void connectSig();
};