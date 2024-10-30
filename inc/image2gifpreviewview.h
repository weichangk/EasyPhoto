#pragma once
#include "inc/models.h"
#include "component/previewwidget.h"

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QMovie>

namespace image2gif {
class Image2GifPreviewView : public QWidget {
    Q_OBJECT
public:
    explicit Image2GifPreviewView(QWidget *parent = nullptr);
    ~Image2GifPreviewView();

protected:
    void createUi();
    void sigConnect();
    bool eventFilter(QObject *watched, QEvent *event) override;

private:
    void preViewDataSelected(Data *data);
    void loadSelectedPixmap(const QString &path);
    void updateSelectedPixmapSize();
    void slotPreviewButtonClicked();
    void slotPreviewEnd(bool state, const QString &filePath, const QString &error);
    void slotPreviewMovieFinished();
private:
    Data *data_ = nullptr;

    QWidget *preview_widget_ = nullptr;
    QLabel *preview_pixmap_label_ = nullptr;
    QPixmap preview_pixmap_;
    QMovie *preview_movie_ = nullptr;
    PreviewWidget *preview_button_ = nullptr;
};
} // namespace image2gif