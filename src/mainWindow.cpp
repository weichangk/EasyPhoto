#include "mainwindow.h"
#include "qtreewidget.h"
#include "qstackedwidget.h"
#include "qtreewidget.h"
#include "acore/inc/alangmgr.h"
#include "awidget/inc/awidget.h"
#include "awidget/inc/ahboxlayout.h"
#include "awidget/inc/avboxlayout.h"
#include "awidget/inc/acombobox.h"
#include "awidget/inc/atextedit.h"
#include "awidget/inc/apushbutton.h"
#include "awidget/inc/athumbnail.h"
#include "awidget/inc/ashadoweffect.h"
#include "awidget/inc/aarrowwidget.h"
#include "agui/inc/atopbar.h"
#include "imagekit/inc/imagekitstartupview.h"
#include "imagekit/inc/imagekitstartupcontroller.h"
#include <QShortcut>

MainWindow::MainWindow(QWidget *parent)
    : ABaseWidget(parent)
{
    createUi();
    changeLanguage();
    sigConnect();
}

MainWindow::~MainWindow()
{
}

void MainWindow::changeLanguage()
{
    testTextEdit->setPlaceholderText(tr("Please enter your mobile phone number or email address"));
}

void MainWindow::sigConnect()
{
    connect(langCombox, &QComboBox::currentIndexChanged, this, &MainWindow::slotLangComboxIndexChanged);
    connect(m_topbar, &ATopbar::sigMin, this, [=](){
        showMinimized();
    });
    connect(m_topbar, &ATopbar::sigMax, this, [=](){
        showMaximized();
    });
    connect(m_topbar, &ATopbar::sigNormal, this, [=](){
        showNormal();
    });
    connect(m_topbar, &ATopbar::sigClose, this, [=](){
        close();
    });
}

void MainWindow::createUi()
{
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    setMinimumSize(1096, 680);

    //
    AVBoxLayout *mainLyt = new AVBoxLayout(this);
    mainLyt->setContentsMargins(0, 0, 0, 0);

    //
    AHBoxLayout *lrLyt = new AHBoxLayout();
    lrLyt->setContentsMargins(20, 20, 20, 20);

    //
    m_topbar = new ATopbar(this);
    // topbar->setStyleSheet("background-color:red;");

    //
    mainLyt->addWidget(m_topbar);
    mainLyt->addLayout(lrLyt);

    //
    createTree();

    //
    m_stackedWidget = new QStackedWidget(this);

    //
    lrLyt->addWidget(m_treeWidget);
    lrLyt->addWidget(m_stackedWidget, 1);


    //
    AWidget *rightWidget = new AWidget();
    rightWidget->setObjectName("rightWidget");
    m_stackedWidget->addWidget(rightWidget);
    m_stackedWidget->setCurrentIndex(0);

    //
    AVBoxLayout *rightWidgetLyt = new AVBoxLayout(rightWidget);

    //
    langCombox = new AComboBox(this);
    langCombox->addItem(tr("Chinens"));
    langCombox->addItem(tr("English"));
    rightWidgetLyt->addWidget(langCombox);

    //
    testTextEdit = new ATextEdit(rightWidget);
    testTextEdit->setFixedHeight(70);
    testTextEdit->setUseCustomTextCursor(true);
    testTextEdit->setCustomTextCursorColor(QColor("#2977FF"));
    rightWidgetLyt->addWidget(testTextEdit);

    //
    AHBoxLayout *testAPushButtonLyt = new AHBoxLayout();
    rightWidgetLyt->addLayout(testAPushButtonLyt);

    APushButton *testBtn1 = new APushButton(rightWidget);
    testBtn1->setCheckable(true);
    testBtn1->setText(tr("first button"));
    testBtn1->setToolTip(tr("first button"));
    testAPushButtonLyt->addWidget(testBtn1);
    APushButton *testBtn2 = new APushButton(rightWidget);
    testBtn2->setCheckable(true);
    testBtn2->setText(tr("second button"));
    testBtn2->setToolTip(tr("second button"));
    testAPushButtonLyt->addWidget(testBtn2);

    connect(testBtn1, &QPushButton::clicked, this, [=](){

        AArrowWidget* widget = new AArrowWidget(this);
        widget->resize(300, 150);
        widget->setTriangleDirection(1);
        widget->setTriangleX(150 - 14);
        widget->show();
    });
    connect(testBtn2, &QPushButton::clicked, this, [=](){
    });

    QPushButton *testBtn3 = new QPushButton(rightWidget);
    testBtn3->setCheckable(true);
    testBtn3->setText(tr("first button"));
    testAPushButtonLyt->addWidget(testBtn3);
    QPushButton *testBtn4 = new QPushButton(rightWidget);
    testBtn4->setCheckable(true);
    testBtn4->setText(tr("second button"));
    testAPushButtonLyt->addWidget(testBtn4);

    m_ImageKitStartupView = new ImageKitStartupView();
    m_ImageKitStartupController = new ImageKitStartupController(m_ImageKitStartupView);
    QPushButton *testBtn5 = new QPushButton(rightWidget);
    testBtn5->setCheckable(true);
    testBtn5->setText(tr("image kit"));
    testAPushButtonLyt->addWidget(testBtn5);
    connect(testBtn5, &QPushButton::clicked, this, [=](){
        m_ImageKitStartupController->show();
    });

    testAPushButtonLyt->addStretch();

    //
    AHBoxLayout *testAThumbnailLyt = new AHBoxLayout();
    rightWidgetLyt->addLayout(testAThumbnailLyt);

    AThumbnail *thum1 = new AThumbnail(this);
    thum1->setFixedSize(600, 300);
    thum1->setPixmap(QPixmap(":/res/image/green.jpg"));
    thum1->setRadiius(20);
    thum1->setHasBorder(true);
    testAThumbnailLyt->addWidget(thum1);

    //
    rightWidgetLyt->addStretch();

    enterShortcut = new QShortcut(Qt::Key_Return, this);
    enterShortcut->setContext(Qt::ApplicationShortcut);
    QObject::connect(enterShortcut, &QShortcut::activated, [&]() {
        qDebug() << "Enter key pressed!";
    });

    //
    auto shadow = new AShadowEffect(this);
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

void MainWindow::slotLangComboxIndexChanged(int index)
{
    switch (index)
    {
    case 0:
        ALangMgr::getInstance()->setLangLocale(ALangLocale::lang_locale_zh);
        break;
    case 1:
        ALangMgr::getInstance()->setLangLocale(ALangLocale::lang_locale_en);
        break;
    default:
        ALangMgr::getInstance()->setLangLocale(ALangLocale::lang_locale_zh);
        break;
    }
}
