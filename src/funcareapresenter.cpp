#include "funcareapresenter.h"
#include "funcareaview.h"
#include "funcarearepository.h"
#include "message/funcchangemessage.h"

FuncAreaPresenter::FuncAreaPresenter(IView *view, IRepository *repository) :
    Presenter(view, repository) {
    FuncAreaView *funcAreaView = dynamic_cast<FuncAreaView *>(view);
    FuncAreaRepository *funcRepository = dynamic_cast<FuncAreaRepository *>(repository);
    if (funcAreaView && funcRepository) {
        m_pHomePresenter = new HomePresenter(funcAreaView->homeView(), funcRepository->homeRepository());
        m_pMyFilePresenter = new MyFilePresenter(funcAreaView->myFileView(), funcRepository->myFileRepository());
        m_pCompressionPresenter = new CompressionPresenter(funcAreaView->compressionView(), funcRepository->compressionRepository());
        m_pConvPresenter = new ConvPresenter(funcAreaView->conversionView(), funcRepository->conversionRepository());
        m_pCropPresenter = new CropPresenter(funcAreaView->cropView(), funcRepository->cropRepository());
        m_pUpscPresenter = new UpscPresenter(funcAreaView->upscView(), funcRepository->upscRepository());
        m_pErasePresenter = new ErasePresenter(funcAreaView->eraseView(), funcRepository->eraseRepository());
        m_pGifMkPresenter = new GifMkPresenter(funcAreaView->gifMkView(), funcRepository->gifMkRepository());
        m_pBgRmPresenter = new BgRmPresenter(funcAreaView->bgRmView(), funcRepository->bgRmRepository());
        m_pThumbMkPresenter = new ThumbMkPresenter(funcAreaView->thumbMkView(), funcRepository->thumbMkRepository());
        m_pImgDlPresenter = new ImgDlPresenter(funcAreaView->imgDlView(), funcRepository->imgDlRepository());
        m_pGifPreviewPresenter = new GifPreviewPresenter(funcAreaView->gifPreviewView(), funcRepository->gifPreviewRepository());
    }
}

FuncAreaPresenter::~FuncAreaPresenter() {
}

HomePresenter *FuncAreaPresenter::homePresente() const {
    return m_pHomePresenter;
}

MyFilePresenter *FuncAreaPresenter::myFilePresenter() const {
    return m_pMyFilePresenter;
}

CompressionPresenter *FuncAreaPresenter::compressionPresenter() const {
    return m_pCompressionPresenter;
}

ConvPresenter *FuncAreaPresenter::conversionPresenter() const {
    return m_pConvPresenter;
}

CropPresenter *FuncAreaPresenter::cropPresenter() const {
    return m_pCropPresenter;
}

UpscPresenter *FuncAreaPresenter::upscPresenter() const {
    return m_pUpscPresenter;
}

ErasePresenter *FuncAreaPresenter::erasePresenter() const {
    return m_pErasePresenter;
}

GifMkPresenter *FuncAreaPresenter::gifMkPresenter() const {
    return m_pGifMkPresenter;
}

BgRmPresenter *FuncAreaPresenter::bgRmPresenter() const {
    return m_pBgRmPresenter;
}

ThumbMkPresenter *FuncAreaPresenter::thumbMkPresenter() const {
    return m_pThumbMkPresenter;
}

ImgDlPresenter *FuncAreaPresenter::imgDlPresenter() const {
    return m_pImgDlPresenter;
}

GifPreviewPresenter *FuncAreaPresenter::gifPreviewPresenter() const {
    return m_pGifPreviewPresenter;
}

void FuncAreaPresenter::funcChangeHandle(EFunc func) {
    FuncChangeMessage msg(func);
    view()->sendMessage(&msg);
}