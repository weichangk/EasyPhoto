#pragma once
#include "globalpresenter.h"
#include "mvp/repository.h"
#include "mvp/presenter.h"
#include "types.h"
#include "import/importlistpresenter.h"

using namespace QtmMvp;

class UpscPresenter : public Presenter {
public:
    explicit UpscPresenter(IView* view, IRepository *repository);
    ~UpscPresenter();

    QList<SUpscSelectModelData> getSelectModelDatas();

    QString getSampleImagePath(EUpscSmapleType type);

    void Upsc();

private:
    ImportListPresenter * m_pImportListPresenter = nullptr;
};