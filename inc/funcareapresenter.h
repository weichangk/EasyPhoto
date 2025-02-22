#pragma once
#include "globalpresenter.h"
#include "navbarobserver.h"
#include "mvp/repository.h"
#include "mvp/presenter.h"
#include "homepresenter.h"
#include "myfilepresenter.h"
#include "compression/presenter.h"
#include "conversion/presenter.h"
#include "cropping/presenter.h"
#include "effects/presenter.h"
#include "enhancement/presenter.h"
#include "erase/presenter.h"
#include "gifgeneration/presenter.h"
#include "inpainting/presenter.h"

using namespace qtmaterialmvp;

class FuncAreaPresenter : public Presenter, public INavbarObserver {
public:
    explicit FuncAreaPresenter(IView* view, IRepository *repository);
    ~FuncAreaPresenter();

private:
    void navChange(EFunc) override;

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