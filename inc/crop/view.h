#pragma once
#include "globalview.h"
#include "mvp/view.h"
#include "widget/button.h"
#include "widget/label.h"
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
#include "imageworkwidget.h"
#include "import/importlistview.h"

#include <QStackedLayout>
#include <QCheckBox>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QButtonGroup>
#include <QStyledItemDelegate>
#include <QEvent>

using namespace QtmMvp;
using namespace QtmWidget;
using namespace QtmCore;
using namespace QtmFilter;

class CropViewCropAspectListDelegate : public QStyledItemDelegate {
    Q_OBJECT
public:
    explicit CropViewCropAspectListDelegate(QObject *parent);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    bool eventFilter(QObject *object, QEvent *event) override;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;

private:
    QSize m_Size = QSize(71, 54);
    int m_EventType = QEvent::None;
    QPoint m_CurPos;
};

class CropViewCropResizeListDelegate : public QStyledItemDelegate {
    Q_OBJECT
public:
    explicit CropViewCropResizeListDelegate(QObject *parent);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    bool eventFilter(QObject *object, QEvent *event) override;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;

private:
    QSize m_Size = QSize(218, 50);
    int m_EventType = QEvent::None;
    QPoint m_CurPos;
};

class CropView : public QWidget, public View {
    Q_OBJECT
public:
    explicit CropView(QWidget *parent = nullptr);
    ~CropView() override {
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

private Q_SLOTS:
    void onLanguageChange();
    void onSmaple1ImageLblClicked();
    void onSmaple2ImageLblClicked();
    void onImportListCountChange(int count);
    void onImportListCurrentChanged(const QString filePath);
    void onGuideImportFile(const QStringList &filePaths);
    void onResetBtnClieked();
    void onCropBtnClicked();
    void onResizeBtnClicked();
    void onCropAspectListCurrentChanged(const QModelIndex &current, const QModelIndex &previous);
    void onCropResizeListCurrentChanged(const QModelIndex &current, const QModelIndex &previous);
    void onStretchToFitCkbStateChanged(int state);

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

    ImageWorkWidget *m_pImageViewer = nullptr;
    ImportListView *m_pImportListView = nullptr;

    QPushButton *m_pCropBtn = nullptr;
    QPushButton *m_pResizeBtn = nullptr;

    ListView<SCropAspectData> *m_pCropAspectListView = nullptr;
    CropViewCropAspectListDelegate *m_pCropAspectListDelegate = nullptr;
    ListView<SCropResizeData> *m_pCropResizeListView = nullptr;
    CropViewCropResizeListDelegate *m_pCropResizeListDelegate = nullptr;

    IconButton *m_pLockScaleBtn = nullptr;
    UnitLineEdit *m_pPixelsWidthLdt = nullptr;
    UnitLineEdit *m_pPixelsHeightLdt = nullptr;

    QWidget *m_pRotateAndFlipWidget = nullptr;
    QLabel *m_pRotateAndFlipLbl = nullptr;
    IconButton *m_pRotateRight90Btn = nullptr;
    IconButton *m_pRotateLeft90Btn = nullptr;
    IconButton *m_pFlipHorBtn = nullptr;
    IconButton *m_pFlipVErBtn = nullptr;

    QWidget *m_pStretchToFitWidget = nullptr;
    QCheckBox *m_pStretchToFitCkb = nullptr;

    QWidget *m_pBgWidget = nullptr;
    QLabel *m_pBgLbl = nullptr;
    QButtonGroup *m_pBgBtnGroup = nullptr;
    IconButton *m_pBg1Btn = nullptr;
    IconButton *m_pBg2Btn = nullptr;
    IconButton *m_pBg3Btn = nullptr;
    IconButton *m_pBg4Btn = nullptr;
    IconButton *m_pBg5Btn = nullptr;
    IconButton *m_pBgSelectBtn = nullptr;

    QCheckBox *m_pApplySameCkb = nullptr;
    IconButton *m_pResetBtn = nullptr;

    QLabel *m_pOutputFmtLbl = nullptr;
    QButtonGroup *m_pOutputFmtBtnGroup = nullptr;
    QPushButton *m_pPNGBtn = nullptr;
    QPushButton *m_pJPGBtn = nullptr;
    QPushButton *m_pBMPBtn = nullptr;
    QPushButton *m_pWEBPBtn = nullptr;

    QPushButton *m_pExportBtn = nullptr;
    QLabel *m_pOutputFolderLbl = nullptr;
    QComboBox *m_pOutputFolderCbb = nullptr;
    IconButton *m_pOpenOutputFolderBtn = nullptr;
};