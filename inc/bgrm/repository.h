#pragma once
#include "globalpresenter.h"
#include "types.h"
#include "mvp/repository.h"
#include "import/importlistrepository.h"

using namespace QtmMvp;

class BgRmRepository : public Repository {
public:
    explicit BgRmRepository();
    ~BgRmRepository();

    QString getSampleImage1Path();
    QString getSampleImage2Path();

    QList<SBgImgData> getBgImgDataDatas(EBgImgType type);

    ImportListRepository *getImportListRepository();

private:
    ImportListRepository *m_pImportListRepository = nullptr;

    QList<SBgImgData> m_BgGeneralImgDatas;
    QList<SBgImgData> m_BgSceneImgDatas;
};