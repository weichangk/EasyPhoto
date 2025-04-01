#pragma once
#include "globalview.h"
#include "mvp/view.h"
#include "widget/button.h"
#include "widget/listview.h"
#include "core/font.h"
#include "core/object.h"
#include "core/file.h"
#include "filter/languagefilter.h"
#include "filter/popupwindow.h"
#include "filter/maskwidget.h"
#include "filter/comboboxfilter.h"
#include "importguide.h"

#include <QStackedLayout>
#include <QCheckBox>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>

using namespace qtmaterialmvp;
using namespace qtmaterialwidget;
using namespace qtmaterialcore;
using namespace qtmaterialfilter;

class EnhancementView : public QWidget, public View {
    Q_OBJECT
public:
    explicit EnhancementView(QWidget *parent = nullptr);
    ~EnhancementView() override {
    }

private:
    void createUi();
    void connectSig();
    void loadSampleImage();

private Q_SLOTS:
    void onLanguageChange();

private:
    LanguageFilter *m_pLanguageFilter = nullptr;

    QLabel *m_pTitleLbl = nullptr;
    QWidget *m_pBodyWidget = nullptr;

    QWidget *m_pLeftWidget = nullptr;
    QWidget *m_pRightWidget = nullptr;

    QStackedLayout *m_pLeftWidgetStackedLayout = nullptr;

    QWidget *m_pImportGuideWidget = nullptr;
    QWidget *m_pSmapleWidget = nullptr;
    QLabel *m_pSmapleTitleLbl = nullptr;
    QLabel *m_pSmaple1ImageLbl = nullptr;
    QLabel *m_pSmaple2ImageLbl = nullptr;
    ImportGuide *m_pImportGuide = nullptr;

    QLabel *m_pOutputFolderLbl = nullptr;
    QComboBox *m_pOutputFolderCbb = nullptr;
    ComboBoxFilter *m_pOutputFolderCbbFilter = nullptr;
    IconButton *m_pOpenOutputFolderBtn = nullptr;

    IconButton *m_pClearFileBtn = nullptr;
    IconButton *m_pPreviewBtn = nullptr;
    IconButton *m_pStartAllBtn = nullptr;
};