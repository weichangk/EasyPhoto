#include "funcareapresenter.h"
#include "funcareaview.h"
#include "funcarearepository.h"
#include "message/funcchangemessage.h"

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
        m_pGifPreviewPresenter = new GifPreviewPresenter(funcAreaView->gifPreviewView(), funcRepository->gifPreviewRepository());
    }
}

FuncAreaPresenter::~FuncAreaPresenter() {
}

HomePresenter *FuncAreaPresenter::homePresente() const {
    return m_pHomePresenter;
}

MyFilePresenter *FuncAreaPresenter::myFilePresenter() const {
    return m_pMyFilePresenter;
}

CompressionPresenter *FuncAreaPresenter::compressionPresenter() const {
    return m_pCompressionPresenter;
}

ConversionPresenter *FuncAreaPresenter::conversionPresenter() const {
    return m_pConversionPresenter;
}

CroppingPresenter *FuncAreaPresenter::croppingPresenter() const {
    return m_pCroppingPresenter;
}

EffectsPresenter *FuncAreaPresenter::effectsPresenter() const {
    return m_pEffectsPresenter;
}

EnhancementPresenter *FuncAreaPresenter::enhancementPresenter() const {
    return m_pEnhancementPresenter;
}

ErasePresenter *FuncAreaPresenter::erasePresenter() const {
    return m_pErasePresenter;
}

GifGenerationPresenter *FuncAreaPresenter::gifGenerationPresenter() const {
    return m_pGifGenerationPresenter;
}

InpaintingPresenter *FuncAreaPresenter::inpaintingPresenter() const {
    return m_pInpaintingPresenter;
}

GifPreviewPresenter *FuncAreaPresenter::gifPreviewPresenter() const {
    return m_pGifPreviewPresenter;
}

void FuncAreaPresenter::funcChangeHandle(EFunc func) {
    FuncChangeMessage msg(func);
    view()->sendMessage(&msg);
}