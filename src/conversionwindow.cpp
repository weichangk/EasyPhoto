#include "inc/conversionwindow.h"
#include "inc/signals.h"
#include "inc/models.h"
#include "inc/settings.h"
#include "control/shadoweffect.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPainter>
#include <QPainterPath>

namespace imageconversion {
ConversionWindow::ConversionWindow(QWidget *parent) :
    QWidget(parent) {
    createUi();
    sigConnect();
}

ConversionWindow::~ConversionWindow() {
}

void ConversionWindow::changeData(QList<Data> datas) {
    m_ConversionListView->chageData(datas);
    m_AddGuideBtn->setVisible(m_ConversionListView->count() == 0);

    bool isAllChecked = datas.count() > 0;
    for (const auto &data : datas) {
        if (!data.is_checked) {
            isAllChecked = false;
            break;
        }
    }
    updateCheckAllBtnState(isAllChecked);
    updateBtnsEnabledByChangeData(datas);
}

void ConversionWindow::addFormatListWidgetItems(const QStringList items) {
    m_FormatPopup->addFormatListWidgetItems(items);
}

void ConversionWindow::changeConvToBtnText(const QString format) {
    m_ConvToBtn->setText(QString("%1%2").arg("转换为").arg(format.toUpper()));
}

void ConversionWindow::createUi() {
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setMinimumSize(800, 540);

    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    m_Topbar = new TopbarWidget(this);
    m_Topbar->setCloseBtnTopRight10Radius();
    mainLayout->addWidget(m_Topbar);

    auto topbarLayout = new QHBoxLayout(m_Topbar->contentWidget());
    topbarLayout->setContentsMargins(0, 0, 0, 0);
    topbarLayout->setSpacing(12);
    topbarLayout->addSpacing(12);
    auto logoLayout = new QHBoxLayout();
    logoLayout->setContentsMargins(0, 0, 0, 0);
    logoLayout->setSpacing(4);
    m_LogoLab = new QLabel(this);
    QPixmap logo(":/agui/res/image/conversion-logo-32.png");
    m_LogoLab->setPixmap(logo);
    logoLayout->addWidget(m_LogoLab);
    m_NameLab = new QLabel(this);
    m_NameLab->setObjectName("ConversionWindow_m_NameLab");
    m_NameLab->setText("图片格式转换");
    logoLayout->addWidget(m_NameLab);
    topbarLayout->addLayout(logoLayout);
    topbarLayout->addStretch();
    m_SetingBtn = new QPushButton(this);
    m_SetingBtn->setObjectName("OnlyIconButton");
    m_SetingBtn->setFixedSize(24, 24);
    m_SetingBtn->setIconSize(QSize(24, 24));
    m_SetingBtn->setIcon(QIcon(":/agui/res/image/setting-24.png"));
    topbarLayout->addWidget(m_SetingBtn);
    QWidget *topbarSplit = new QWidget(this);
    topbarSplit->setStyleSheet("background-color:#2F2F2F");
    topbarSplit->setFixedSize(1, 16);
    topbarLayout->addWidget(topbarSplit);
    topbarLayout->addSpacing(12);

    auto bodyLayout = new QVBoxLayout();
    bodyLayout->setContentsMargins(25, 0, 25, 0);

    auto convertListViewBG = new QWidget(this);
    convertListViewBG->setObjectName("ConversionWindow_convertListViewBG");
    bodyLayout->addWidget(convertListViewBG);

    auto convertListViewBGLayout = new QVBoxLayout(convertListViewBG);
    convertListViewBGLayout->setContentsMargins(0, 0, 0, 0);
    m_ConversionListView = new ConversionListView(this);
    convertListViewBGLayout->addWidget(m_ConversionListView);

    mainLayout->addLayout(bodyLayout);

    auto bottomBG = new QWidget(this);
    bottomBG->setFixedHeight(64);
    auto bottomLayout = new QHBoxLayout(bottomBG);
    bottomLayout->setContentsMargins(25, 0, 25, 0);
    bottomLayout->setSpacing(12);

    m_AddFileBtn = new QPushButton(this);
    m_AddFileBtn->setObjectName("FullBGButton_FS14");
    m_AddFileBtn->setFixedSize(80, 32);
    m_AddFileBtn->setText("导入");
    m_AddFileBtn->setIconSize(QSize(24, 24));
    m_AddFileBtn->setIcon(QIcon(":/agui/res/image/add-24.png"));
    bottomLayout->addWidget(m_AddFileBtn);

    m_DelFileBtn = new QPushButton(this);
    m_DelFileBtn->setObjectName("FullBGButton_FS14");
    m_DelFileBtn->setFixedSize(80, 32);
    m_DelFileBtn->setText("删除");
    m_DelFileBtn->setIconSize(QSize(24, 24));
    m_DelFileBtn->setIcon(QIcon(":/agui/res/image/delete-24.png"));
    bottomLayout->addWidget(m_DelFileBtn);

    m_CheckAllBtn = new QPushButton(this);
    m_CheckAllBtn->setObjectName("FullBGButton_FS14");
    m_CheckAllBtn->setFixedSize(80, 32);
    m_CheckAllBtn->setText("全选");
    m_CheckAllBtn->setIconSize(QSize(24, 24));
    bottomLayout->addWidget(m_CheckAllBtn);

    bottomLayout->addStretch();

    m_ConvToBtn = new QPushButton(this);
    m_ConvToBtn->setObjectName("FullBGButton_FS14");
    m_ConvToBtn->setFixedSize(136, 32);
    changeConvToBtnText(SETTINGS->conversionOutFormat());
    m_ConvToBtn->setIconSize(QSize(24, 24));
    m_ConvToBtn->setIcon(QIcon(":/agui/res/image/export-24.png"));
    // m_ConvToBtn->setLayoutDirection(Qt::RightToLeft);

    bottomLayout->addWidget(m_ConvToBtn);

    m_ConvAllBtn = new QPushButton(this);
    m_ConvAllBtn->setObjectName("FullBGButton_FS14");
    m_ConvAllBtn->setFixedSize(136, 32);
    m_ConvAllBtn->setText("开始转换");
    m_ConvAllBtn->setIconSize(QSize(24, 24));
    m_ConvAllBtn->setIcon(QIcon(":/agui/res/image/refresh-24.png"));
    bottomLayout->addWidget(m_ConvAllBtn);

    mainLayout->addWidget(bottomBG);

    auto shadow = new ShadowEffect(this);

    m_AddGuideBtn = new QPushButton(this);
    m_AddGuideBtn->setObjectName("ConversionWindow_m_AddGuideBtn");
    m_AddGuideBtn->setFixedSize(96 * 3, 96 * 2);
    m_AddGuideBtn->setIconSize(QSize(96, 96));
    m_AddGuideBtn->setIcon(QIcon(":/agui/res/image/image-file-add-96.png"));

    m_ConvertingWidget = new WidgetWithRotatingItem(QPixmap(":agui/res/image/loading-96.png"), this);
    m_ConvertingWidget->setFixedSize(96, 96);
    showConverting(false);

    m_FormatPopup = new ConversionFormatPopup(this);

    QList<Data> datas;
    updateBtnsEnabledByChangeData(datas);
    updateCheckAllBtnState(false);
}

void ConversionWindow::sigConnect() {
    connect(m_Topbar, &TopbarWidget::sigMin, this, [=]() { showMinimized(); });
    connect(m_Topbar, &TopbarWidget::sigMax, this, [=]() { showMaximized(); });
    connect(m_Topbar, &TopbarWidget::sigNormal, this, [=]() { showNormal(); });
    connect(m_Topbar, &TopbarWidget::sigClose, this, [=]() {
        close();
        emit ::SIGNALS->sigGotoFunc(ImageFunc::STARTUP);
    });
    connect(m_ConversionListView, &QListView::clicked, this, [=](const QModelIndex &index) {
        auto data = index.data(Qt::UserRole).value<Data>();
        QRect rc = m_ConversionListView->visualRect(index);
        int posx = m_ConversionListView->mapFromGlobal(QCursor::pos()).x();
        int posy = m_ConversionListView->mapFromGlobal(QCursor::pos()).y();
        QRect borderRect = rc.adjusted(1 + 8, 1 + 8, -1, -1);
        QRect delIconRect = QRect(borderRect.x() + borderRect.width() - 16 - 4, borderRect.y() + 4, 16, 16);
        if (posx >= delIconRect.x() && posx <= delIconRect.x() + delIconRect.width()
            && posy >= delIconRect.y() && posy <= delIconRect.y() + delIconRect.height()) {
            emit SIGNALS->sigDeleteFile(data.file_path);
        }
        auto checkedconRect = QRect(borderRect.x() + 4, borderRect.y() + 4, 16, 16);
        if (posx >= checkedconRect.x() && posx <= checkedconRect.x() + checkedconRect.width()
            && posy >= checkedconRect.y() && posy <= checkedconRect.y() + checkedconRect.height()) {
            emit SIGNALS->sigSwitchChecked(data.file_path, data.is_checked);
        }
    });
    connect(m_AddFileBtn, &QPushButton::clicked, this, [=]() {
        emit SIGNALS->sigOpenFileDialog(this);
    });
    connect(m_AddGuideBtn, &QPushButton::clicked, this, [=]() {
        emit SIGNALS->sigOpenFileDialog(this);
    });
    connect(m_DelFileBtn, &QPushButton::clicked, this, [=]() {
        emit SIGNALS->sigDeleteByChecked();
    });
    connect(m_CheckAllBtn, &QPushButton::clicked, this, [=]() {
        bool oldChecked = "true" == m_CheckAllBtn->property("is-checked").toString();
        bool newChecked = !oldChecked;
        emit SIGNALS->sigCheckedAll(newChecked);
        updateCheckAllBtnState(newChecked);
    });
    connect(m_ConvAllBtn, &QPushButton::clicked, this, [=]() {
        emit SIGNALS->sigStatus(Status::START);
        convStatus(Status::START);
    });
    connect(m_ConvToBtn, &QPushButton::clicked, this, &ConversionWindow::formatPopup);
    connect(SIGNALS, &Signals::sigStatus2View, this, &ConversionWindow::convStatus);
}

void ConversionWindow::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    // 背景色透明
    painter.fillRect(this->rect(), QColor(0, 0, 0, 1));

