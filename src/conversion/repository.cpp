#include "conversion/repository.h"

ConversionRepository::ConversionRepository() {
}

ConversionRepository::~ConversionRepository() {
}

QList<Data> ConversionRepository::datas() {
    return m_datas;
}

void ConversionRepository::appendData(QList<Data> datas) {
    m_datas.append(datas);
}