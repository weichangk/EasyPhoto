#pragma once
#include "globalpresenter.h"
#include "observer/ifuncchangeobserver.h"
#include "mvp/repository.h"
#include "mvp/presenter.h"
#include "home/presenter.h"
#include "myfile/presenter.h"
#include "compression/presenter.h"
#include "conversion/presenter.h"
#include "crop/presenter.h"
#include "effects/presenter.h"
#include "upsc/presenter.h"
#include "erase/presenter.h"
#include "gifmk/presenter.h"
#include "inpainting/presenter.h"
#include "gifpreview/presenter.h"
#include "bgrm/presenter.h"
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
    CropPresenter *cropPresenter() const;
    EffectsPresenter *effectsPresenter() const;
    UpscPresenter *upscPresenter() const;
    ErasePresenter *erasePresenter() const;
    GifMkPresenter *gifMkPresenter() const;
    InpaintingPresenter *inpaintingPresenter() const;
    BgRmPresenter *bgRmPresenter() const;
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
    CropPresenter *m_pCropPresenter = nullptr;
    EffectsPresenter *m_pEffectsPresenter = nullptr;
    UpscPresenter *m_pUpscPresenter = nullptr;
    ErasePresenter *m_pErasePresenter = nullptr;
    GifMkPresenter *m_pGifMkPresenter = nullptr;
    InpaintingPresenter *m_pInpaintingPresenter = nullptr;
    BgRmPresenter *m_pBgRmPresenter = nullptr;
    ThumbnailMakerPresenter *m_pThumbnailMakerPresenter = nullptr;
    DownloaderPresenter *m_pDownloaderPresenter = nullptr;
    GifPreviewPresenter *m_pGifPreviewPresenter = nullptr;
};