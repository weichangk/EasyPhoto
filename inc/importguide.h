#pragma once
#include "globalview.h"
#include "widget/label.h"

using namespace qtmaterialwidget;
using namespace qtmaterialcore;
using namespace qtmaterialfilter;

class ImportGuide : public QWidget {
    Q_OBJECT
public:
    explicit ImportGuide(QWidget *parent = nullptr);
    ~ImportGuide() override {
    }

private:
    void createUi();
    void connectSig();
    QWidget *createDividingLine();

private:
    void onLanguageChange();

private:
    LanguageFilter *m_pLanguageFilter = nullptr;
    QVBoxLayout *m_pMainLayout = nullptr;
    VectorLabel *m_pImportIconLab = nullptr;
    QLabel *m_pImportDecLab = nullptr;
    QWidget *m_pDividingLine = nullptr;
};