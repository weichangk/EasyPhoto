#pragma once
#include "globalpresenter.h"
#include "mvp/repository.h"
#include "home/repository.h"
#include "myfile/repository.h"
#include "compression/repository.h"
#include "conv/repository.h"
#include "crop/repository.h"
#include "upsc/repository.h"
#include "erase/repository.h"
#include "gifmk/repository.h"
#include "bgrm/repository.h"
#include "thumbmk/repository.h"
#include "imgdl/repository.h"
#include "gifpreview/repository.h"

using namespace QtmMvp;

class FuncAreaRepository : public Repository {
public:
    explicit FuncAreaRepository();
    ~FuncAreaRepository();

    HomeRepository *homeRepository() const;
    MyFileRepository *myFileRepository() const;
    CompressionRepository *compressionRepository() const;
    ConvRepository *conversionRepository() const;
    CropRepository *cropRepository() const;
    UpscRepository *upscRepository() const;
    EraseRepository *eraseRepository() const;
    GifMkRepository *gifMkRepository() const;
    ThumbMkRepository *thumbMkRepository() const;
    ImgDlRepository *imgDlRepository() const;
    BgRmRepository *bgRmRepository() const;
    GifPreviewRepository *gifPreviewRepository() const;

private:
    HomeRepository *m_pHomeRepository = nullptr;
    MyFileRepository *m_pMyFileRepository = nullptr;
    CompressionRepository *m_pCompressionRepository = nullptr;
    ConvRepository *m_pConvRepository = nullptr;
    CropRepository *m_pCropRepository = nullptr;
    UpscRepository *m_pUpscRepository = nullptr;
    EraseRepository *m_pEraseRepository = nullptr;
    GifMkRepository *m_pGifMkRepository = nullptr;
    ThumbMkRepository *m_pThumbMkRepository = nullptr;
    ImgDlRepository *m_pImgDlRepository = nullptr;
    BgRmRepository *m_pBgRmRepository = nullptr;
    GifPreviewRepository *m_pGifPreviewRepository = nullptr;
};