    // 背景图
    QPixmap pixmapTemp = QPixmap(this->rect().size());
    pixmapTemp.fill(QColor("#181818"));
    pixmapTemp.setDevicePixelRatio(1);

    // 背景图圆角裁剪
    QPainterPath path;
    path.addRoundedRect(this->rect(), 10, 10);
    painter.setClipPath(path);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.drawPixmap(this->rect(), pixmapTemp);

    // 边框
    QPen pen(QColor("#402F38"));
    pen.setWidth(1);
    painter.setPen(pen);
    auto borderRect = this->rect(); //.adjusted(1, 1, -1, -1);
    painter.drawRoundedRect(borderRect, 10, 10);
}

void ConversionWindow::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    m_AddGuideBtn->setGeometry((width() - m_AddGuideBtn->width()) / 2, (height() - m_AddGuideBtn->height()) / 2, m_AddGuideBtn->width(), m_AddGuideBtn->height());
    m_ConvertingWidget->setGeometry((width() - m_ConvertingWidget->width()) / 2, (height() - m_ConvertingWidget->height()) / 2, m_ConvertingWidget->width(), m_ConvertingWidget->height());
}

void ConversionWindow::updateCheckAllBtnState(bool checked) {
    m_CheckAllBtn->setProperty("is-checked", checked ? "true" : "false");
    m_CheckAllBtn->setIcon(QIcon(checked ? ":/agui/res/image/checked-24.png" : ":/agui/res/image/unchecked-24.png"));
}

