#pragma once
#include "globalview.h"
#include "funcenum.h"
#include "mvp/view.h"
#include "home/view.h"
#include "myfile/view.h"
#include "compression/view.h"
#include "conversion/view.h"
#include "crop/view.h"
#include "effects/view.h"
#include "enhancement/view.h"
#include "erase/view.h"
#include "gifmk/view.h"
#include "inpainting/view.h"
#include "gifpreview/view.h"
#include "bgrm/view.h"
#include "thumbmaker/view.h"
#include "downloader/view.h"
#include "imagepreviewview.h"
#include "funcnavigationhistory.h"

#include <QStackedLayout>

using namespace QtmMvp;

class FuncAreaView : public QWidget, public View {
    Q_OBJECT
public:
    explicit FuncAreaView(QWidget *parent = nullptr);
    ~FuncAreaView() override {
    }

    HomeView *homeView() const;
    MyFileView *myFileView() const;
    CompressionView *compressionView() const;
    ConversionView *conversionView() const;
    CropView *cropView() const;
    EffectsView *effectsView() const;
    EnhancementView *enhancementView() const;
    EraseView *eraseView() const;
    GifMkView *gifMkView() const;
    InpaintingView *inpaintingView() const;
    BgRmView *bgRmView() const;
    ThumbnailMakerView *thumbnailMakerView() const;
    DownloaderView *downloaderView() const;
    ImagePreviewView *imagePreviewView() const;
    GifPreviewView *gifPreviewView() const;

private:
    void createUi();
    void connectSig();
    void setCurrentFuncView(EFunc);

private:
    bool handleMessage(IMessage *message) override;

private:
    FuncNavigationHistory m_rFuncNavigationHistory;
    EFunc m_ePreviousFunc = EFunc::FuncHome;
    EFunc m_eCurrentFunc = EFunc::FuncHome;

    QStackedLayout *m_pStackedLayout = nullptr;
    HomeView *m_pHomeView = nullptr;
    MyFileView *m_pMyFileView = nullptr;
    CompressionView *m_pCompressionView = nullptr;
    ConversionView *m_pConversionView = nullptr;
    CropView *m_pCropView = nullptr;
    EffectsView *m_pEffectsView = nullptr;
    EnhancementView *m_pEnhancementView = nullptr;
    EraseView *m_pEraseView = nullptr;
    GifMkView *m_pGifMkView = nullptr;
    InpaintingView *m_pInpaintingView = nullptr;
    BgRmView *m_pBgRmView = nullptr;
    ThumbnailMakerView *m_pThumbnailMakerView = nullptr;
    DownloaderView *m_pDownloaderView = nullptr;
    ImagePreviewView *m_pImagePreviewView = nullptr;
    GifPreviewView *m_pGifPreviewView = nullptr;
};