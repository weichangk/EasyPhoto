#pragma once
#include "globalview.h"
#include "mvp/view.h"
#include "widget/button.h"
#include "widget/listview.h"
#include "core/font.h"
#include "filter/languagefilter.h"
#include "importguide.h"
#include "model.h"

#include <QStackedLayout>
#include <QCheckBox>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>

using namespace qtmaterialmvp;
using namespace qtmaterialwidget;
using namespace qtmaterialcore;
using namespace qtmaterialfilter;

class ConversionView : public QWidget, public View {
    Q_OBJECT
public:
    explicit ConversionView(QWidget *parent = nullptr);
    ~ConversionView() override {
    }

private:
    void createUi();
    void connectSig();
    QWidget *createDividingLine();
    void listViewImportFile(const QStringList filePaths);

private:
    void onLanguageChange();
    void onAddFileClicked();

private:
    LanguageFilter *m_pLanguageFilter = nullptr;

    VectorButton *m_pAddFileBtn = nullptr;
    VectorButton *m_pAddFolderBtn = nullptr;
    VectorButton *m_pDelFileBtn = nullptr;
    QCheckBox *m_pSelectAllCkb = nullptr;
    QLabel *m_pOutputFormatLbl = nullptr;
    QComboBox *m_pOutputFormatCbb = nullptr;
    QLabel *m_pOutputFolderLbl = nullptr;
    QComboBox *m_pOutputFolderCbb = nullptr;
    VectorButton *m_pOpenOutputFolderBtn = nullptr;
    QPushButton *m_pConversionBtn = nullptr;
    QStackedLayout *m_pStackedLayout = nullptr;

    ImportGuide *m_pImportGuide = nullptr;

    ListView<Data> *m_pListView = nullptr;
};