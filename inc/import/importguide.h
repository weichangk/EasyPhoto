#pragma once
#include "globalview.h"
#include "widget/button.h"

#include <QMouseEvent>
#include <QDropEvent>
#include <QMimeData>

using namespace qtmaterialwidget;
using namespace qtmaterialcore;
using namespace qtmaterialfilter;

class ImportGuide : public QWidget {
    Q_OBJECT
public:
    explicit ImportGuide(QWidget *parent = nullptr, const QString &filter = "All Files (*)");
    ~ImportGuide() override {
    }
    
    void setIconPixmapPath(const QString &path);
    void setTitle(const QString &title);
    void setDec(const QString &dec);
    void setImportBtnText(const QString &text);

Q_SIGNALS:
    void sigImportFile(QStringList);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;

private:
    void createUi();
    void connectSig();
    QWidget *createDividingLine();
    void getAllFilesInDirectory(const QString &dirPath, QList<QString> &files);
    void openFileDialog();
    QStringList extractExtensions(const QString &filter);

private:
    void onLanguageChange();

private:
    QString m_strFilter;

    LanguageFilter *m_pLanguageFilter = nullptr;
    QVBoxLayout *m_pMainLayout = nullptr;
    IconButton *m_pIconBtn = nullptr;
    QLabel *m_pTitleLab = nullptr;
    QLabel *m_pDecLab = nullptr;
    HorIconTextButton *m_pImportBtn = nullptr;
    QWidget *m_pDividingLine = nullptr;
};