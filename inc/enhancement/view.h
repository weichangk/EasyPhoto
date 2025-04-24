#pragma once
#include "globalview.h"
#include "mvp/view.h"
#include "widget/button.h"
#include "widget/label.h"
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
#include "modellistdelegate.h"
#include "preview/imageviewer.h"
#include "import/importlistview.h"

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

    ImportListView *getImportListView();

protected:
    void showEvent(QShowEvent *event) override;

private:
    void createUi();
    void connectSig();
    void firstShow();
    void loadSampleImage();
    void importSampleImage1();
    void importSampleImage2();
    void initOutputFolderCbbItem();
    void loadModelList();
    void gotoImportGuide();
    void gotoWorkspace();
    void imageViewerLoad(const QString &filePath);
    void setModelListCurrentIndex(int index);
    void initUpscaleCbbItem();
    void upscaleSettingVisible(bool visible);
    void initCompressionCbbItem();
    void initSaveAsFormatCbbItem();

private Q_SLOTS:
    void onLanguageChange();
    void onSmaple1ImageLblClicked();
    void onSmaple2ImageLblClicked();
    void onImportListCountChange(int count);
    void onImportListCurrentChanged(const QString filePath);
    void onGuideImportFile(const QStringList &filePaths);
    void ondModelListViewCurrentChanged(const QModelIndex &current, const QModelIndex &previous);
    void onExportBtnClicked();

private:
    LanguageFilter *m_pLanguageFilter = nullptr;

    QLabel *m_pTitleLbl = nullptr;

    QStackedLayout *m_pStackedLayout = nullptr;

    QWidget *m_pImportGuideWidget = nullptr;
    ImportGuide *m_pImportGuide = nullptr;
    QWidget *m_pSmapleWidget = nullptr;
    QLabel *m_pSmapleTitleLbl = nullptr;
    ClickableLabel *m_pSmaple1ImageLbl = nullptr;
    ClickableLabel *m_pSmaple2ImageLbl = nullptr;

    QWidget *m_pWorkspaceWidget = nullptr;
    QWidget *m_pLeftWidget = nullptr;
    QWidget *m_pRightWidget = nullptr;

    ImageViewer *m_pImageViewer = nullptr;
    ImportListView *m_pImportListView = nullptr;

    QLabel *m_pChooseModelLbl = nullptr;
    ListView<SEnhanceModelData> *m_pModelListView = nullptr;
    EnhanceModelListDelegate *m_pModelListDelegate = nullptr;
    QLabel *m_pUpscaleLbl = nullptr;
    QComboBox *m_pUpscaleCbb = nullptr;
    ComboBoxFilter *m_pUpscaleCbbFilter = nullptr;
    QCheckBox *m_pCustomOutputWidthCkb = nullptr;
    QLineEdit *m_pCustomOutputWidthLdt = nullptr;
    QLabel *m_pCompressionLbl = nullptr;
    QComboBox *m_pCompressionCbb = nullptr;
    QLabel *m_pSaveAsFormatLbl = nullptr;
    QComboBox *m_pSaveAsFormatCbb = nullptr;

    QPushButton *m_pExportBtn = nullptr;
    QLabel *m_pOutputFolderLbl = nullptr;
    QComboBox *m_pOutputFolderCbb = nullptr;
    ComboBoxFilter *m_pOutputFolderCbbFilter = nullptr;
    IconButton *m_pOpenOutputFolderBtn = nullptr;

};