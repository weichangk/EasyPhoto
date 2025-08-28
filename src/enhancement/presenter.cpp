#include "enhancement/presenter.h"
#include "enhancement/repository.h"
#include "enhancement/view.h"
#include "upsc/task.h"
#include "upsc/types.h"
#include "core/file.h"

using namespace QtmCore;

EnhancementPresenter::EnhancementPresenter(IView *view, IRepository *repository) :
    Presenter(view, repository) {
    EnhancementView *enhancementView = dynamic_cast<EnhancementView *>(view);
    EnhancementRepository *enhancementRepository = dynamic_cast<EnhancementRepository *>(repository);
    m_pImportListPresenter = new ImportListPresenter(enhancementView->getImportListView(), enhancementRepository->getImportListRepository());
}

EnhancementPresenter::~EnhancementPresenter() {
}

QList<SEnhanceModelData> EnhancementPresenter::getModelDatas() {
    EnhancementRepository *rep = dynamic_cast<EnhancementRepository *>(repository());
    return rep->getModelDatas();
}

QString EnhancementPresenter::getSampleImage1Path() {
    EnhancementRepository *rep = dynamic_cast<EnhancementRepository *>(repository());
    return rep->getSampleImage1Path();
}

QString EnhancementPresenter::getSampleImage2Path() {
    EnhancementRepository *rep = dynamic_cast<EnhancementRepository *>(repository());
    return rep->getSampleImage2Path();
}

void EnhancementPresenter::Enhancement() {
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