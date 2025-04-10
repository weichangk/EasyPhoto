#pragma once
#include "globalpresenter.h"
#include "mvp/repository.h"
#include "mvp/presenter.h"
#include "model.h"
#include "import/importlistpresenter.h"

using namespace qtmaterialmvp;

class ErasePresenter : public Presenter {
public:
    explicit ErasePresenter(IView* view, IRepository *repository);
    ~ErasePresenter();

    QString getSampleImage1Path();
    QString getSampleImage2Path();

private:
    ImportListPresenter * m_pImportListPresenter = nullptr;
};