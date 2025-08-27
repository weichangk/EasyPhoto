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
#include "gifgeneration/repository.h"
#include "inpainting/repository.h"
#include "bgremover/repository.h"
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
    GifGenerationRepository *gifGenerationRepository() const;
    InpaintingRepository *inpaintingRepository() const;
    ThumbnailMakerRepository *thumbnailMakerRepository() const;
    DownloaderRepository *downloaderRepository() const;
    BackgroungRemoverRepository *backgroungRemoverRepository() const;
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
    GifGenerationRepository *m_pGifGenerationRepository = nullptr;
    InpaintingRepository *m_pInpaintingRepository = nullptr;
    ThumbnailMakerRepository *m_pThumbnailMakerRepository = nullptr;
    DownloaderRepository *m_pDownloaderRepository = nullptr;
    BackgroungRemoverRepository *m_pBackgroungRemoverRepository = nullptr;
    GifPreviewRepository *m_pGifPreviewRepository = nullptr;
};