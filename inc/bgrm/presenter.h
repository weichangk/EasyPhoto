#pragma once
#include "globalpresenter.h"
#include "types.h"
#include "mvp/repository.h"
#include "mvp/presenter.h"
#include "import/importlistpresenter.h"

using namespace QtmMvp;

class BgRmPresenter : public Presenter {
public:
    explicit BgRmPresenter(IView* view, IRepository *repository);
    ~BgRmPresenter();

    QString getSampleImage1Path();
    QString getSampleImage2Path();

    QList<SBgImgData> getBgImgDataDatas(EBgImgType type);

private:
    ImportListPresenter * m_pImportListPresenter = nullptr;
};