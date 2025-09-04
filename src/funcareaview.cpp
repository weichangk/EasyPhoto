#include "funcareaview.h"
#include "message/funcchangemessage.h"

FuncAreaView::FuncAreaView(QWidget *parent) :
    QWidget(parent) {
    createUi();
    connectSig();
}

HomeView *FuncAreaView::homeView() const {
    return m_pHomeView;
}

MyFileView *FuncAreaView::myFileView() const {
    return m_pMyFileView;
}

CompressionView *FuncAreaView::compressionView() const {
    return m_pCompressionView;
}

ConversionView *FuncAreaView::conversionView() const {
    return m_pConversionView;
}

CropView *FuncAreaView::cropView() const {
    return m_pCropView;
}

UpscView *FuncAreaView::upscView() const {
    return m_pUpscView;
}

EraseView *FuncAreaView::eraseView() const {
    return m_pEraseView;
}

GifMkView *FuncAreaView::gifMkView() const {
    return m_pGifMkView;
}

InpaintingView *FuncAreaView::inpaintingView() const {
    return m_pInpaintingView;
}

BgRmView *FuncAreaView::bgRmView() const {
    return m_pBgRmView;
}

ThumbMkView *FuncAreaView::thumbMkView() const {
    return m_pThumbMkView;
}

DownloaderView *FuncAreaView::downloaderView() const {
    return m_pDownloaderView;
}

ImagePreviewView *FuncAreaView::imagePreviewView() const {
    return m_pImagePreviewView;
}

GifPreviewView *FuncAreaView::gifPreviewView() const {
    return m_pGifPreviewView;
}

void FuncAreaView::createUi() {
    setObjectName("FuncAreaView");
    setAttribute(Qt::WA_StyledBackground);

    m_pStackedLayout = new QStackedLayout();
    m_pStackedLayout->setContentsMargins(0, 0, 0, 0);
    m_pStackedLayout->setSpacing(0);

    m_pHomeView = new HomeView(this);
    m_pMyFileView = new MyFileView(this);
    m_pCompressionView = new CompressionView(this);
    m_pConversionView = new ConversionView(this);
    m_pCropView = new CropView(this);
    m_pUpscView = new UpscView(this);
    m_pEraseView = new EraseView(this);
    m_pGifMkView = new GifMkView(this);
    m_pInpaintingView = new InpaintingView(this);
    m_pBgRmView = new BgRmView(this);
    m_pThumbMkView = new ThumbMkView(this);
    m_pDownloaderView = new DownloaderView(this);
    m_pImagePreviewView = new ImagePreviewView(this);
    m_pGifPreviewView = new GifPreviewView(this);

    m_pStackedLayout->insertWidget(EFunc::FuncHome, m_pHomeView);
    m_pStackedLayout->insertWidget(EFunc::FuncMyFile, m_pMyFileView);
    m_pStackedLayout->insertWidget(EFunc::FuncConversion, m_pConversionView);
    m_pStackedLayout->insertWidget(EFunc::FuncCompression, m_pCompressionView);
    m_pStackedLayout->insertWidget(EFunc::FuncUpsc, m_pUpscView);
    m_pStackedLayout->insertWidget(EFunc::FuncErase, m_pEraseView);
    m_pStackedLayout->insertWidget(EFunc::FuncBgRm, m_pBgRmView);
    m_pStackedLayout->insertWidget(EFunc::FuncCrop, m_pCropView);
    m_pStackedLayout->insertWidget(EFunc::FuncGifMk, m_pGifMkView);
    m_pStackedLayout->insertWidget(EFunc::FuncThumbMk, m_pThumbMkView);
    m_pStackedLayout->insertWidget(EFunc::FuncDownloader, m_pDownloaderView);
    m_pStackedLayout->insertWidget(EFunc::FuncInpainting, m_pInpaintingView);
    m_pStackedLayout->insertWidget(EFunc::FuncImagePreview, m_pImagePreviewView);
    m_pStackedLayout->insertWidget(EFunc::FuncGifPreview, m_pGifPreviewView);

    auto layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    layout->addLayout(m_pStackedLayout);
}

void FuncAreaView::connectSig() {
}

void FuncAreaView::setCurrentFuncView(EFunc func) {
    m_pStackedLayout->setCurrentIndex(func);
}

bool FuncAreaView::handleMessage(IMessage* message) {
    if (FuncChangeMessage *msg = dynamic_cast<FuncChangeMessage *>(message)) {
        EFunc ef = (EFunc)msg->code();
        // setCurrentFuncView(ef);
        std::function<void(EFunc)> func = [&](EFunc e) {
            setCurrentFuncView(e);
        };
        if (ef == EFunc::FuncUndo || ef == EFunc::FuncRedo) {
            ef == EFunc::FuncUndo ? m_rFuncNavigationHistory.undo() : m_rFuncNavigationHistory.redo();
        } else {
            m_ePreviousFunc = m_eCurrentFunc;
            m_eCurrentFunc = ef;
            if (m_ePreviousFunc != m_eCurrentFunc) {
                m_rFuncNavigationHistory.executeCommand(m_ePreviousFunc, ef, func);
            }
        }
    }
    return false;
}