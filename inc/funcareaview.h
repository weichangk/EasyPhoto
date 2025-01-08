#pragma once
#include "globalview.h"
#include "mvp/view.h"
#include "compression/view.h"
#include "conversion/view.h"
#include "cropping/view.h"
#include "effects/view.h"
#include "enhancement/view.h"
#include "erase/view.h"
#include "gifgeneration/view.h"
#include "inpainting/view.h"

#include <QStackedLayout>

using namespace qtmaterialmvp;

class FuncAreaView : public QWidget, public View {
    Q_OBJECT
public:
    explicit FuncAreaView(QWidget *parent = nullptr);
    ~FuncAreaView() override {
    }

    CompressionView *compressionView() const;
    ConversionView *conversionView() const;
    CroppingView *croppingView() const;
    EffectsView *effectsView() const;
    EnhancementView *enhancementView() const;
    EraseView *eraseView() const;
    GifGenerationView *gifGenerationView() const;
    InpaintingView *inpaintingView() const;

private:
    void createUi();
    void connectSig();

private:
    QStackedLayout *m_pStackedLayout = nullptr;
    CompressionView *m_pCompressionView = nullptr;
    ConversionView *m_pConversionView = nullptr;
    CroppingView *m_pCroppingView = nullptr;
    EffectsView *m_pEffectsView = nullptr;
    EnhancementView *m_pEnhancementView = nullptr;
    EraseView *m_pEraseView = nullptr;
    GifGenerationView *m_pGifGenerationView = nullptr;
    InpaintingView *m_pInpaintingView = nullptr;
};