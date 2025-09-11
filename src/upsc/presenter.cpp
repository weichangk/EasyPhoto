#include "upsc/presenter.h"
#include "upsc/repository.h"
#include "upsc/view.h"
#include "upsc/task.h"
#include "ImageKitCore/inc/upsc/types.h"
#include "core/file.h"

using namespace QtmCore;

UpscPresenter::UpscPresenter(IView *view, IRepository *repository) :
    Presenter(view, repository) {
    UpscView *enhancementView = dynamic_cast<UpscView *>(view);
    UpscRepository *enhancementRepository = dynamic_cast<UpscRepository *>(repository);
    m_pImportListPresenter = new ImportListPresenter(enhancementView->getImportListView(), enhancementRepository->getImportListRepository());
}

UpscPresenter::~UpscPresenter() {
}

QList<SUpscSelectModelData> UpscPresenter::getSelectModelDatas() {
    UpscRepository *rep = dynamic_cast<UpscRepository *>(repository());
    return rep->getSelectModelDatas();
}

QString UpscPresenter::getSampleImagePath(EUpscSmapleType type) {
    UpscRepository *rep = dynamic_cast<UpscRepository *>(repository());
    return rep->getSampleImagePath(type);
}

void UpscPresenter::Upsc() {
    auto datas = m_pImportListPresenter->getDatas();
    foreach (auto data, datas) {
        QString outPath = data.path;
        File::renameIfExists(outPath);
        ImgKitCore::UPSC::SParam param;
        param.inputFile = data.path;
        param.outputFile = outPath;
        param.scale = 1;
        param.modelName = "upscayl-standard-4x";
        param.gpuId = "";
        param.compression = 0;
        param.saveAsFormat = ImgKitCore::UPSC::EFormat::PNG;
        param.useCustomWidth = false;
        param.customWidth = 1000;
        param.tileSize = 0;
        param.ttaMode = false;
        ImgKitCore::UPSC::Task task;
        task.exec(param);
    }
}