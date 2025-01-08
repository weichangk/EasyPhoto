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

    m_pStackedLayout->insertWidget(0, m_pCompressionView);
    m_pStackedLayout->insertWidget(1, m_pConversionView);
    m_pStackedLayout->insertWidget(2, m_pCroppingView);
    m_pStackedLayout->insertWidget(3, m_pEffectsView);
    m_pStackedLayout->insertWidget(4, m_pEnhancementView);
    m_pStackedLayout->insertWidget(5, m_pEraseView);
    m_pStackedLayout->insertWidget(6, m_pGifGenerationView);
    m_pStackedLayout->insertWidget(7, m_pInpaintingView);

    auto layout = new QVBoxLayout(this);
    layout->setContentsMargins(16, 8, 16, 12);
    layout->setSpacing(0);

    layout->addLayout(m_pStackedLayout);
}

void FuncAreaView::connectSig() {
}