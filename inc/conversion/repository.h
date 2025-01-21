#pragma once
#include "globalpresenter.h"
#include "model.h"
#include "mvp/repository.h"

using namespace qtmaterialmvp;

class ConversionRepository : public Repository {
public:
    explicit ConversionRepository();
    ~ConversionRepository();
    QList<Data> datas();
    void appendData(QList<Data> datas);

private:
    QList<Data> m_datas;
};