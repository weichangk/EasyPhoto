#pragma once
#include "globalpresenter.h"
#include "mvp/repository.h"

using namespace QtmMvp;

class DownloaderRepository : public Repository {
public:
    explicit DownloaderRepository();
    ~DownloaderRepository();
};