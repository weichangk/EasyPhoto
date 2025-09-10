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
#include "listdelegate.h"
#include "preview/imageviewer.h"
#include "import/importlistview.h"

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

class BgRmView : public QWidget, public View {
    Q_OBJECT
public:
    explicit BgRmView(QWidget *parent = nullptr);
    ~BgRmView() override {
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
    void gotoImportGuide();
    void gotoWorkspace();
    void imageViewerLoad(const QString &filePath);

private 
Q_SLOTS:
    void onLanguageChange();
    void onSmaple1ImageLblClicked();
    void onSmaple2ImageLblClicked();
    void onImportListCountChange(int count);
    void onImportListCurrentChanged(const QString filePath);
    void onGuideImportFile(const QStringList &filePaths);
    void onStartAllBtnClicked();
    void onBgCustomImgBtnClicked();
    void onBgGeneralImgBtnClicked();
    void onBgSceneImgBtnClicked();

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

    QLabel *m_pOutputFolderLbl = nullptr;
    QComboBox *m_pOutputFolderCbb = nullptr;
    IconButton *m_pOpenOutputFolderBtn = nullptr;

    QLabel *m_pBgColorLbl = nullptr;
    IconButton *m_pBgColor0Btn = nullptr;
    IconButton *m_pBgColor1Btn = nullptr;
    IconButton *m_pBgColor2Btn = nullptr;
    IconButton *m_pBgColor3Btn = nullptr;
    IconButton *m_pBgColor4Btn = nullptr;
    IconButton *m_pBgColorSelectBtn = nullptr;

    QLabel *m_pBgImgLbl = nullptr;
    QPushButton *m_pBgCustomImgBtn = nullptr;
    QPushButton *m_pBgGeneralImgBtn = nullptr;
    QPushButton *m_pBgSceneImgBtn = nullptr;

    ListView<SBgImgData> *m_pBgImgListView = nullptr;
    BgImgListDelegate *m_pBgImgListDelegate = nullptr;

    QPushButton *m_pStartAllBtn = nullptr;
};