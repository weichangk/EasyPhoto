#include "globalview.h"
#include "mvp/view.h"
#include "widget/button.h"

#include <QMovie>

using namespace QtmWidget;

class GifViewer : public QWidget {
    Q_OBJECT
public:
    explicit GifViewer(QWidget *parent = nullptr);
    ~GifViewer() override {
    }

protected:
    void resizeEvent(QResizeEvent *event) override;
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;

private Q_SLOTS:
    void onExitBtnClicked();
    void onPlayBtnClicked();
    
private:
    void createUi();
    void connectSig();

    void start();
    void stop();
    void preview(const QString &path);
    void exit();


private:
    IconButton *m_pExitBtn = nullptr;
    IconButton *m_pPlayBtn = nullptr;
    QLabel *m_pGifLabel = nullptr;
    QMovie *m_pGifMovie = nullptr;
};