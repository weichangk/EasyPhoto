#include "funcarearepository.h"

FuncAreaRepository::FuncAreaRepository() {
    m_pHomeRepository = new HomeRepository();
    m_pMyFileRepository = new MyFileRepository();
    m_pCompressionRepository = new CompressionRepository();
    m_pConversionRepository = new ConversionRepository();
    m_pCropRepository = new CropRepository();
    m_pEffectsRepository = new EffectsRepository();
    m_pEnhancementRepository = new EnhancementRepository();
    m_pEraseRepository = new EraseRepository();
    m_pGifMkRepository = new GifMkRepository();
    m_pInpaintingRepository = new InpaintingRepository();
    m_pBgRmRepository = new BgRmRepository();
    m_pThumbnailMakerRepository = new ThumbnailMakerRepository();
    m_pDownloaderRepository = new DownloaderRepository();
    m_pGifPreviewRepository = new GifPreviewRepository();
}

FuncAreaRepository::~FuncAreaRepository() {
}

HomeRepository *FuncAreaRepository::homeRepository() const {
    return m_pHomeRepository;
}

MyFileRepository *FuncAreaRepository::myFileRepository() const {
    return m_pMyFileRepository;
}

CompressionRepository *FuncAreaRepository::compressionRepository() const {
    return m_pCompressionRepository;
}

ConversionRepository *FuncAreaRepository::conversionRepository() const {
    return m_pConversionRepository;
}

CropRepository *FuncAreaRepository::cropRepository() const {
    return m_pCropRepository;
}

EffectsRepository *FuncAreaRepository::effectsRepository() const {
    return m_pEffectsRepository;
}

EnhancementRepository *FuncAreaRepository::enhancementRepository() const {
    return m_pEnhancementRepository;
}

EraseRepository *FuncAreaRepository::eraseRepository() const {
    return m_pEraseRepository;
}

GifMkRepository *FuncAreaRepository::gifMkRepository() const {
    return m_pGifMkRepository;
}

InpaintingRepository *FuncAreaRepository::inpaintingRepository() const {
    return m_pInpaintingRepository;
}

BgRmRepository *FuncAreaRepository::bgRmRepository() const {
    return m_pBgRmRepository;
}

ThumbnailMakerRepository *FuncAreaRepository::thumbnailMakerRepository() const {
    return m_pThumbnailMakerRepository;
}

DownloaderRepository *FuncAreaRepository::downloaderRepository() const {
    return m_pDownloaderRepository;
}

GifPreviewRepository *FuncAreaRepository::gifPreviewRepository() const {
    return m_pGifPreviewRepository;
}
