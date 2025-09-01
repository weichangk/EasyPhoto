#pragma once
#include "globalpresenter.h"
#include "observer/ifuncchangeobserver.h"
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
#include "gifmk/presenter.h"
#include "inpainting/presenter.h"
#include "gifpreview/presenter.h"
#include "bgremover/presenter.h"
#include "thumbmaker/presenter.h"
#include "downloader/presenter.h"

using namespace QtmMvp;

class FuncAreaPresenter : public Presenter, public IFuncChangeObserver {
public:
    explicit FuncAreaPresenter(IView *view, IRepository *repository);
    ~FuncAreaPresenter();

    HomePresenter *homePresente() const;
    MyFilePresenter *myFilePresenter() const;
    CompressionPresenter *compressionPresenter() const;
    ConversionPresenter *conversionPresenter() const;
    CroppingPresenter *croppingPresenter() const;
    EffectsPresenter *effectsPresenter() const;
    EnhancementPresenter *enhancementPresenter() const;
    ErasePresenter *erasePresenter() const;
    GifMkPresenter *gifMkPresenter() const;
    InpaintingPresenter *inpaintingPresenter() const;
    BackgroungRemoverPresenter *backgroungRemoverPresenter() const;
    ThumbnailMakerPresenter *thumbnailMakerPresenter() const;
    DownloaderPresenter *downloaderPresenter() const;
    GifPreviewPresenter *gifPreviewPresenter() const;

private:
    void funcChangeHandle(EFunc) override;

private:
    HomePresenter *m_pHomePresenter = nullptr;
    MyFilePresenter *m_pMyFilePresenter = nullptr;
    CompressionPresenter *m_pCompressionPresenter = nullptr;
    ConversionPresenter *m_pConversionPresenter = nullptr;
    CroppingPresenter *m_pCroppingPresenter = nullptr;
    EffectsPresenter *m_pEffectsPresenter = nullptr;
    EnhancementPresenter *m_pEnhancementPresenter = nullptr;
    ErasePresenter *m_pErasePresenter = nullptr;
    GifMkPresenter *m_pGifMkPresenter = nullptr;
    InpaintingPresenter *m_pInpaintingPresenter = nullptr;
    BackgroungRemoverPresenter *m_pBackgroungRemoverPresenter = nullptr;
    ThumbnailMakerPresenter *m_pThumbnailMakerPresenter = nullptr;
    DownloaderPresenter *m_pDownloaderPresenter = nullptr;
    GifPreviewPresenter *m_pGifPreviewPresenter = nullptr;
};