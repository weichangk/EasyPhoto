#pragma once
#include "globalview.h"
#include "widget/button.h"
#include "widget/listview.h"
#include "importmodel.h"
#include "importlistdelegate.h"

using namespace qtmaterialwidget;

class ImportListView : public QWidget {
    Q_OBJECT
public:
    explicit ImportListView(QWidget *parent = nullptr);
    ~ImportListView() override {
    }

private:
    void createUi();
    void connectSig();

private Q_SLOTS:
    void onAddBtnClicked();
    void onClearBtnClicked();

private:
    ListView<SImportListItem> *m_pImportListView = nullptr;
    ImportListDelegate *m_pImportListDelegate = nullptr;
    IconButton *m_pAddBtn = nullptr;
    IconButton *m_pClearBtn = nullptr;
};