#pragma once
#include "globalview.h"
#include "widget/button.h"

#include <QMovie>

using namespace qtmaterialwidget;

class GifPreviewView : public QWidget {
    Q_OBJECT
public:
    explicit GifPreviewView(QWidget *parent = nullptr);
    ~GifPreviewView() override {
    }

private:
    void createUi();
    void connectSig();

private:
    VectorButton *m_pExitBtn = nullptr;
    VectorButton *m_pPlayBtn = nullptr;
    QMovie *m_pMovie = nullptr;
};