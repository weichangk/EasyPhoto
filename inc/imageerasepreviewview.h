#pragma once
#include "inc/models.h"

#include <QWidget>

namespace imageerase {
class ImageErasePreviewView : public QWidget {
    Q_OBJECT
public:
    explicit ImageErasePreviewView(QWidget *parent = nullptr);
    ~ImageErasePreviewView();

protected:
    void createUi();
    void sigConnect();

private:

private:

};
} // namespace imageedit