#pragma once
#include <QWidget>

class MainWindow : public QWidget {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void createUi();
    void sigConnect();
};
