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
#include "import/importguide.h"
#include "model.h"
#include "inputlistdelegate.h"
#include "modellistdelegate.h"

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

protected:
    void showEvent(QShowEvent *event) override;

private:
    void createUi();
    void connectSig();
    void firstShow();
    void loadSampleImage();
    void initOutputFolderCbbItem();
    void loadModelList();

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
    ImportGuide *m_pImportGuide = nullptr;
    QWidget *m_pSmapleWidget = nullptr;
    QLabel *m_pSmapleTitleLbl = nullptr;
    QLabel *m_pSmaple1ImageLbl = nullptr;
    QLabel *m_pSmaple2ImageLbl = nullptr;

    QLabel *m_pChooseModelLbl = nullptr;
    ListView<SEnhanceModelData> *m_pModelListView = nullptr;
    EnhanceModelListDelegate *m_pModelListDelegate = nullptr;

    // IconButton *m_pClearFileBtn = nullptr;
    // IconButton *m_pPreviewBtn = nullptr;

    QWidget *m_pWorkspaceWidget = nullptr;


    QPushButton *m_pExportBtn = nullptr;
    QLabel *m_pOutputFolderLbl = nullptr;
    QComboBox *m_pOutputFolderCbb = nullptr;
    ComboBoxFilter *m_pOutputFolderCbbFilter = nullptr;
    IconButton *m_pOpenOutputFolderBtn = nullptr;

};