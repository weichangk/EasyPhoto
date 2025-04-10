#pragma once
#include "globalpresenter.h"
#include "mvp/repository.h"
#include "mvp/presenter.h"
#include "model.h"
#include "import/importlistpresenter.h"

using namespace qtmaterialmvp;

class CroppingPresenter : public Presenter {
public:
    explicit CroppingPresenter(IView* view, IRepository *repository);
    ~CroppingPresenter();

    QString getSampleImage1Path();
    QString getSampleImage2Path();

private:
    ImportListPresenter * m_pImportListPresenter = nullptr;
};