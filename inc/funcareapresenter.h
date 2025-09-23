#pragma once
#include "globalpresenter.h"
#include "observer/ifuncchangeobserver.h"
#include "mvp/repository.h"
#include "mvp/presenter.h"
#include "home/presenter.h"
#include "myfile/presenter.h"
#include "compression/presenter.h"
#include "conv/presenter.h"
#include "crop/presenter.h"
#include "upsc/presenter.h"
#include "erase/presenter.h"
#include "gifmk/presenter.h"
#include "gifpreview/presenter.h"
#include "bgrm/presenter.h"
#include "thumbmk/presenter.h"
#include "imgdl/presenter.h"

using namespace QtmMvp;

class FuncAreaPresenter : public Presenter, public IFuncChangeObserver {
public:
    explicit FuncAreaPresenter(IView *view, IRepository *repository);
    ~FuncAreaPresenter();

    HomePresenter *homePresente() const;
    MyFilePresenter *myFilePresenter() const;
    CompressionPresenter *compressionPresenter() const;
    ConvPresenter *conversionPresenter() const;
    CropPresenter *cropPresenter() const;
    UpscPresenter *upscPresenter() const;
    ErasePresenter *erasePresenter() const;
    GifMkPresenter *gifMkPresenter() const;
    BgRmPresenter *bgRmPresenter() const;
    ThumbMkPresenter *thumbMkPresenter() const;
    ImgDlPresenter *imgDlPresenter() const;
    GifPreviewPresenter *gifPreviewPresenter() const;

private:
    void funcChangeHandle(EFunc) override;

private:
    HomePresenter *m_pHomePresenter = nullptr;
    MyFilePresenter *m_pMyFilePresenter = nullptr;
    CompressionPresenter *m_pCompressionPresenter = nullptr;
    ConvPresenter *m_pConvPresenter = nullptr;
    CropPresenter *m_pCropPresenter = nullptr;
    UpscPresenter *m_pUpscPresenter = nullptr;
    ErasePresenter *m_pErasePresenter = nullptr;
    GifMkPresenter *m_pGifMkPresenter = nullptr;
    BgRmPresenter *m_pBgRmPresenter = nullptr;
    ThumbMkPresenter *m_pThumbMkPresenter = nullptr;
    ImgDlPresenter *m_pImgDlPresenter = nullptr;
    GifPreviewPresenter *m_pGifPreviewPresenter = nullptr;
};