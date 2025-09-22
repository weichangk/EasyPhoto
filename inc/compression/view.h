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
#include "types.h"
#include "listdelegate.h"

#include <QStackedLayout>
#include <QCheckBox>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QSlider>

using namespace QtmMvp;
using namespace QtmWidget;
using namespace QtmCore;
using namespace QtmFilter;

class CompressionView : public QWidget, public View {
    Q_OBJECT
public:
    explicit CompressionView(QWidget *parent = nullptr);
    ~CompressionView() override {
    }

protected:
    void showEvent(QShowEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    void createUi();
    void connectSig();
    QWidget *createDividingLine();
    void listViewImportFile(const QStringList &filePaths);
    void listItemSelectChanged(const QString &filePath);
    void listItemDelete(const QString &filePath);
    void listViewNoDataState();
    void selectAllState();
    void initOutputFormatCbbItem();
    void initOutputFolderCbbItem();
    void setOutputFolder(const QString &path);
    void setStartAllBtnVisible(bool visible);

    QList<SImageData> getListViewModels() const;
    SImageData getListViewModel(const QString &filePath) const;
    int getListViewModelIndex(const QString &filePath) const;

    void startAllTask();
    void startTask(const QString &path);

private Q_SLOTS:
    void onLanguageChange();
    void onAddFileBtnClicked();
    void onAddFolderBtnClicked();
    void onListModeSwitchBtnClicked();
    void onClearFileBtnClicked();
    void onSelectAllStateChanged(int);
    void onListViewClicked(const QModelIndex &index);
    void onOutputFormatCbbCurrentIndex(int index);
    void onOutputFolderCbbIndexChanged(int index);
    void onOpenOutputFolderBtnClicked();
    void onStartAllBtnClicked();
    void onCancelAllBtnClicked();
    void onCompreSliderValueChanged(int value);
    void onCompreValueEdited(const QString &text);

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
    QCheckBox *m_pSelectAllCkb = nullptr;
    QLabel *m_pOutputFormatLbl = nullptr;
    QComboBox *m_pOutputFormatCbb = nullptr;
    QLabel *m_pOutputFolderLbl = nullptr;
    QComboBox *m_pOutputFolderCbb = nullptr;
    IconButton *m_pOpenOutputFolderBtn = nullptr;
    QLabel *m_pCompreToLbl = nullptr;
    QSlider *m_pCompreSlider = nullptr;
    QLineEdit *m_pCompreValueEdit = nullptr;
    QLabel *m_pComprePercentLbl = nullptr;
    QPushButton *m_pStartAllBtn = nullptr;
    QPushButton *m_pCancelAllBtn = nullptr;
    QStackedLayout *m_pStackedLayout = nullptr;

    QWidget *m_pListViewColumnName = nullptr;
    QCheckBox *m_pColumnFileNameCkb = nullptr;
    QLabel *m_pColumnResolutionLbl = nullptr;
    QLabel *m_pColumnSizeLbl = nullptr;
    QLabel *m_pColumnStatusLbl = nullptr;
    QLabel *m_pColumnActionLbl = nullptr;

    ListView<SImageData> *m_pListView = nullptr;
    CompressionListDelegate *m_pListDelegate = nullptr;
};