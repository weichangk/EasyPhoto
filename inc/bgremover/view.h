#pragma once
#include "globalview.h"
#include "mvp/view.h"
#include "widget/button.h"
#include "widget/listview.h"
#include "core/font.h"
#include "core/object.h"
#include "filter/languagefilter.h"
#include "filter/popupwindow.h"
#include "filter/maskwidget.h"
#include "filter/comboboxfilter.h"
#include "import/importguide.h"
#include "model.h"
#include "listdelegate.h"

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

class BackgroungRemoverView : public QWidget, public View {
    Q_OBJECT
public:
    explicit BackgroungRemoverView(QWidget *parent = nullptr);
    ~BackgroungRemoverView() override {
    }

protected:
    void showEvent(QShowEvent *event) override;

private:
    void createUi();
    void connectSig();
    void firstShow();
    QWidget *createDividingLine();
    void listViewImportFile(const QStringList &filePaths);
    void listItemSelectChanged(const QString &filePath);
    void listItemDelete(const QString &filePath);
    void listViewNoDataState();
    void selectAllState();
    void initOutputFolderCbbItem();
    void setOutputFolder(const QString &path);

private 
Q_SLOTS:
    void onLanguageChange();
    void onAddFileBtnClicked();
    void onAddFolderBtnClicked();
    void onListModeSwitchBtnClicked();
    void onClearFileBtnClicked();
    void onSelectAllStateChanged(int);
    void onListViewClicked(const QModelIndex &index);
    void onOutputFolderCbbClicked();
    void onOutputFolderCbbIndexChanged(int index);
    void onOpenOutputFolderBtnClicked();
    void onStartAllBtnClicked();

private:
    LanguageFilter *m_pLanguageFilter = nullptr;

    QLabel *m_pTitleLbl = nullptr;

    QWidget *m_pImportGuideWidget = nullptr;
    ImportGuide *m_pImportGuide = nullptr;

    QWidget *m_pWorkspaceWidget = nullptr;

    IconButton *m_pAddFileBtn = nullptr;
    IconButton *m_pAddFolderBtn = nullptr;
    IconButton *m_pClearFileBtn = nullptr;
    IconButton *m_pListModeSwitchBtn = nullptr;
    QCheckBox *m_pSelectAllCkb = nullptr;
    QLabel *m_pOutputFolderLbl = nullptr;
    QComboBox *m_pOutputFolderCbb = nullptr;
    ComboBoxFilter *m_pOutputFolderCbbFilter = nullptr;
    IconButton *m_pOpenOutputFolderBtn = nullptr;
    QPushButton *m_pStartAllBtn = nullptr;
    QStackedLayout *m_pStackedLayout = nullptr;

    ListView<SBGRemoverData> *m_pListView = nullptr;
    BackgroungRemoverListDelegate *m_pListDelegate = nullptr;
};