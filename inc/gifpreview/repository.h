#pragma once
#include "globalpresenter.h"
#include "mvp/repository.h"

using namespace QtmMvp;

class GifPreviewRepository : public Repository {
    public:
        explicit GifPreviewRepository();
        ~GifPreviewRepository();

    };