void ConversionWindow::updateBtnsEnabledByChangeData(QList<Data> datas) {
    auto allUnchecked = [](const QList<Data> &datas) {
        return std::all_of(datas.begin(), datas.end(), [](const Data &cd) {
            return cd.is_checked == false;
        });
    };

    bool isEnabled = datas.count() > 0;
    m_CheckAllBtn->setEnabled(isEnabled);
    m_ConvToBtn->setEnabled(isEnabled);

    isEnabled = !allUnchecked(datas);
    m_DelFileBtn->setEnabled(isEnabled);
    m_ConvAllBtn->setEnabled(isEnabled);
}

void ConversionWindow::formatPopup() {
    auto btnPos = m_ConvToBtn->mapToGlobal(QPoint(0, 0));
    auto newPos = btnPos - QPoint(m_FormatPopup->width() - m_ConvToBtn->width(), m_FormatPopup->height() + 8);
    m_FormatPopup->move(newPos);
    m_FormatPopup->show();
}

void ConversionWindow::showConverting(bool isShow) {
    m_ConvertingWidget->setVisible(isShow);
    if (isShow) {
        m_ConvertingWidget->start();
    } else {
        m_ConvertingWidget->stop();
    }
}

void ConversionWindow::convStatus(Status state) {
    switch (state) {
    case Status::NONE:
        break;
    case Status::START:
        startConv();
        break;
    case Status::FINISHED:
        finishedConv();
        break;
    case Status::CANCEL:
        cancelConv();
        break;
    }
}

