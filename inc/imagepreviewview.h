#pragma once
#include "globalview.h"
#include "widget/button.h"

#include <QMovie>

using namespace qtmaterialwidget;

class ImagePreviewView : public QWidget {
    Q_OBJECT
public:
    explicit ImagePreviewView(QWidget *parent = nullptr);
    ~ImagePreviewView() override {
    }

private:
    void createUi();
    void connectSig();

private:
    VectorButton *m_pExitBtn = nullptr;
    QLabel *m_pImageLab = nullptr;
};