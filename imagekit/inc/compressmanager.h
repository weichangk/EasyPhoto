/*
 * @Author: weick
 * @Date: 2024-03-05 22:54:25
 * @Last Modified by: weick
 * @Last Modified time: 2024-03-23 23:14:17
 */

#pragma once
#include <QObject>
#include "models.h"

class CompressProtocal : public QObject {
    Q_OBJECT
public:
    virtual bool compressable(const QString &preferredSuffix) = 0;
    virtual imagecompression::Result compress(const QString &src, const QString &dst, const imagecompression::Param &params) = 0;
};

class CompressManager {
public:
    static CompressManager &instance();
    CompressManager();
    imagecompression::Result doCompress(const QString &src, const QString &dst, const imagecompression::Param &params);

private:
    void init();

private:
    std::vector<CompressProtocal *> m_CompressProtocals;
};

class GUEETZLIProtocal : public CompressProtocal {
    Q_OBJECT
public:
    bool compressable(const QString &preferredSuffix) override;
    imagecompression::Result compress(const QString &src, const QString &dst, const imagecompression::Param &params) override;
};

class CJPEGProtocal : public CompressProtocal {
    Q_OBJECT
public:
    bool compressable(const QString &preferredSuffix) override;
    imagecompression::Result compress(const QString &src, const QString &dst, const imagecompression::Param &params) override;

private:
    QString toBitmap(const QString &src);
};


class PNGQUANTProtocal : public CompressProtocal {
    Q_OBJECT
public:
    bool compressable(const QString &preferredSuffix) override;
    imagecompression::Result compress(const QString &src, const QString &dst, const imagecompression::Param &params) override;
};

class OPTIPNGProtocal : public CompressProtocal {
    Q_OBJECT
public:
    bool compressable(const QString &preferredSuffix) override;
    imagecompression::Result compress(const QString &src, const QString &dst, const imagecompression::Param &params) override;
};

class CWEBPProtocal : public CompressProtocal {
    Q_OBJECT
public:
    bool compressable(const QString &preferredSuffix) override;
    imagecompression::Result compress(const QString &src, const QString &dst, const imagecompression::Param &params) override;
};

class GIFSICLEProtocal : public CompressProtocal {
    Q_OBJECT
public:
    bool compressable(const QString &preferredSuffix) override;
    imagecompression::Result compress(const QString &src, const QString &dst, const imagecompression::Param &params) override;
};
