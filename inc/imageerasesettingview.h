#pragma once
#include <QWidget>

namespace imageerase {
class ImageEraseSettingView : public QWidget {
    Q_OBJECT
public:
    explicit ImageEraseSettingView(QWidget *parent = nullptr);
    ~ImageEraseSettingView();

protected:
    void createUi();
    void sigConnect();
};
} // namespace imageerase