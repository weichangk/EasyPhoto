/*
 * @Author: weick
 * @Date: 2023-12-09 23:45:45
 * @Last Modified by: weick
 * @Last Modified time: 2024-07-06 16:36:08
 */

#pragma once
#include "../acore/inc/asinglton.h"
#include "models.h"
#include <QWidget>
#include <QPoint>

class Signals : public QObject, public ASinglton<Signals> {
    Q_OBJECT
public:
Q_SIGNALS:
    void sigGotoFunc(ImageFunc func);
};

namespace imageconversion {
class Signals : public QObject, public ASinglton<Signals> {
    Q_OBJECT
public:
Q_SIGNALS:
    void sigOpenFileDialog(QWidget *parent = 0);
    void sigAddFile();
    void sigDeleteFile(const QString filePath);
    void sigDeleteByChecked();
    void sigStatus(Status state);
    void sigStatus2View(Status state);
    void sigSwitchChecked(const QString filePath, const bool checked);
    void sigCheckedAll(const bool checked);
    void sigChangeFormat(const QString format);
};
} // namespace imageconversion

namespace imagecompression {
class Signals : public QObject, public ASinglton<Signals> {
    Q_OBJECT
public:
Q_SIGNALS:
    void sigOpenFileDialog(QWidget *parent = 0);
    void sigAddFile();
    void sigDeleteFile(const QString filePath);
    void sigDeleteByChecked();
    void sigStatus(Status state);
    void sigStatus2View(Status state);
    void sigSwitchChecked(const QString filePath, const bool checked);
    void sigCheckedAll(const bool checked);
    void sigChangeFormat(const QString format);
};
} // namespace imagecompression

namespace imageedit {
class Signals : public QObject, public ASinglton<Signals> {
    Q_OBJECT
public:
Q_SIGNALS:
    void sigWindowMove();
    void sigOpenFileDialog(QWidget *parent = nullptr);
    void sigDeleteFile(const QString filePath);
    void sigClickedFile(const QString filePath);
    void sigDeleteAll();
    void sigStatus(Status state);
    void sigListItemDataSelected(Data *data);
    void sigDataUpdate(Data data);
    void sigSelectRectPreview2Setting(const QRect &rect);
    void sigSelectRectSetting2Preview(const QRect &rect);
    void sigEqualRatioCropSetting2Preview(bool);

    void sigRotateAngleSetting2Preview(int);

    void sigLuminanceSetting2Preview(int);
    void sigContrastSetting2Preview(int);
    void sigSaturationSetting2Preview(int);
    void sigEffectResetSetting2Preview(int, int, int);
};
} // namespace image2gif

namespace image2gif {
class Signals : public QObject, public ASinglton<Signals> {
    Q_OBJECT
public:
Q_SIGNALS:
    void sigWindowMove();
    void sigOpenFileDialog(QWidget *parent = nullptr);
    void sigDeleteFile(const QString filePath);
    void sigClickedFile(const QString filePath);
    void sigDeleteAll();
    void sigStatus(Status state);
    void sigListItemDataSelected(Data *data);
    void sigListItemBeforeOrAfterAdd(int index, bool isBefore, QWidget *parent = nullptr);
    void sigListItemSwapedDatas(const QList<Data> &datas);
    void sigExportStart();
    void sigExportEnd(bool state, const QString &filePath, const QString &error);
    void sigExportProgress(int progress);
    void sigPreviewStart();
    void sigPreviewEnd(bool state, const QString &filePath, const QString &error);
};
} // namespace image2gif

namespace imageerase {
class Signals : public QObject, public ASinglton<Signals> {
    Q_OBJECT
public:
Q_SIGNALS:
    void sigWindowMove();
    void sigOpenFileDialog(QWidget *parent = nullptr);
    void sigDeleteFile(const QString filePath);
    void sigClickedFile(const QString filePath);
    void sigDeleteAll();
    void sigStatus(Status state);
    void sigListItemDataSelected(Data *data);
};
} // namespace imageerase

namespace imageenhancement {
class Signals : public QObject, public ASinglton<Signals> {
    Q_OBJECT
public:
Q_SIGNALS:
    void sigWindowMove();
    void sigOpenFileDialog(QWidget *parent = nullptr);
    void sigDeleteFile(const QString filePath);
    void sigClickedFile(const QString filePath);
    void sigDeleteAll();
    void sigStatus(Status state);
    void sigListItemDataSelected(Data *data);
};
} // namespace imageenhancement