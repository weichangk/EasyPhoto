#include "mainwindow.h"
#include <QHBoxLayout>
#include <QTreeWidgetItem>

MainWindow::MainWindow(QWidget* parent)
    : QWidget(parent)
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
    createTree();

    //
    m_stackedWidget = new QStackedWidget(this);

    //
    QHBoxLayout *mainLyt = new QHBoxLayout(this);
    mainLyt->setContentsMargins(20, 20, 20, 20);
    mainLyt->addWidget(m_treeWidget);
    mainLyt->addWidget(m_stackedWidget, 1);
}

void MainWindow::createTree()
{
    m_treeWidget = new QTreeWidget(this);
    m_treeWidget->setHeaderHidden(true);
    m_treeWidget->setFixedWidth(170);

    QTreeWidgetItem *home = new QTreeWidgetItem(m_treeWidget);
    home->setText(0, tr("Home"));

    // layouts
    QTreeWidgetItem *layoutsitem = new QTreeWidgetItem(m_treeWidget);
    layoutsitem->setText(0, tr("Layouts"));

    QTreeWidgetItem *layouts_layouts = new QTreeWidgetItem(layoutsitem);
    layouts_layouts->setText(0, tr("Ver Hor Grid Form"));

    QTreeWidgetItem *layouts_splitter = new QTreeWidgetItem(layoutsitem);
    layouts_splitter->setText(0, tr("Splitter"));

    QTreeWidgetItem *layouts_flow_layout = new QTreeWidgetItem(layoutsitem);
    layouts_flow_layout->setText(0, tr("CustomFlowLayout"));

    // containers
    QTreeWidgetItem *containeritem = new QTreeWidgetItem(m_treeWidget);
    containeritem->setText(0, tr("Containers"));

    QTreeWidgetItem *container_scrollarea = new QTreeWidgetItem(containeritem);
    container_scrollarea->setText(0, tr("ScrollArea"));

    QTreeWidgetItem *container_dock = new QTreeWidgetItem(containeritem);
    container_dock->setText(0, tr("DockWidget"));
    QTreeWidgetItem *dockwidget_add = new QTreeWidgetItem(container_dock);
    dockwidget_add->setText(0, tr("AddDockWidget"));
    QTreeWidgetItem *dockwidget_split = new QTreeWidgetItem(container_dock);
    dockwidget_split->setText(0, tr("SplitDockWidget"));
    QTreeWidgetItem *dockwidget_tabify = new QTreeWidgetItem(container_dock);
    dockwidget_tabify->setText(0, tr("TabifyDockWidget"));

    QTreeWidgetItem *container_stack = new QTreeWidgetItem(containeritem);
    container_stack->setText(0, tr("StackedWidget"));

    // properties
    QTreeWidgetItem *propertiesitem = new QTreeWidgetItem(m_treeWidget);
    propertiesitem->setText(0, tr("Properties"));
    QTreeWidgetItem *properties_sizetest = new QTreeWidgetItem(propertiesitem);
    properties_sizetest->setText(0, tr("SizeTest"));

    // itemviews
    QTreeWidgetItem *itemviewsitem = new QTreeWidgetItem(m_treeWidget);
    itemviewsitem->setText(0, tr("itemviews"));
}
