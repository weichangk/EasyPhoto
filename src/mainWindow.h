#pragma once
#include <QWidget>
#include <QTreeWidget>
#include <QStackedWidget>

class MainWindow : public QWidget {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    void createUi();
    void createTree();
private:

    QTreeWidget *m_treeWidget = nullptr;
    QStackedWidget *m_stackedWidget = nullptr;
};
