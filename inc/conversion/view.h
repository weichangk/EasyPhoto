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
#include "importguide.h"
#include "model.h"
#include "listdelegate.h"
#include "outputformatdelegate.h"

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

class ConversionOutputFormatView : public QWidget {
    Q_OBJECT
public:
    explicit ConversionOutputFormatView(QWidget *parent = nullptr);
    ~ConversionOutputFormatView() override {
    }
    void setSelection(const QString &format);

Q_SIGNALS:
    void sigSelectionChanged(const QString &format);

private:
    void createUi();
    void connectSig();

private:
    void onListItemViewclicked(const QModelIndex &index);

private:
    ListView<SConversionOuputFormat> *m_pListView = nullptr;
    ConversionOutputFormatDelegate *m_pListDelegate = nullptr;
};

class ConversionView : public QWidget, public View {
    Q_OBJECT
public:
    explicit ConversionView(QWidget *parent = nullptr);
    ~ConversionView() override {
    }

protected:
    void showEvent(QShowEvent *event) override;

private:
    void createUi();
    void connectSig();
    QWidget *createDividingLine();
    void listViewImportFile(const QStringList &filePaths);
    void listItemSelectChanged(const QString &filePath);
    void listItemDelete(const QString &filePath);
    void listViewNoDataState();
    void selectAllState();
    void showOutputFormatView();
    void setOutputFormatCbbText(const QString &text);
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
    void onOutputFormatCbbClicked();
    void onOutputFolderCbbClicked();
    void onOutputFolderCbbIndexChanged(int index);
    void onOpenOutputFolderBtnClicked();
    void onConversionBtnClicked();

private:
    LanguageFilter *m_pLanguageFilter = nullptr;

    QLabel *m_pTitleLbl = nullptr;

    QWidget *m_pImportGuideWidget = nullptr;
    ImportGuide *m_pImportGuide = nullptr;

    QWidget *m_pContentWidget = nullptr;

    IconButton *m_pAddFileBtn = nullptr;
    IconButton *m_pAddFolderBtn = nullptr;
    IconButton *m_pClearFileBtn = nullptr;
    IconButton *m_pListModeSwitchBtn = nullptr;
    QCheckBox *m_pSelectAllCkb = nullptr;
    QLabel *m_pOutputFormatLbl = nullptr;
    QLineEdit *m_pOutputFormatEdit = nullptr;
    QComboBox *m_pOutputFormatCbb = nullptr;
    ComboBoxFilter *m_pOutputFormatCbbFilter = nullptr;
    QLabel *m_pOutputFolderLbl = nullptr;
    QComboBox *m_pOutputFolderCbb = nullptr;
    ComboBoxFilter *m_pOutputFolderCbbFilter = nullptr;
    IconButton *m_pOpenOutputFolderBtn = nullptr;
    QPushButton *m_pConversionBtn = nullptr;
    QStackedLayout *m_pStackedLayout = nullptr;

    ListView<SConversionData> *m_pListView = nullptr;
    ConversionListDelegate *m_pListDelegate = nullptr;

    ConversionOutputFormatView *m_pOutputFormatView = nullptr;
};