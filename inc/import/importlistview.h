#pragma once
#include "globalview.h"
#include "mvp/view.h"
#include "widget/button.h"
#include "widget/listview.h"
#include "importmodel.h"
#include "importlistdelegate.h"

using namespace qtmaterialmvp;
using namespace qtmaterialwidget;

class ImportListView : public QWidget, public View {
    Q_OBJECT
public:
    explicit ImportListView(QWidget *parent = nullptr, QString fileFilter = "(*.*)");
    ~ImportListView() override {
    }

    void importFile(const QStringList &filePaths);
    void deleteFile(const QString &filePath);
    void clearFile();

Q_SIGNALS:
    void sigImportListCountChange(int count);

private:
    void createUi();
    void connectSig();
    void listItemDelete(const QString &filePath);

private Q_SLOTS:
    void onAddBtnClicked();
    void onClearBtnClicked();
    void onListViewClicked(const QModelIndex &index);

private:
    ListView<SImportListItem> *m_pImportListView = nullptr;
    ImportListDelegate *m_pImportListDelegate = nullptr;
    IconButton *m_pAddBtn = nullptr;
    IconButton *m_pClearBtn = nullptr;

    QString m_FileFilter;
};