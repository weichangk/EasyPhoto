#pragma once
#include "globalpresenter.h"
#include "ifuncchangeobserver.h"
#include "mvp/repository.h"
#include "mvp/presenter.h"
#include "home/presenter.h"
#include "myfile/presenter.h"
#include "compression/presenter.h"
#include "conversion/presenter.h"
#include "cropping/presenter.h"
#include "effects/presenter.h"
#include "enhancement/presenter.h"
#include "erase/presenter.h"
#include "gifgeneration/presenter.h"
#include "inpainting/presenter.h"

using namespace qtmaterialmvp;

class FuncAreaPresenter : public Presenter, public IFuncChangeObserver {
public:
    explicit FuncAreaPresenter(IView *view, IRepository *repository);
    ~FuncAreaPresenter();

    HomePresenter *homePresente();
    MyFilePresenter *myFilePresenter();
    CompressionPresenter *compressionPresenter();
    ConversionPresenter *conversionPresenter();
    CroppingPresenter *croppingPresenter();
    EffectsPresenter *effectsPresenter();
    EnhancementPresenter *enhancementPresenter();
    ErasePresenter *erasePresenter();
    GifGenerationPresenter *gifGenerationPresenter();
    InpaintingPresenter *inpaintingPresenter();

private:
    void funcChange(EFunc) override;

private:
    HomePresenter *m_pHomePresenter = nullptr;
    MyFilePresenter *m_pMyFilePresenter = nullptr;
    CompressionPresenter *m_pCompressionPresenter = nullptr;
    ConversionPresenter *m_pConversionPresenter = nullptr;
    CroppingPresenter *m_pCroppingPresenter = nullptr;
    EffectsPresenter *m_pEffectsPresenter = nullptr;
    EnhancementPresenter *m_pEnhancementPresenter = nullptr;
    ErasePresenter *m_pErasePresenter = nullptr;
    GifGenerationPresenter *m_pGifGenerationPresenter = nullptr;
    InpaintingPresenter *m_pInpaintingPresenter = nullptr;
};