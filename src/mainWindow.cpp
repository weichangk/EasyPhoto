#include "mainwindow.h"
#include <QStringListModel>
#include <QStringList>
#include <QHBoxLayout>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    createUi();
}

MainWindow::~MainWindow()
{
}

void MainWindow::createUi()
{
    setMinimumSize(1096, 680);

    //
    m_listView = new QListView(this);
    m_listView->setFixedWidth(170);
    QStringListModel *listModel = new QStringListModel();
    QStringList data;
    data << "控件使用" << "样式效果" << "Qt对象模型" << "Item 4" << "Item 5";
    listModel->setStringList(data);
    m_listView->setModel(listModel);
    m_listView->setViewMode(QListView::ListMode);

    //
    m_stackedWidget = new QStackedWidget(this);

    //
    QHBoxLayout *mainLyt = new QHBoxLayout(this);
    mainLyt->addWidget(m_listView);
    mainLyt->addWidget(m_stackedWidget, 1);
}
