#include "funcarearepository.h"

FuncAreaRepository::FuncAreaRepository() {
    m_pHomeRepository = new HomeRepository();
    m_pMyFileRepository = new MyFileRepository();
    m_pCompRepository = new CompRepository();
    m_pConvRepository = new ConvRepository();
    m_pCropRepository = new CropRepository();
    m_pUpscRepository = new UpscRepository();
    m_pEraseRepository = new EraseRepository();
    m_pGifMkRepository = new GifMkRepository();
    m_pBgRmRepository = new BgRmRepository();
    m_pThumbMkRepository = new ThumbMkRepository();
    m_pImgDlRepository = new ImgDlRepository();
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

CompRepository *FuncAreaRepository::compressionRepository() const {
    return m_pCompRepository;
}

ConvRepository *FuncAreaRepository::conversionRepository() const {
    return m_pConvRepository;
}

CropRepository *FuncAreaRepository::cropRepository() const {
    return m_pCropRepository;
}

UpscRepository *FuncAreaRepository::upscRepository() const {
    return m_pUpscRepository;
}

EraseRepository *FuncAreaRepository::eraseRepository() const {
    return m_pEraseRepository;
}

GifMkRepository *FuncAreaRepository::gifMkRepository() const {
    return m_pGifMkRepository;
}

BgRmRepository *FuncAreaRepository::bgRmRepository() const {
    return m_pBgRmRepository;
}

ThumbMkRepository *FuncAreaRepository::thumbMkRepository() const {
    return m_pThumbMkRepository;
}

ImgDlRepository *FuncAreaRepository::imgDlRepository() const {
    return m_pImgDlRepository;
}

GifPreviewRepository *FuncAreaRepository::gifPreviewRepository() const {
    return m_pGifPreviewRepository;
}
