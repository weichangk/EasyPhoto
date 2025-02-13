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

using namespace qtmaterialmvp;

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
    void onGenerationBtnClicked();

private:
    LanguageFilter *m_pLanguageFilter = nullptr;

    VectorButton *m_pAddFileBtn = nullptr;
    VectorButton *m_pAddFolderBtn = nullptr;
    VectorButton *m_pClearFileBtn = nullptr;
    VectorButton *m_pListModeSwitchBtn = nullptr;
    QLabel *m_pOutputFolderLbl = nullptr;
    QComboBox *m_pOutputFolderCbb = nullptr;
    ComboBoxFilter *m_pOutputFolderCbbFilter = nullptr;
    VectorButton *m_pOpenOutputFolderBtn = nullptr;
    QPushButton *m_pPreviewBtn = nullptr;
    QPushButton *m_pGenerationBtn = nullptr;
    QStackedLayout *m_pStackedLayout = nullptr;

    ImportGuide *m_pImportGuide = nullptr;
    QWidget *m_pImportGuideWidget = nullptr;

    ListView<SGifGenerationData> *m_pListView = nullptr;
    GifGenerationListDelegate *m_pListDelegate = nullptr;
};