#include "funcareapresenter.h"
#include "funcareaview.h"
#include "funcarearepository.h"
#include "funcchangemessage.h"

FuncAreaPresenter::FuncAreaPresenter(IView *view, IRepository *repository) :
    Presenter(view, repository) {
    FuncAreaView *funcAreaView = dynamic_cast<FuncAreaView *>(view);
    FuncAreaRepository *funcRepository = dynamic_cast<FuncAreaRepository *>(repository);
    if (funcAreaView && funcRepository) {
        m_pHomePresenter = new HomePresenter(funcAreaView->homeView(), funcRepository->homeRepository());
        m_pMyFilePresenter = new MyFilePresenter(funcAreaView->myFileView(), funcRepository->myFileRepository());
        m_pCompressionPresenter = new CompressionPresenter(funcAreaView->compressionView(), funcRepository->compressionRepository());
        m_pConversionPresenter = new ConversionPresenter(funcAreaView->conversionView(), funcRepository->conversionRepository());
        m_pCroppingPresenter = new CroppingPresenter(funcAreaView->croppingView(), funcRepository->croppingRepository());
        m_pEffectsPresenter = new EffectsPresenter(funcAreaView->effectsView(), funcRepository->effectsRepository());
        m_pEnhancementPresenter = new EnhancementPresenter(funcAreaView->enhancementView(), funcRepository->enhancementRepository());
        m_pErasePresenter = new ErasePresenter(funcAreaView->eraseView(), funcRepository->eraseRepository());
        m_pGifGenerationPresenter = new GifGenerationPresenter(funcAreaView->gifGenerationView(), funcRepository->gifGenerationRepository());
        m_pInpaintingPresenter = new InpaintingPresenter(funcAreaView->inpaintingView(), funcRepository->inpaintingRepository());
    }
}

FuncAreaPresenter::~FuncAreaPresenter() {
}

void FuncAreaPresenter::funcChange(EFunc func) {
    FuncChangeMessage msg(func);
    view()->sendMessage(&msg);
}