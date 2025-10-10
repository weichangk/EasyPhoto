#include "upsc/presenter.h"
#include "upsc/repository.h"
#include "upsc/view.h"
#include "upsc/task.h"
#include "upsc/types.h"
#include "core/file.h"
#include "task/asynctask.h"
#include "task/taskfactory.h"
#include "task/taskdata.h"
#include "task/taskresult.h"
#include "message/upsc/upscresultmessage.h"
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
    auto func = [this](AsyncTask<void*, std::vector<EasyPhotoCore::Upsc::SResult>> *task) -> TaskResult<std::vector<EasyPhotoCore::Upsc::SResult>> {
        auto datas = m_pImportListPresenter->getDatas();
        std::vector<EasyPhotoCore::Upsc::SResult> results;
        foreach (auto data, datas) {
            QFileInfo fileInfo(data.file_path);
            QString baseName = fileInfo.completeBaseName();
            QString suffix = fileInfo.suffix(); 
            QString outPath = QString("%1/%2-%3-%4x.%5")
            .arg(SETTINGS->getUpscSetting()->getOutPath())
            .arg(UPSC_MODEL_NAMES[(EUpscModelType)SETTINGS->getUpscSetting()->getModelType()])
            .arg(baseName)
            .arg(SETTINGS->getUpscSetting()->getScale())
            .arg(SETTINGS->getUpscSetting()->getOutFmt());
            File::renameIfExists(outPath, false);

            EasyPhotoCore::Upsc::SParam param;
            param.inputFile = data.file_path;
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
            EasyPhotoCore::Upsc::Task task;
            EasyPhotoCore::Upsc::SResult res = task.exec(param);
            results.push_back(res);
        }
        view()->sendMessage(new UpscResultMessage(results, 0));
        return TaskResult<std::vector<EasyPhotoCore::Upsc::SResult>>::Success(results);
    };
    auto task = TaskFactory::instance()->createTask<void*, std::vector<EasyPhotoCore::Upsc::SResult>>(func, nullptr, TaskData<void*>());
    task->start();
}

bool UpscPresenter::handleMessage(IMessage* message) {
    return false;
}
