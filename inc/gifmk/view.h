#pragma once
#include "globalview.h"
#include "mvp/view.h"
#include "widget/button.h"
#include "widget/listview.h"
#include "widget/lineedit.h"
#include "core/font.h"
#include "core/object.h"
#include "core/file.h"
#include "filter/languagefilter.h"
#include "filter/popupwindow.h"
#include "filter/maskwidget.h"
#include "filter/comboboxfilter.h"
#include "import/importguide.h"
#include "types.h"
#include "listdelegate.h"
#include "preview/imageviewer.h"
#include "import/importlistview.h"

#include <QStackedLayout>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QCheckBox>

using namespace QtmMvp;
using namespace QtmWidget;
using namespace QtmCore;
using namespace QtmFilter;

class GifMkView : public QWidget, public View {
    Q_OBJECT
public:
    explicit GifMkView(QWidget *parent = nullptr);
    ~GifMkView() override {
    }

    ImportListView *getImportListView();

protected:
    void showEvent(QShowEvent *event) override;

private:
    void createUi();
    void connectSig();
    void firstShow();
    void initOutputFolderCbbItem();
    QWidget *createDividingLine();
    void setOutputFolder(const QString &path);
    void initUI();
    void gotoImportGuide();
    void gotoWorkspace();
    void imageViewerLoad(const QString &filePath);
    // void scaleOrSizeSwitch();

private Q_SLOTS:
    void onLanguageChange();
    void onOutputFolderCbbIndexChanged(int index);
    void onOpenOutputFolderBtnClicked();
    void onPreviewBtnClicked();
    void onStartAllClicked();
    void onImportListCountChange(int count);
    void onImportListCurrentChanged(const QString filePath);
    void onGuideImportFile(const QStringList &filePaths);
    void onSizeBtnClicked();
    void onScaleBtnClicked();
    void onScaleCbbIndexChanged(int index);
    void onSizeCbbIndexChanged(int index);
    void onLockScaleBtnClicked();
    void onLoopCkbStateChanged(int state);
    void onReverseCkbStateChanged(int state);
    void onSpeedSliderValueChanged(int value);
    void onBg1BtnClicked();
    void onBg2BtnClicked();
    void onBg3BtnClicked();
    void onBg4BtnClicked();
    void onBg5BtnClicked();
    void onBgSelectBtnClicked();

private:
    LanguageFilter *m_pLanguageFilter = nullptr;

    QLabel *m_pTitleLbl = nullptr;

    QStackedLayout *m_pStackedLayout = nullptr;

    QWidget *m_pImportGuideWidget = nullptr;
    ImportGuide *m_pImportGuide = nullptr;

    QWidget *m_pWorkspaceWidget = nullptr;
    QWidget *m_pLeftWidget = nullptr;
    QWidget *m_pRightWidget = nullptr;

    ImageViewer *m_pImageViewer = nullptr;
    ImportListView *m_pImportListView = nullptr;


    QWidget *m_pContentWidget = nullptr;

    QPushButton *m_pSizeBtn = nullptr;
    QPushButton *m_pScaleBtn = nullptr;
    QComboBox *m_pScaleCbb = nullptr;
    QComboBox *m_pSizeCbb = nullptr;
    IconButton *m_pLockScaleBtn = nullptr;
    UnitLineEdit *m_pPixelsWidthLdt = nullptr;
    UnitLineEdit *m_pPixelsHeightLdt = nullptr;
    QLabel *m_pPlayLbl = nullptr;
    QCheckBox *m_pLoopCkb = nullptr;
    QCheckBox *m_pReverseCkb = nullptr;
    QLabel *m_pSpeedLbl = nullptr;
    QLabel *m_pSpeedDescLbl = nullptr;
    QSlider *m_pSpeedSlider = nullptr;
    QLabel *m_pBgLbl = nullptr;
    QButtonGroup *m_pBgBtnGroup = nullptr;
    IconButton *m_pBg1Btn = nullptr;
    IconButton *m_pBg2Btn = nullptr;
    IconButton *m_pBg3Btn = nullptr;
    IconButton *m_pBg4Btn = nullptr;
    IconButton *m_pBg5Btn = nullptr;
    IconButton *m_pBgSelectBtn = nullptr;
    QLabel *m_pOutputFolderLbl = nullptr;
    QComboBox *m_pOutputFolderCbb = nullptr;
    IconButton *m_pOpenOutputFolderBtn = nullptr;
    QPushButton *m_pPreviewBtn = nullptr;
    QPushButton *m_pStartAllBtn = nullptr;
};