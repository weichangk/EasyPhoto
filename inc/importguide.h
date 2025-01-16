#pragma once
#include "globalview.h"
#include "widget/label.h"

#include <QMouseEvent>
#include <QDropEvent>
#include <QMimeData>

using namespace qtmaterialwidget;
using namespace qtmaterialcore;
using namespace qtmaterialfilter;

class ImportGuide : public QWidget {
    Q_OBJECT
public:
    explicit ImportGuide(QWidget *parent = nullptr);
    ~ImportGuide() override {
    }

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

private:
    void onLanguageChange();

private:
    LanguageFilter *m_pLanguageFilter = nullptr;
    QVBoxLayout *m_pMainLayout = nullptr;
    VectorLabel *m_pImportIconLab = nullptr;
    QLabel *m_pImportDecLab = nullptr;
    QWidget *m_pDividingLine = nullptr;
};