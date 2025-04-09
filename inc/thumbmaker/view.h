#pragma once
#include "globalview.h"
#include "mvp/view.h"

using namespace qtmaterialmvp;

class ThumbnailMakerView : public QWidget, public View {
    Q_OBJECT
public:
    explicit ThumbnailMakerView(QWidget *parent = nullptr);
    ~ThumbnailMakerView() override {
    }

private:
    void createUi();
    void connectSig();
};