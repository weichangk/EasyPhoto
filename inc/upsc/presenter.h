#pragma once
#include "globalpresenter.h"
#include "mvp/repository.h"
#include "mvp/presenter.h"
#include "types.h"
#include "import/importlistpresenter.h"

class UpscPresenter : public Presenter {
public:
    explicit UpscPresenter(QtmMvp::IView* view, QtmMvp::IRepository *repository);
    ~UpscPresenter();

    QList<SUpscSelectModelData> getSelectModelDatas();

    QString getSampleBeforeImagePath(EUpscModelType type);

    void Upsc();

private:
    bool handleMessage(IMessage* message) override;

private:
    ImportListPresenter * m_pImportListPresenter = nullptr;
};