#pragma once
#include "globalview.h"
#include "mvp/view.h"
#include "widget/button.h"
#include "widget/listview.h"
#include "types.h"
#include "importlistdelegate.h"

using namespace QtmMvp;
using namespace QtmWidget;

class ImportListView : public QWidget, public View {
    Q_OBJECT
public:
    explicit ImportListView(QWidget *parent = nullptr, QString fileFilter = "(*.*)");
    ~ImportListView() override {
    }

    void importFile(const QStringList &filePaths);
    void deleteFile(const QString &filePath);
    void clearFile();

    void setImportListCurrentIndex(int index);
    int getImportListCount();

Q_SIGNALS:
    void sigImportListCountChange(int count);
    void sigImportListCurrentChanged(const QString &filePath);

protected:
    bool eventFilter(QObject* watched, QEvent* event);

private:
    void createUi();
    void connectSig();
    bool listViewClicked(const QModelIndex &index, QMouseEvent *mouseEvent);
    bool isListViewCurrent(const QString &filePath);

private Q_SLOTS:
    void onAddBtnClicked();
    void onClearBtnClicked();
    void onListViewCurrentChanged(const QModelIndex &current, const QModelIndex &previous);

private:
    ListView<SImageData> *m_pImportListView = nullptr;
    ImportListDelegate *m_pImportListDelegate = nullptr;
    IconButton *m_pAddBtn = nullptr;
    IconButton *m_pClearBtn = nullptr;

    QString m_FileFilter;
};