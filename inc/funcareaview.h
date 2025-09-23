#pragma once
#include "globalview.h"
#include "funcenum.h"
#include "mvp/view.h"
#include "home/view.h"
#include "myfile/view.h"
#include "compression/view.h"
#include "conv/view.h"
#include "crop/view.h"
#include "upsc/view.h"
#include "erase/view.h"
#include "gifmk/view.h"
#include "gifpreview/view.h"
#include "bgrm/view.h"
#include "thumbmk/view.h"
#include "imgdl/view.h"
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
    ConvView *conversionView() const;
    CropView *cropView() const;
    UpscView *upscView() const;
    EraseView *eraseView() const;
    GifMkView *gifMkView() const;
    BgRmView *bgRmView() const;
    ThumbMkView *thumbMkView() const;
    ImgDlView *imgDlView() const;
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
    ConvView *m_pConvView = nullptr;
    CropView *m_pCropView = nullptr;
    UpscView *m_pUpscView = nullptr;
    EraseView *m_pEraseView = nullptr;
    GifMkView *m_pGifMkView = nullptr;
    BgRmView *m_pBgRmView = nullptr;
    ThumbMkView *m_pThumbMkView = nullptr;
    ImgDlView *m_pImgDlView = nullptr;
    ImagePreviewView *m_pImagePreviewView = nullptr;
    GifPreviewView *m_pGifPreviewView = nullptr;
};