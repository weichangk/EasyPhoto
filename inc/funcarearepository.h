#pragma once
#include "globalpresenter.h"
#include "mvp/repository.h"
#include "home/repository.h"
#include "myfile/repository.h"
#include "compression/repository.h"
#include "conversion/repository.h"
#include "cropping/repository.h"
#include "effects/repository.h"
#include "enhancement/repository.h"
#include "erase/repository.h"
#include "gifmk/repository.h"
#include "inpainting/repository.h"
#include "bgrm/repository.h"
#include "thumbmaker/repository.h"
#include "downloader/repository.h"
#include "gifpreview/repository.h"

using namespace QtmMvp;

class FuncAreaRepository : public Repository {
public:
    explicit FuncAreaRepository();
    ~FuncAreaRepository();

    HomeRepository *homeRepository() const;
    MyFileRepository *myFileRepository() const;
    CompressionRepository *compressionRepository() const;
    ConversionRepository *conversionRepository() const;
    CroppingRepository *croppingRepository() const;
    EffectsRepository *effectsRepository() const;
    EnhancementRepository *enhancementRepository() const;
    EraseRepository *eraseRepository() const;
    GifMkRepository *gifMkRepository() const;
    InpaintingRepository *inpaintingRepository() const;
    ThumbnailMakerRepository *thumbnailMakerRepository() const;
    DownloaderRepository *downloaderRepository() const;
    BgRmRepository *bgRmRepository() const;
    GifPreviewRepository *gifPreviewRepository() const;

private:
    HomeRepository *m_pHomeRepository = nullptr;
    MyFileRepository *m_pMyFileRepository = nullptr;
    CompressionRepository *m_pCompressionRepository = nullptr;
    ConversionRepository *m_pConversionRepository = nullptr;
    CroppingRepository *m_pCroppingRepository = nullptr;
    EffectsRepository *m_pEffectsRepository = nullptr;
    EnhancementRepository *m_pEnhancementRepository = nullptr;
    EraseRepository *m_pEraseRepository = nullptr;
    GifMkRepository *m_pGifMkRepository = nullptr;
    InpaintingRepository *m_pInpaintingRepository = nullptr;
    ThumbnailMakerRepository *m_pThumbnailMakerRepository = nullptr;
    DownloaderRepository *m_pDownloaderRepository = nullptr;
    BgRmRepository *m_pBgRmRepository = nullptr;
    GifPreviewRepository *m_pGifPreviewRepository = nullptr;
};