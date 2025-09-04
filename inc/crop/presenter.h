#pragma once
#include "globalpresenter.h"
#include "mvp/repository.h"
#include "mvp/presenter.h"
#include "types.h"
#include "import/importlistpresenter.h"

using namespace QtmMvp;

class CropPresenter : public Presenter {
public:
    explicit CropPresenter(IView* view, IRepository *repository);
    ~CropPresenter();

    QString getSampleImage1Path();
    QString getSampleImage2Path();

private:
    ImportListPresenter * m_pImportListPresenter = nullptr;
};