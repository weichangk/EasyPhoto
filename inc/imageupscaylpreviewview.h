#pragma once
#include <QWidget>

namespace imageupscayl {
class ImageUpscaylPreviewView : public QWidget {
    Q_OBJECT
public:
    explicit ImageUpscaylPreviewView(QWidget *parent = nullptr);
    ~ImageUpscaylPreviewView();

protected:
    void createUi();
    void sigConnect();

private:

private:

};
} // namespace imageupscayl