#include "funcarearepository.h"

FuncAreaRepository::FuncAreaRepository() {
    m_pCompressionRepository = new CompressionRepository();
    m_pConversionRepository = new ConversionRepository();
    m_pCroppingRepository = new CroppingRepository();
    m_pEffectsRepository = new EffectsRepository();
    m_pEnhancementRepository = new EnhancementRepository();
    m_pEraseRepository = new EraseRepository();
    m_pGifGenerationRepository = new GifGenerationRepository();
    m_pInpaintingRepository = new InpaintingRepository();
}

FuncAreaRepository::~FuncAreaRepository() {
}

CompressionRepository *FuncAreaRepository::compressionRepository() const {
    return m_pCompressionRepository;
}

ConversionRepository *FuncAreaRepository::conversionRepository() const {
    return m_pConversionRepository;
}

CroppingRepository *FuncAreaRepository::croppingRepository() const {
    return m_pCroppingRepository;
}

EffectsRepository *FuncAreaRepository::effectsRepository() const {
    return m_pEffectsRepository;
}

EnhancementRepository *FuncAreaRepository::enhancementRepository() const {
    return m_pEnhancementRepository;
}

EraseRepository *FuncAreaRepository::eraseRepository() const {
    return m_pEraseRepository;
}

GifGenerationRepository *FuncAreaRepository::gifGenerationRepository() const {
    return m_pGifGenerationRepository;
}

InpaintingRepository *FuncAreaRepository::inpaintingRepository() const {
    return m_pInpaintingRepository;
}
