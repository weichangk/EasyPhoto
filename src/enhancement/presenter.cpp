#include "enhancement/presenter.h"
#include "enhancement/repository.h"
#include "enhancement/view.h"
#include "upscayl/upscayl.h"
#include "upscayl/types.h"
#include "core/file.h"

using namespace qtmaterialcore;

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
        upscayl::SUpscaylPayload payload;
        payload.inputFile = data.path;
        payload.outputFile = outPath;
        payload.scale = 1;
        payload.modelName = "upscayl-standard-4x";
        payload.gpuId = "";
        payload.useSaveAsFormat = false;
        payload.useCustomWidth = false;
        payload.useCompression = false;
        payload.tileSize = 0;
        payload.ttaMode = false;
        upscayl::Upscayl upscayl;
        upscayl.exec(payload);
    }
}