void ConversionWindow::startConv() {
    showConverting(true);
}

void ConversionWindow::finishedConv() {
    showConverting(false);
}

void ConversionWindow::cancelConv() {
}

ConversionFormatPopup::ConversionFormatPopup(QWidget *parent) :
    QWidget(parent) {
    createUi();
    sigConnect();
}

void ConversionFormatPopup::addFormatListWidgetItems(const QStringList items) {
    m_FormatListWidget->addItems(items);
}

void ConversionFormatPopup::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    // 背景色透明
    painter.fillRect(this->rect(), QColor(0, 0, 0, 1));

    // 背景图
    QPixmap pixmapTemp = QPixmap(this->rect().size());
    pixmapTemp.fill(QColor("#222222"));
    pixmapTemp.setDevicePixelRatio(1);

    // 背景图圆角裁剪
    QPainterPath path;
    path.addRoundedRect(this->rect(), 10, 10);
    painter.setClipPath(path);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.drawPixmap(this->rect(), pixmapTemp);

    // 边框
    QPen pen(QColor("#313131"));
    pen.setWidth(1);
    painter.setPen(pen);
    auto borderRect = this->rect(); //.adjusted(1, 1, -1, -1);
    painter.drawRoundedRect(borderRect, 10, 10);
}

void ConversionFormatPopup::createUi() {
    setObjectName("ConversionFormatPopup");
    setWindowFlags(Qt::FramelessWindowHint | Qt::Popup | Qt::NoDropShadowWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setFixedSize(425, 260);
    auto mainLayout = new QHBoxLayout(this);
    mainLayout->setContentsMargins(12, 12, 12, 12);
    m_FormatListWidget = new QListWidget(this);
    mainLayout->addWidget(m_FormatListWidget, 1);
    auto *delegate = new ConversionFormatListDelegate(this);
    m_FormatListWidget->setItemDelegate(delegate);
    m_FormatListWidget->viewport()->installEventFilter(delegate);
    m_FormatListWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_FormatListWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_FormatListWidget->setAttribute(Qt::WA_StyledBackground);
    m_FormatListWidget->setResizeMode(QListView::Adjust);
    m_FormatListWidget->setViewMode(QListView::IconMode);
    m_FormatListWidget->setSelectionMode(QAbstractItemView::NoSelection);
    m_FormatListWidget->setMouseTracking(true);
    m_FormatListWidget->setStyleSheet("border:0px; background-color:transparent;");
    m_FormatListWidget->setSpacing(0);
}

void ConversionFormatPopup::sigConnect() {
    connect(m_FormatListWidget, &QListWidget::itemClicked, this, &ConversionFormatPopup::formatItemClicked);
}

void ConversionFormatPopup::formatItemClicked(QListWidgetItem *item) {
    QString fmt = item->data(Qt::DisplayRole).toString();
    emit SIGNALS->sigChangeFormat(fmt);
    close();
}

ConversionFormatListDelegate::ConversionFormatListDelegate(QObject *parent) :
    QStyledItemDelegate(parent) {
}

void ConversionFormatListDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setRenderHint(QPainter::SmoothPixmapTransform);

    auto data = index.data(Qt::DisplayRole).toString();
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::NoBrush);

    QRect rc = option.rect;
    bool hover = option.state & QStyle::State_MouseOver;
    auto borderRect = rc.adjusted(1, 1, -1 - 10, -1 - 10);

    painter->setBrush(Qt::NoBrush);
    QPen pen(QColor("#404040"));
    pen.setWidth(1);
    painter->setPen(pen);
    painter->drawRoundedRect(borderRect, 18, 18);
    if (hover) {
        pen.setColor(QColor("#4A4A4A"));
        painter->setPen(pen);
        painter->drawRoundedRect(borderRect, 18, 18);
        painter->setBrush(QColor(50, 50, 50, 0.75 * 255));
        painter->drawRoundedRect(borderRect, 18, 18);
        painter->setBrush(Qt::NoBrush);
    }
    painter->setPen(Qt::NoPen);

    pen.setColor(QColor("#575859"));
    painter->setPen(pen);
    QFont font = painter->font();
    font.setPointSizeF(11);
    painter->setFont(font);
    auto nameRect = QRect(borderRect.x(), borderRect.y() + 6, borderRect.width(), 24);
    painter->drawText(nameRect, Qt::AlignHCenter, data);
    painter->setPen(Qt::NoPen);
}

QSize ConversionFormatListDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {
    return QSize(80, 46);
}
} // namespace imageconversion