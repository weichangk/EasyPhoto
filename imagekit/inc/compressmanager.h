/*
 * @Author: weick
 * @Date: 2024-03-05 22:54:25
 * @Last Modified by: weick
 * @Last Modified time: 2024-03-24 20:49:46
 */

#pragma once
#include <QObject>
#include "models.h"

namespace imagecompression {
class CompressProtocal : public QObject {
    Q_OBJECT
public:
    virtual bool compressable(const QString &preferredSuffix) = 0;
    virtual Result compress(const QString &src, const QString &dst, const Param &params) = 0;
};

class CompressManager {
public:
    static CompressManager &instance();
    CompressManager();
    Result doCompress(const QString &src, const QString &dst, const Param &params);

private:
    void init();

private:
    std::vector<CompressProtocal *> m_CompressProtocals;
};

class GUEETZLIProtocal : public CompressProtocal {
    Q_OBJECT
public:
    bool compressable(const QString &preferredSuffix) override;
    Result compress(const QString &src, const QString &dst, const Param &params) override;
};

class CJPEGProtocal : public CompressProtocal {
    Q_OBJECT
public:
    bool compressable(const QString &preferredSuffix) override;
    Result compress(const QString &src, const QString &dst, const Param &params) override;

private:
    QString toBitmap(const QString &src);
};

class PNGQUANTProtocal : public CompressProtocal {
    Q_OBJECT
public:
    bool compressable(const QString &preferredSuffix) override;
    Result compress(const QString &src, const QString &dst, const Param &params) override;
};

class OPTIPNGProtocal : public CompressProtocal {
    Q_OBJECT
public:
    bool compressable(const QString &preferredSuffix) override;
    Result compress(const QString &src, const QString &dst, const Param &params) override;
};

class CWEBPProtocal : public CompressProtocal {
    Q_OBJECT
public:
    bool compressable(const QString &preferredSuffix) override;
    Result compress(const QString &src, const QString &dst, const Param &params) override;
};

class GIFSICLEProtocal : public CompressProtocal {
    Q_OBJECT
public:
    bool compressable(const QString &preferredSuffix) override;
    Result compress(const QString &src, const QString &dst, const Param &params) override;
};
} // namespace imagecompression