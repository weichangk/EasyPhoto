#include "gifmk/repository.h"

GifMkRepository::GifMkRepository() {
    m_pImportListRepository = new ImportListRepository();
}

GifMkRepository::~GifMkRepository() {
}

ImportListRepository *GifMkRepository::getImportListRepository() {
    return m_pImportListRepository;
}