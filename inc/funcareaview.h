#pragma once
#include "globalview.h"
#include "mvp/view.h"

#include <QStackedLayout>

using namespace qtmaterialmvp;

class FuncAreaView : public QWidget, public View {
    Q_OBJECT
public:
    explicit FuncAreaView(QWidget *parent = nullptr);
    ~FuncAreaView() override {
    }

private:
    void createUi();
    void connectSig();

private:
    QStackedLayout *m_pStackedLayout = nullptr;
};