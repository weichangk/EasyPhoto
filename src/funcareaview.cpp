#include "funcareaview.h"

FuncAreaView::FuncAreaView(QWidget *parent) :
    QWidget(parent) {
    createUi();
    connectSig();
}

CompressionView *FuncAreaView::compressionView() const {
    return m_pCompressionView;
}

ConversionView *FuncAreaView::conversionView() const {
    return m_pConversionView;
}

CroppingView *FuncAreaView::croppingView() const {
    return m_pCroppingView;
}

EffectsView *FuncAreaView::effectsView() const {
    return m_pEffectsView;
}

EnhancementView *FuncAreaView::enhancementView() const {
    return m_pEnhancementView;
}

EraseView *FuncAreaView::eraseView() const {
    return m_pEraseView;
}

GifGenerationView *FuncAreaView::gifGenerationView() const {
    return m_pGifGenerationView;
}

InpaintingView *FuncAreaView::inpaintingView() const {
    return m_pInpaintingView;
}

void FuncAreaView::setCurrentFuncView(EFunc func) {
    m_pStackedLayout->setCurrentIndex(func);
}

void FuncAreaView::createUi() {
    setObjectName("FuncAreaView");
    setAttribute(Qt::WA_StyledBackground);

    m_pStackedLayout = new QStackedLayout();
    m_pStackedLayout->setContentsMargins(0, 0, 0, 0);
    m_pStackedLayout->setSpacing(0);

    m_pCompressionView = new CompressionView(this);
    m_pConversionView = new ConversionView(this);
    m_pCroppingView = new CroppingView(this);
    m_pEffectsView = new EffectsView(this);
    m_pEnhancementView = new EnhancementView(this);
    m_pEraseView = new EraseView(this);
    m_pGifGenerationView = new GifGenerationView(this);
    m_pInpaintingView = new InpaintingView(this);

    m_pStackedLayout->insertWidget(EFunc::FuncConversion, m_pConversionView);
    m_pStackedLayout->insertWidget(EFunc::FuncCompression, m_pCompressionView);
    m_pStackedLayout->insertWidget(EFunc::FuncCropping, m_pCroppingView);
    m_pStackedLayout->insertWidget(EFunc::FuncErase, m_pEraseView);
    m_pStackedLayout->insertWidget(EFunc::FuncEnhancement, m_pEnhancementView);
    m_pStackedLayout->insertWidget(EFunc::FuncInpainting, m_pInpaintingView);
    m_pStackedLayout->insertWidget(EFunc::FuncEffects, m_pEffectsView);
    m_pStackedLayout->insertWidget(EFunc::FuncGifGeneration, m_pGifGenerationView);

    auto layout = new QVBoxLayout(this);
    layout->setContentsMargins(16, 8, 16, 12);
    layout->setSpacing(0);

    layout->addLayout(m_pStackedLayout);
}

void FuncAreaView::connectSig() {
}