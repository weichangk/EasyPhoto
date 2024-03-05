/*
 * @Author: weick
 * @Date: 2024-03-05 22:54:25
 * @Last Modified by: weick
 * @Last Modified time: 2024-03-05 23:08:34
 */

#pragma once
#include <QObject>
#include "models.h"

class CompressProtocal : public QObject {
    Q_OBJECT
public:
    virtual bool compressable(const QString &preferredSuffix) = 0;
    virtual CompressResult compress(const QString &src, const QString &dst, const CompressParam &params) = 0;
};

class CompressManager : public CompressProtocal {
    Q_OBJECT
public:
    static CompressManager &instance();
    CompressManager();
    bool compressable(const QString &preferredSuffix) override;
    CompressResult compress(const QString &src, const QString &dst, const CompressParam &params) override;

private:
    void init();
    CompressResult doCompress(const QString &src, const QString &dst, const CompressParam &params);

private:
    std::vector<CompressProtocal *> m_CompressProtocals;
};
