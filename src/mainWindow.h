#pragma once
#include <QMainWindow>
#include <QListView>
#include <QStackedWidget>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    void createUi();

private:
    QListView *m_listView = nullptr;
    QStackedWidget *m_stackedWidget = nullptr;
};
