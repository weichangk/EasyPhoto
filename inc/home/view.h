#pragma once
#include "globalview.h"
#include "mvp/view.h"
#include "widget/listview.h"
#include "model.h"
#include "funcitemdelegate.h"

using namespace qtmaterialmvp;
using namespace qtmaterialwidget;
class HomeView : public QWidget, public View {
    Q_OBJECT
public:
    explicit HomeView(QWidget *parent = nullptr);
    ~HomeView() override {
    }

protected:
    void showEvent(QShowEvent *event) override;
    
private:
    void createUi();
    void connectSig();
    void initListView();

private:
    ListView<SFuncItemData> *m_pListView = nullptr;
    FuncItemDelegate *m_pListDelegate = nullptr;
};