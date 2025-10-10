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
#include "types.h"
#include "preview/imageviewer.h"
#include "import/importlistview.h"
#include "modelcard.h"

#include <QStackedLayout>
#include <QCheckBox>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>

using namespace QtmMvp;
using namespace QtmWidget;
using namespace QtmCore;
using namespace QtmFilter;

class UpscView : public QWidget, public View {
    Q_OBJECT
public:
    explicit UpscView(QWidget *parent = nullptr);
    ~UpscView() override {
    }

    ImportListView *getImportListView();

protected:
    void showEvent(QShowEvent *event) override;

private:
    void createUi();
    void connectSig();
    void firstShow();
    void loadSampleImage();
    void importSampleImage(EUpscModelType type);
    void initOutputFolderCbbItem();
    void initSelectModelCbbItem();
    void initModelCard();
    void initUpscaleCbbItem();
    void initDoubleUpscaleCkb();
    void initSaveAsFormatCbbItem();
    void gotoImportGuide();
    void gotoWorkspace();
    void imageViewerLoad(const QString &filePath);
    void setOutputFolder(const QString &path);

private:
    bool handleMessage(IMessage* message) override;

private Q_SLOTS:
    void onLanguageChange();
    void onStandardSmapleImageLblClicked();
    void onLiteSmapleImageLblClicked();
    void onFidelitySmapleImageLblClicked();
    void onRemacriSmapleImageLblClicked();
    void onUltramixSmapleImageLblClicked();
    void onUltrasharpSmapleImageLblClicked();
    void onDigitalSmapleImageLblClicked();
    void onImportListCountChange(int count);
    void onImportListCurrentChanged(const QString filePath);
    void onGuideImportFile(const QStringList &filePaths);
    void onExportBtnClicked();
    void onSelectModelCbbCurrentIndex(int index);
    void onScaleCbbCurrentIndex(int index);
    void onSaveAsFormatCbbCurrentIndex(int index);
    void onDoubleUpscaleCkbStateChanged(int state);
    void onOpenOutputFolderBtnClicked();
    void onOutputFolderCbbIndexChanged(int index);

private:
    LanguageFilter *m_pLanguageFilter = nullptr;

    QLabel *m_pTitleLbl = nullptr;

    QStackedLayout *m_pStackedLayout = nullptr;

    QWidget *m_pImportGuideWidget = nullptr;
    ImportGuide *m_pImportGuide = nullptr;
    QWidget *m_pSmapleWidget = nullptr;
    QLabel *m_pSmapleTitleLbl = nullptr;
    ClickableLabel *m_pStandardSmapleImageLbl = nullptr;
    ClickableLabel *m_pLiteSmapleImageLbl = nullptr;
    ClickableLabel *m_pFidelitySmapleImageLbl = nullptr;
    ClickableLabel *m_pRemacriSmapleImageLbl = nullptr;
    ClickableLabel *m_pUltramixSmapleImageLbl = nullptr;
    ClickableLabel *m_pUltrasharpSmapleImageLbl = nullptr;
    ClickableLabel *m_pDigitalSmapleImageLbl = nullptr;

    QWidget *m_pWorkspaceWidget = nullptr;
    QWidget *m_pLeftWidget = nullptr;
    QWidget *m_pRightWidget = nullptr;

    ImageViewer *m_pImageViewer = nullptr;
    ImportListView *m_pImportListView = nullptr;

    QLabel *m_pSelectModelLbl = nullptr;
    QComboBox *m_pSelectModelCbb = nullptr;
    ModelCard *m_pModelCard = nullptr;

    QCheckBox *m_pDoubleUpscaleCkb = nullptr;
    IconButton *m_pDoubleUpscaleTipBtn = nullptr;

    QLabel *m_pScaleLbl = nullptr;
    QComboBox *m_pScaleCbb = nullptr;

    QLabel *m_pSaveAsFormatLbl = nullptr;
    QComboBox *m_pSaveAsFormatCbb = nullptr;

    QLabel *m_pOutputFolderLbl = nullptr;
    QComboBox *m_pOutputFolderCbb = nullptr;
    IconButton *m_pOpenOutputFolderBtn = nullptr;

    QPushButton *m_pExportBtn = nullptr;
};