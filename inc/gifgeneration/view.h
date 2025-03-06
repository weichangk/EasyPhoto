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
#include "model.h"
#include "listdelegate.h"

#include <QStackedLayout>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>

using namespace qtmaterialmvp;
using namespace qtmaterialwidget;
using namespace qtmaterialcore;
using namespace qtmaterialfilter;

class GifGenerationView : public QWidget, public View {
    Q_OBJECT
public:
    explicit GifGenerationView(QWidget *parent = nullptr);
    ~GifGenerationView() override {
    }

protected:
    void showEvent(QShowEvent *event) override;

private:
    void createUi();
    void connectSig();
    QWidget *createDividingLine();
    void listViewImportFile(const QStringList &filePaths);
    void listItemDelete(const QString &filePath);
    void listViewNoDataState();
    void initOutputFolderCbbItem();
    void setOutputFolder(const QString &path);
    void initFrameRateCbbItem();

private Q_SLOTS:
    void onLanguageChange();
    void onAddFileBtnClicked();
    void onAddFolderBtnClicked();
    void onListModeSwitchBtnClicked();
    void onClearFileBtnClicked();
    void onListViewClicked(const QModelIndex &index);
    void onOutputFolderCbbClicked();
    void onOutputFolderCbbIndexChanged(int index);
    void onOpenOutputFolderBtnClicked();
    void onPreviewBtnClicked();
    void onStartAllClicked();

private:
    LanguageFilter *m_pLanguageFilter = nullptr;

    QLabel *m_pTitleLbl = nullptr;

    ImportGuide *m_pImportGuide = nullptr;
    QWidget *m_pImportGuideWidget = nullptr;

    QWidget *m_pContentWidget = nullptr;

    IconButton *m_pAddFileBtn = nullptr;
    IconButton *m_pAddFolderBtn = nullptr;
    IconButton *m_pClearFileBtn = nullptr;
    IconButton *m_pListModeSwitchBtn = nullptr;
    QLabel *m_pOutputFolderLbl = nullptr;
    QComboBox *m_pOutputFolderCbb = nullptr;
    ComboBoxFilter *m_pOutputFolderCbbFilter = nullptr;
    IconButton *m_pOpenOutputFolderBtn = nullptr;
    QLabel *m_pPixelsLbl = nullptr;
    QLabel *m_pPixels_x_Lbl = nullptr;
    QLineEdit *m_pPixelsWidthLdt = nullptr;
    QLineEdit *m_pPixelsHeightLdt = nullptr;
    QLabel *m_pFrameRateLbl = nullptr;
    QComboBox *m_pFrameRateCbb = nullptr;
    QPushButton *m_pPreviewBtn = nullptr;
    QPushButton *m_pStartAllBtn = nullptr;
    QStackedLayout *m_pStackedLayout = nullptr;

    ListView<SGifGenerationData> *m_pListView = nullptr;
    GifGenerationListDelegate *m_pListDelegate = nullptr;
};