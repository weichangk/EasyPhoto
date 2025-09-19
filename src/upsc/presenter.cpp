#include "upsc/presenter.h"
#include "upsc/repository.h"
#include "upsc/view.h"
#include "upsc/task.h"
#include "ImageKitCore/inc/upsc/types.h"
#include "core/file.h"
#include "settings.h"
#include "types.h"

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

QString UpscPresenter::getSampleBeforeImagePath(EUpscModelType type) {
    UpscRepository *rep = dynamic_cast<UpscRepository *>(repository());
    return rep->getSampleBeforeImagePath(type);
}

void UpscPresenter::Upsc() {
    auto datas = m_pImportListPresenter->getDatas();
    foreach (auto data, datas) {
        QFileInfo fileInfo(data.path);
        QString baseName = fileInfo.completeBaseName();
        QString suffix = fileInfo.suffix(); 
        QString outPath = QString("%1/%2-%3-%4x.%5")
        .arg(SETTINGS->getUpscSetting()->getOutPath())
        .arg(UPSC_MODEL_NAMES[(EUpscModelType)SETTINGS->getUpscSetting()->getModelType()])
        .arg(baseName)
        .arg(SETTINGS->getUpscSetting()->getScale())
        .arg(SETTINGS->getUpscSetting()->getOutFmt());
        File::renameIfExists(outPath, false);

        ImgKitCore::UPSC::SParam param;
        param.inputFile = data.path;
        param.outputFile = outPath;
        param.scale = SETTINGS->getUpscSetting()->getScale();
        param.modelName = UPSC_MODEL_NAMES[(EUpscModelType)SETTINGS->getUpscSetting()->getModelType()];
        param.gpuId = "";
        param.compression = 0;
        param.saveAsFormat = SETTINGS->getUpscSetting()->getOutFmt();
        param.useCustomWidth = false;
        param.customWidth = 0;
        param.tileSize = 0;
        param.ttaMode = false;
        ImgKitCore::UPSC::Task task;
        task.exec(param);
    }
}