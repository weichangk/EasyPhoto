#pragma once
#include "globalview.h"
#include "mvp/view.h"

using namespace qtmaterialmvp;

class GifGenerationView : public QWidget, public View {
    Q_OBJECT
public:
    explicit GifGenerationView(QWidget *parent = nullptr);
    ~GifGenerationView() override {
    }

private:
    void createUi();
    void connectSig();
};