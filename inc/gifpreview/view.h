#pragma once
#include "globalview.h"
#include "mvp/view.h"
#include "widget/button.h"

#include <QMovie>

using namespace qtmaterialmvp;
using namespace qtmaterialwidget;

class GifPreviewView : public QWidget, public View {
    Q_OBJECT
public:
    explicit GifPreviewView(QWidget *parent = nullptr);
    ~GifPreviewView() override {
    }

protected:
    void resizeEvent(QResizeEvent *event) override;
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;

private:
    void createUi();
    void connectSig();

    void start();
    void stop();
    void preview(const QString &path);
    void exit();

private Q_SLOTS:
    void onExitBtnClicked();
    void onPlayBtnClicked();

private:
    IconButton *m_pExitBtn = nullptr;
    IconButton *m_pPlayBtn = nullptr;
    QLabel *m_pGifLabel = nullptr;
    QMovie *m_pGifMovie = nullptr;
};