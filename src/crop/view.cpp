#include "crop/view.h"
#include "crop/presenter.h"
#include "settings.h"
#include "core/theme.h"
#include "core/painter.h"

#include <QButtonGroup>
#include <QPainter>
#include <QFontMetricsF>

static QMap<ECropAspectType, ImageWorkspace::CropAspectRatioMode> CropAspectRatioMode = {
    {ECropAspectType_Original, ImageWorkspace::CropAspectOriginal},
    {ECropAspectType_Custom, ImageWorkspace::CropAspectFree},
    {ECropAspectType_1_1, ImageWorkspace::CropAspectSquare},
    {ECropAspectType_16_9, ImageWorkspace::CropAspect16_9},
    {ECropAspectType_9_16, ImageWorkspace::CropAspect9_16},
    {ECropAspectType_4_3, ImageWorkspace::CropAspect4_3},
    {ECropAspectType_3_4, ImageWorkspace::CropAspect3_4},
    {ECropAspectType_3_2, ImageWorkspace::CropAspect3_2},
    {ECropAspectType_2_3, ImageWorkspace::CropAspect2_3},
};

static QMap<ECropResizeType, QSize> CropAspectResizeMode = {
    {ECropResizeType_Original, QSize(0, 0)},
    {ECropResizeType_Custom, QSize(0, 0)},
    {ECropResizeType_1080_1080, QSize(1080, 1080)},
    {ECropResizeType_1080_1920, QSize(1080, 1920)},
    {ECropResizeType_1200_630, QSize(1200, 630)},
    {ECropResizeType_851_315, QSize(851, 315)},
    {ECropResizeType_1200_675, QSize(1200, 675)},
    {ECropResizeType_1500_500, QSize(1500, 500)},
    {ECropResizeType_1280_720, QSize(1280, 720)},
    {ECropResizeType_2000_2000, QSize(2000, 2000)},
    {ECropResizeType_1600_1600, QSize(1600, 1600)},
    {ECropResizeType_2048_2048, QSize(2048, 2048)},
    {ECropResizeType_1000_1500, QSize(1000, 1500)},
    {ECropResizeType_1920_1080, QSize(1920, 1080)},
};  

QList<SCropAspectData> getCropAspectFormatDatas() {
    QList<SCropAspectData> datas;
    SCropAspectData data;

    data.type = ECropAspectType_Original;
    data.name = "Original";
    data.thumbnail = QPixmap(QString(":/QtmImg/img/%1/v165/icon20_crop_original.svg").arg(QtmCore::Theme::currentTheme())).copy(0, 0, 20, 20);
    datas.append(data);

    data.type = ECropAspectType_Custom;
    data.name = "Custom";
    data.thumbnail = QPixmap(QString(":/QtmImg/img/%1/v165/icon20_crop_custom.svg").arg(QtmCore::Theme::currentTheme())).copy(0, 0, 20, 20);
    datas.append(data);

    data.type = ECropAspectType_1_1;
    data.name = "1:1";
    data.thumbnail = QPixmap(QString(":/QtmImg/img/%1/v165/icon20_crop_1_1.svg").arg(QtmCore::Theme::currentTheme())).copy(0, 0, 20, 20);
    datas.append(data);

    data.type = ECropAspectType_16_9;
    data.name = "16:9";
    data.thumbnail = QPixmap(QString(":/QtmImg/img/%1/v165/icon20_crop_16_9.svg").arg(QtmCore::Theme::currentTheme())).copy(0, 0, 20, 20);
    datas.append(data);

    data.type = ECropAspectType_9_16;
    data.name = "9:16";
    data.thumbnail = QPixmap(QString(":/QtmImg/img/%1/v165/icon20_crop_9_16.svg").arg(QtmCore::Theme::currentTheme())).copy(0, 0, 20, 20);
    datas.append(data);

    data.type = ECropAspectType_4_3;
    data.name = "4:3";
    data.thumbnail = QPixmap(QString(":/QtmImg/img/%1/v165/icon20_crop_4_3.svg").arg(QtmCore::Theme::currentTheme())).copy(0, 0, 20, 20);
    datas.append(data);

    data.type = ECropAspectType_3_4;
    data.name = "3:4";
    data.thumbnail = QPixmap(QString(":/QtmImg/img/%1/v165/icon20_crop_3_4.svg").arg(QtmCore::Theme::currentTheme())).copy(0, 0, 20, 20);
    datas.append(data);

    data.type = ECropAspectType_3_2;
    data.name = "3:2";
    data.thumbnail = QPixmap(QString(":/QtmImg/img/%1/v165/icon20_crop_3_2.svg").arg(QtmCore::Theme::currentTheme())).copy(0, 0, 20, 20);
    datas.append(data);

    data.type = ECropAspectType_2_3;
    data.name = "2:3";
    data.thumbnail = QPixmap(QString(":/QtmImg/img/%1/v165/icon20_crop_2_3.svg").arg(QtmCore::Theme::currentTheme())).copy(0, 0, 20, 20);
    datas.append(data);

    return datas;
}

QList<SCropResizeData> getCropResizeFormatDatas() {
    QList<SCropResizeData> datas;
    SCropResizeData data;

    data.type = ECropResizeType_Original;
    data.name = "Original Size";
    data.desc = "";
    data.thumbnail = QPixmap(QString(":/QtmImg/img/%1/v165/icon20_crop_original.svg").arg(QtmCore::Theme::currentTheme()));
    datas.append(data);

    data.type = ECropResizeType_Custom;
    data.name = "Custom Size";
    data.desc = "";
    data.thumbnail = QPixmap(QString(":/QtmImg/img/%1/v165/icon20_crop_original.svg").arg(QtmCore::Theme::currentTheme()));
    datas.append(data);

    data.type = ECropResizeType_1080_1080;
    data.name = "Instagram Post";
    data.desc = "1080 x 1080 px";
    data.thumbnail = QPixmap(QString(":/QtmImg/img/%1/v165/icon20_crop_original.svg").arg(QtmCore::Theme::currentTheme()));
    datas.append(data);

    data.type = ECropResizeType_1080_1920;
    data.name = "Instagram Story";
    data.desc = "1080 x 1920 px";
    data.thumbnail = QPixmap(QString(":/QtmImg/img/%1/v165/icon20_crop_original.svg").arg(QtmCore::Theme::currentTheme()));
    datas.append(data);

    data.type = ECropResizeType_1200_630;
    data.name = "Facebook Post";
    data.desc = "1200 x 630 px";
    data.thumbnail = QPixmap(QString(":/QtmImg/img/%1/v165/icon20_crop_original.svg").arg(QtmCore::Theme::currentTheme()));
    datas.append(data);

    data.type = ECropResizeType_851_315;
    data.name = "Facebook Cover Image";
    data.desc = "851 x 315 px";
    data.thumbnail = QPixmap(QString(":/QtmImg/img/%1/v165/icon20_crop_original.svg").arg(QtmCore::Theme::currentTheme()));
    datas.append(data);

    data.type = ECropResizeType_1200_675;
    data.name = "X (Twitter) Post";
    data.desc = "1200 x 675 px";
    data.thumbnail = QPixmap(QString(":/QtmImg/img/%1/v165/icon20_crop_original.svg").arg(QtmCore::Theme::currentTheme()));
    datas.append(data);

    data.type = ECropResizeType_1500_500;
    data.name = "X (Twitter) Cover Image";
    data.desc = "1500 x 500 px";
    data.thumbnail = QPixmap(QString(":/QtmImg/img/%1/v165/icon20_crop_original.svg").arg(QtmCore::Theme::currentTheme()));
    datas.append(data);

    data.type = ECropResizeType_1280_720;
    data.name = "Youtube Thumbnail";
    data.desc = "1280 x 720 px";
    data.thumbnail = QPixmap(QString(":/QtmImg/img/%1/v165/icon20_crop_original.svg").arg(QtmCore::Theme::currentTheme()));
    datas.append(data);

    data.type = ECropResizeType_2000_2000;
    data.name = "Amazon Product";
    data.desc = "2000 x 2000 px";
    data.thumbnail = QPixmap(QString(":/QtmImg/img/%1/v165/icon20_crop_original.svg").arg(QtmCore::Theme::currentTheme()));
    datas.append(data);

    data.type = ECropResizeType_1600_1600;
    data.name = "eBay Product";
    data.desc = "1600 x 1600 px";
    data.thumbnail = QPixmap(QString(":/QtmImg/img/%1/v165/icon20_crop_original.svg").arg(QtmCore::Theme::currentTheme()));
    datas.append(data);

    data.type = ECropResizeType_2048_2048;
    data.name = "Shopify Product";
    data.desc = "2048 x 2048 px";
    data.thumbnail = QPixmap(QString(":/QtmImg/img/%1/v165/icon20_crop_original.svg").arg(QtmCore::Theme::currentTheme()));
    datas.append(data);

    data.type = ECropResizeType_1000_1500;
    data.name = "Pinterest Pin";
    data.desc = "1000 x 1500 px";
    data.thumbnail = QPixmap(QString(":/QtmImg/img/%1/v165/icon20_crop_original.svg").arg(QtmCore::Theme::currentTheme()));
    datas.append(data);

    data.type = ECropResizeType_1920_1080;
    data.name = "PPT Slide (16:9)";
    data.desc = "1920 x 1080 px";
    data.thumbnail = QPixmap(QString(":/QtmImg/img/%1/v165/icon20_crop_original.svg").arg(QtmCore::Theme::currentTheme()));
    datas.append(data);

    return datas;
}

CropViewCropAspectListDelegate::CropViewCropAspectListDelegate(QObject *parent) :
    QStyledItemDelegate(parent) {
}

void CropViewCropAspectListDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    auto data = index.data(Qt::UserRole).value<SCropAspectData>();
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::NoBrush);
    painter->setRenderHint(QPainter::Antialiasing, true);

    QRect rc = option.rect;
    bool pressed = m_EventType == QEvent::MouseButtonPress && rc.contains(m_CurPos);
    bool selected = option.state & QStyle::State_Selected;
    bool hover = option.state & QStyle::State_MouseOver;
    bool selected_or_hover = selected || hover;

    auto bgRect = rc.adjusted(0, 0, 0, 0);
    int radius = 8;

    QColor bgColor = QColor("#ffffff");
    if(hover) {
        bgColor = QColor("#e8e0fc");
    }
    painter->setBrush(bgColor);
    painter->drawRoundedRect(bgRect, radius, radius);
    painter->setBrush(Qt::NoBrush);

    auto pixmapRect = QRect(rc.left() + (rc.width() - 20) / 2, rc.top() + 10, 20, 20);
    Painter::paintPixmap(painter, pixmapRect, data.thumbnail, 1, radius, true);

    QColor borderColor = QColor("#ecebef");
    if (hover) {
        borderColor = QColor("#c9afff");
    }
    if (selected) {
        borderColor = QColor("#7938ff");
    }
    QPen penBorder(borderColor);
    painter->setPen(penBorder);
    painter->drawRoundedRect(bgRect.adjusted(1, 1, -1, -1), radius, radius);
    painter->setPen(Qt::NoPen);

    auto nameRect = QRect(bgRect.left() + 4, bgRect.bottom() - 24, bgRect.width() - 8, 18);
    QColor nameColor = QColor("#000000");
    QPen penName(nameColor);
    painter->setPen(penName);
    QFont font = painter->font();
    font.setPixelSize(13);
    painter->setFont(font);
    QString fileName = data.name;
    QFontMetricsF metrics(font);
    if (metrics.horizontalAdvance(fileName) > nameRect.width()) {
        fileName = metrics.elidedText(fileName, Qt::ElideMiddle, nameRect.width());
    }
    painter->drawText(nameRect, Qt::AlignCenter, fileName);
    painter->setPen(Qt::NoPen);
}

bool CropViewCropAspectListDelegate::eventFilter(QObject *object, QEvent *event) {
    int type = event->type();
    if (type == QEvent::MouseMove || type == QEvent::MouseButtonPress || type == QEvent::MouseButtonRelease) {
        m_EventType = type;
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        if (mouseEvent) {
            QPoint pos = mouseEvent->pos();
            m_CurPos = pos;
            QWidget *curWidget = static_cast<QWidget *>(object);
            curWidget->update();
        }
    }
    return QStyledItemDelegate::eventFilter(object, event);
}

QSize CropViewCropAspectListDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {
    return m_Size;
}

CropViewCropResizeListDelegate::CropViewCropResizeListDelegate(QObject *parent) :
    QStyledItemDelegate(parent) {
}

void CropViewCropResizeListDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    auto data = index.data(Qt::UserRole).value<SCropResizeData>();
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::NoBrush);
    painter->setRenderHint(QPainter::Antialiasing, true);

    QRect rc = option.rect;
    bool pressed = m_EventType == QEvent::MouseButtonPress && rc.contains(m_CurPos);
    bool selected = option.state & QStyle::State_Selected;
    bool hover = option.state & QStyle::State_MouseOver;
    bool selected_or_hover = selected || hover;

    auto bgRect = rc.adjusted(0, 0, 0, 0);
    int radius = 8;

    QColor bgColor = QColor("#ffffff");
    if(hover) {
        bgColor = QColor("#e8e0fc");
    }
    painter->setBrush(bgColor);
    painter->drawRoundedRect(bgRect, radius, radius);
    painter->setBrush(Qt::NoBrush);

    // auto pixmapRect = rc.adjusted(4, 4, -4, -28);
    // Painter::paintPixmap(painter, pixmapRect, data.thumbnail, 1, radius, true);

    QColor borderColor = QColor("#ecebef");
    if (hover) {
        borderColor = QColor("#c9afff");
    }
    if (selected) {
        borderColor = QColor("#7938ff");
    }
    QPen penBorder(borderColor);
    painter->setPen(penBorder);
    painter->drawRoundedRect(bgRect.adjusted(1, 1, -1, -1), radius, radius);
    painter->setPen(Qt::NoPen);

    //
    auto nameRect = QRect(bgRect.left() + 8, bgRect.top() + 8, bgRect.width() - 16, 18);
    if(data.type == ECropResizeType_Original || data.type == ECropResizeType_Custom) {
        nameRect = QRect(bgRect.left() + 8, bgRect.top() + (bgRect.height() - 18) / 2, bgRect.width() - 16, 18);
    }
    QColor nameColor = QColor("#000000");
    QPen penName(nameColor);
    painter->setPen(penName);
    QFont fontName = painter->font();
    fontName.setPixelSize(13);
    painter->setFont(fontName);
    QString fileName = data.name;
    QFontMetricsF metricsName(fontName);
    if (metricsName.horizontalAdvance(fileName) > nameRect.width()) {
        fileName = metricsName.elidedText(fileName, Qt::ElideMiddle, nameRect.width());
    }
    painter->drawText(nameRect, Qt::AlignCenter, fileName);
    painter->setPen(Qt::NoPen);

    //
    auto descRect = QRect(bgRect.left() + 8, bgRect.bottom() - 24, bgRect.width() - 16, 16);
    QColor descColor = QColor("#666666");
    QPen penDesc(descColor);
    painter->setPen(penDesc);
    QFont fontDesc = painter->font();
    fontDesc.setPixelSize(12);
    painter->setFont(fontDesc);
    QString desc = data.desc;
    QFontMetricsF metricsDesc(fontDesc);
    if (metricsDesc.horizontalAdvance(desc) > descRect.width()) {
        desc = metricsDesc.elidedText(desc, Qt::ElideMiddle, descRect.width());
    }
    painter->drawText(descRect, Qt::AlignCenter, desc);
    painter->setPen(Qt::NoPen);
}

bool CropViewCropResizeListDelegate::eventFilter(QObject *object, QEvent *event) {
    int type = event->type();
    if (type == QEvent::MouseMove || type == QEvent::MouseButtonPress || type == QEvent::MouseButtonRelease) {
        m_EventType = type;
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        if (mouseEvent) {
            QPoint pos = mouseEvent->pos();
            m_CurPos = pos;
            QWidget *curWidget = static_cast<QWidget *>(object);
            curWidget->update();
        }
    }
    return QStyledItemDelegate::eventFilter(object, event);
}

QSize CropViewCropResizeListDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {
    return m_Size;
}

CropView::CropView(QWidget *parent) :
    QWidget(parent) {
    createUi();
    connectSig();
    onLanguageChange();
}

ImportListView *CropView::getImportListView() {
    return m_pImportListView;
}

void CropView::showEvent(QShowEvent *event) {
    QWidget::showEvent(event);
    firstShow();
}

void CropView::createUi() {
    setObjectName("EP_BGView");
    setAttribute(Qt::WA_StyledBackground);

    m_pLanguageFilter = new LanguageFilter(this);

    //
    m_pTitleLbl = new QLabel(this);
    m_pTitleLbl->setObjectName("QLbl_LH24_FS24_FW7");
    auto titleLabLayout = new QHBoxLayout();
    titleLabLayout->setContentsMargins(20, 0, 0, 0);
    titleLabLayout->addWidget(m_pTitleLbl, 0, Qt::AlignLeft);

    //
    m_pImportGuideWidget = new QWidget(this);
    QVBoxLayout *importGuideLayout = new QVBoxLayout(m_pImportGuideWidget);
    importGuideLayout->setContentsMargins(20, 20, 20, 8);
    importGuideLayout->setSpacing(0);

    m_pImportGuide = new ImportGuide(this);

    m_pSmapleWidget = new QWidget(this);
    m_pSmapleWidget->setFixedHeight(100);
    auto smapleWidgetLayout = new QVBoxLayout(m_pSmapleWidget);
    smapleWidgetLayout->setContentsMargins(0, 0, 0, 12);
    smapleWidgetLayout->setSpacing(0);

    m_pSmapleTitleLbl = new QLabel(this);
    m_pSmapleTitleLbl->setObjectName("QLbl_LH20_FS14_FW4");
    m_pSmapleTitleLbl->setAlignment(Qt::AlignCenter);

    m_pSmaple1ImageLbl = new ClickableLabel(this);
    m_pSmaple1ImageLbl->setFixedSize(128, 72);
    m_pSmaple2ImageLbl = new ClickableLabel(this);
    m_pSmaple2ImageLbl->setFixedSize(128, 72);

    auto sampleImageLayout = new QHBoxLayout();
    sampleImageLayout->setContentsMargins(0, 0, 0, 0);
    sampleImageLayout->setSpacing(14);
    sampleImageLayout->addStretch();
    sampleImageLayout->addWidget(m_pSmaple1ImageLbl);
    sampleImageLayout->addWidget(m_pSmaple2ImageLbl);
    sampleImageLayout->addStretch();

    smapleWidgetLayout->addWidget(m_pSmapleTitleLbl);
    smapleWidgetLayout->addSpacing(4);
    smapleWidgetLayout->addLayout(sampleImageLayout);

    importGuideLayout->addWidget(m_pImportGuide, 1);
    importGuideLayout->addSpacing(8);
    importGuideLayout->addWidget(m_pSmapleWidget);

    //
    m_pWorkspaceWidget = new QWidget(this);
    auto bodyWidgetLayout = new QHBoxLayout(m_pWorkspaceWidget);
    bodyWidgetLayout->setContentsMargins(0, 0, 0, 0);
    bodyWidgetLayout->setSpacing(0);

    m_pLeftWidget = new QWidget(this);
    auto LeftWidgetLayout = new QVBoxLayout(m_pLeftWidget);
    LeftWidgetLayout->setContentsMargins(12, 12, 0, 10);
    LeftWidgetLayout->setSpacing(0);

    m_pRightWidget = new QWidget(this);
    m_pRightWidget->setFixedWidth(255);
    auto rightWidgetLayout = new QVBoxLayout(m_pRightWidget);
    rightWidgetLayout->setContentsMargins(12, 12, 12, 20);
    rightWidgetLayout->setSpacing(0);

    bodyWidgetLayout->addWidget(m_pLeftWidget, 1);
    bodyWidgetLayout->addWidget(m_pRightWidget);

    //
    m_pImageViewer = new ImageWorkWidget(this);
    m_pImportListView = new ImportListView(this);
    LeftWidgetLayout->addWidget(m_pImageViewer, 1);
    LeftWidgetLayout->addSpacing(8);
    LeftWidgetLayout->addWidget(m_pImportListView);

    //
    auto scaleOrSizeBtnWidget = new QWidget();
    scaleOrSizeBtnWidget->setObjectName("EP_SwitchBtnWidget");
    scaleOrSizeBtnWidget->setFixedHeight(28);

    auto scaleOrSizeBtnLayout = new QHBoxLayout(scaleOrSizeBtnWidget);
    scaleOrSizeBtnLayout->setContentsMargins(2, 2, 2, 2);
    scaleOrSizeBtnLayout->setSpacing(4);

    m_pCropBtn = new QPushButton(this);
    m_pCropBtn->setObjectName("EP_SwitchBtn");
    m_pCropBtn->setFixedHeight(24);
    m_pCropBtn->setCheckable(true);
    scaleOrSizeBtnLayout->addWidget(m_pCropBtn);

    m_pResizeBtn = new QPushButton(this);
    m_pResizeBtn->setObjectName("EP_SwitchBtn");
    m_pResizeBtn->setFixedHeight(24);
    m_pResizeBtn->setCheckable(true);
    scaleOrSizeBtnLayout->addWidget(m_pResizeBtn);

    auto scaleOrSizeBtnGroup = new QButtonGroup(this);
    scaleOrSizeBtnGroup->setExclusive(true);
    scaleOrSizeBtnGroup->addButton(m_pCropBtn, 0);
    scaleOrSizeBtnGroup->addButton(m_pResizeBtn, 1);

    rightWidgetLayout->addWidget(scaleOrSizeBtnWidget);
    rightWidgetLayout->addSpacing(4);

    //
    m_pCropAspectListView = new ListView<SCropAspectData>(this);
    m_pCropAspectListView->setStyleSheet("border-radius:10px; background-color:#f7f7fc;");
    m_pCropAspectListView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_pCropAspectListView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_pCropAspectListView->setFixedHeight(179);
    m_pCropAspectListView->setSpacing(4);
    m_pCropAspectListDelegate = new CropViewCropAspectListDelegate(m_pCropAspectListView);
    m_pCropAspectListView->setItemDelegate(m_pCropAspectListDelegate);
    m_pCropAspectListView->viewport()->installEventFilter(m_pCropAspectListDelegate);
    rightWidgetLayout->addWidget(m_pCropAspectListView);

    //
    m_pCropResizeListView = new ListView<SCropResizeData>(this);
    m_pCropResizeListView->setStyleSheet("border-radius:10px; background-color:#f7f7fc;");
    m_pCropResizeListView->setFixedHeight(220);
    m_pCropResizeListView->setSpacing(4);
    m_pCropResizeListDelegate = new CropViewCropResizeListDelegate(m_pCropResizeListView);
    m_pCropResizeListView->setItemDelegate(m_pCropResizeListDelegate);
    m_pCropResizeListView->viewport()->installEventFilter(m_pCropResizeListDelegate);
    rightWidgetLayout->addWidget(m_pCropResizeListView);

    rightWidgetLayout->addSpacing(4);

    //
    m_pPixelsWidthLdt = new UnitLineEdit(this);
    m_pPixelsWidthLdt->setFixedHeight(24);
    m_pPixelsWidthLdt->setAlignment(Qt::AlignCenter);
    m_pPixelsWidthLdt->setPrefix("W");
    m_pPixelsWidthLdt->setUnit("PX");
    m_pPixelsWidthLdt->setText("0");
    m_pLockScaleBtn = new IconButton(this);
    m_pLockScaleBtn->setFixedSize(24, 24);
    m_pLockScaleBtn->setIconSize(24, 24);
    m_pLockScaleBtn->setFourPixmapPath(QString(":/QtmImg/img/%1/v165/icon24_lock.svg").arg(QtmCore::Theme::currentTheme()));
    m_pPixelsHeightLdt = new UnitLineEdit(this);
    m_pPixelsHeightLdt->setFixedHeight(24);
    m_pPixelsHeightLdt->setAlignment(Qt::AlignCenter);
    m_pPixelsHeightLdt->setPrefix("H");
    m_pPixelsHeightLdt->setUnit("PX");
    m_pPixelsHeightLdt->setText("0");

    auto pixelsLayout = new QHBoxLayout();
    pixelsLayout->setContentsMargins(0, 0, 0, 0);
    pixelsLayout->setSpacing(4);
    pixelsLayout->addWidget(m_pPixelsWidthLdt);
    pixelsLayout->addWidget(m_pLockScaleBtn);
    pixelsLayout->addWidget(m_pPixelsHeightLdt);
    rightWidgetLayout->addLayout(pixelsLayout);

    //
    rightWidgetLayout->addSpacing(16);


    //
    m_pRotateAndFlipWidget = new QWidget(this);
    auto rotateAndFlipLayout = new QVBoxLayout(m_pRotateAndFlipWidget);
    rotateAndFlipLayout->setContentsMargins(0, 0, 0, 0);
    rotateAndFlipLayout->setSpacing(0);

    m_pRotateAndFlipLbl = new QLabel(this);
    m_pRotateAndFlipLbl->setObjectName("QLbl_LH16_FS12_FW4");
    rotateAndFlipLayout->addWidget(m_pRotateAndFlipLbl);
    rotateAndFlipLayout->addSpacing(4);

    m_pRotateRight90Btn = new IconButton(this);
    m_pRotateRight90Btn->setFixedSize(32, 32);
    m_pRotateRight90Btn->setIconSize(32, 32);
    m_pRotateRight90Btn->setFourPixmapPath(QString(":/QtmImg/img/%1/v16/icon32/icon32_rotate_right.svg").arg(QtmCore::Theme::currentTheme()));
    m_pRotateLeft90Btn = new IconButton(this);
    m_pRotateLeft90Btn->setFixedSize(32, 32);
    m_pRotateLeft90Btn->setIconSize(32, 32);
    m_pRotateLeft90Btn->setFourPixmapPath(QString(":/QtmImg/img/%1/v16/icon32/icon32_rotate_Left.svg").arg(QtmCore::Theme::currentTheme()));
    m_pFlipHorBtn = new IconButton(this);
    m_pFlipHorBtn->setFixedSize(32, 32);
    m_pFlipHorBtn->setIconSize(32, 32);
    m_pFlipHorBtn->setFourPixmapPath(QString(":/QtmImg/img/%1/v16/icon32/icon32_vertical symmetry.svg").arg(QtmCore::Theme::currentTheme()));
    m_pFlipVErBtn = new IconButton(this);
    m_pFlipVErBtn->setFixedSize(32, 32);
    m_pFlipVErBtn->setIconSize(32, 32);
    m_pFlipVErBtn->setFourPixmapPath(QString(":/QtmImg/img/%1/v16/icon32/icon32_horizontal symmetry.svg").arg(QtmCore::Theme::currentTheme()));
    auto rotateBtnLayout = new QHBoxLayout();
    rotateBtnLayout->setContentsMargins(0, 0, 0, 0);
    rotateBtnLayout->setSpacing(8);
    rotateBtnLayout->addWidget(m_pRotateRight90Btn);
    rotateBtnLayout->addWidget(m_pRotateLeft90Btn);
    rotateBtnLayout->addWidget(m_pFlipHorBtn);
    rotateBtnLayout->addWidget(m_pFlipVErBtn);
    rotateBtnLayout->addStretch();
    rotateAndFlipLayout->addLayout(rotateBtnLayout);

    rotateAndFlipLayout->addSpacing(16);

    rightWidgetLayout->addWidget(m_pRotateAndFlipWidget);

    //
    m_pStretchToFitWidget = new QWidget(this);
    auto stretchToFitLayout = new QVBoxLayout(m_pStretchToFitWidget);
    stretchToFitLayout->setContentsMargins(0, 0, 0, 0);
    stretchToFitLayout->setSpacing(0);

    m_pStretchToFitCkb = new QCheckBox(this);
    stretchToFitLayout->addWidget(m_pStretchToFitCkb);
    stretchToFitLayout->addSpacing(16);

    rightWidgetLayout->addWidget(m_pStretchToFitWidget);

    //
    m_pBgWidget = new QWidget(this);
    auto bgWidgetLayout = new QVBoxLayout(m_pBgWidget);
    bgWidgetLayout->setContentsMargins(0, 0, 0, 0);
    bgWidgetLayout->setSpacing(0);

    m_pBgLbl = new QLabel(this);
    m_pBgLbl->setObjectName("QLbl_LH16_FS12_FW4");
    bgWidgetLayout->addWidget(m_pBgLbl);
    bgWidgetLayout->addSpacing(4);

    m_pBg1Btn = new IconButton(this);
    m_pBg1Btn->setFixedSize(32, 32);
    m_pBg1Btn->setIconSize(32, 32);
    m_pBg1Btn->setFourPixmapPath(QString(":/QtmImg/img/%1/v165/bg32_alpha.svg").arg(QtmCore::Theme::currentTheme()), true);
    m_pBg1Btn->setCheckable(true);

    m_pBg2Btn = new IconButton(this);
    m_pBg2Btn->setFixedSize(32, 32);
    m_pBg2Btn->setIconSize(32, 32);
    m_pBg2Btn->setFourPixmapPath(QString(":/QtmImg/img/%1/v165/bg32_white.svg").arg(QtmCore::Theme::currentTheme()));
    m_pBg2Btn->setCheckable(true);

    m_pBg3Btn = new IconButton(this);
    m_pBg3Btn->setFixedSize(32, 32);
    m_pBg3Btn->setIconSize(32, 32);
    m_pBg3Btn->setFourPixmapPath(QString(":/QtmImg/img/%1/v165/bg32_black.svg").arg(QtmCore::Theme::currentTheme()));
    m_pBg3Btn->setCheckable(true);

    m_pBg4Btn = new IconButton(this);
    m_pBg4Btn->setFixedSize(32, 32);
    m_pBg4Btn->setIconSize(32, 32);
    m_pBg4Btn->setFourPixmapPath(QString(":/QtmImg/img/%1/v165/bg32_grey.svg").arg(QtmCore::Theme::currentTheme()));
    m_pBg4Btn->setCheckable(true);

    m_pBg5Btn = new IconButton(this);
    m_pBg5Btn->setFixedSize(32, 32);
    m_pBg5Btn->setIconSize(32, 32);
    m_pBg5Btn->setFourPixmapPath(QString(":/QtmImg/img/%1/v165/bg32_light blue.svg").arg(QtmCore::Theme::currentTheme()));
    m_pBg5Btn->setCheckable(true);

    m_pBgSelectBtn = new IconButton(this);
    m_pBgSelectBtn->setFixedSize(32, 32);
    m_pBgSelectBtn->setIconSize(32, 32);
    m_pBgSelectBtn->setFourPixmapPath(QString(":/QtmImg/img/%1/v165/bg32_gradiet3.png").arg(QtmCore::Theme::currentTheme()));

    m_pBgBtnGroup = new QButtonGroup(this);
    m_pBgBtnGroup->setExclusive(true);
    m_pBgBtnGroup->addButton(m_pBg1Btn, 0);
    m_pBgBtnGroup->addButton(m_pBg2Btn, 1);
    m_pBgBtnGroup->addButton(m_pBg3Btn, 2);
    m_pBgBtnGroup->addButton(m_pBg4Btn, 3);
    m_pBgBtnGroup->addButton(m_pBg5Btn, 4);

    auto bgBtnLayout = new QHBoxLayout();
    bgBtnLayout->setContentsMargins(0, 0, 0, 0);
    bgBtnLayout->setSpacing(4);
    bgBtnLayout->addWidget(m_pBg1Btn);
    bgBtnLayout->addWidget(m_pBg2Btn);
    bgBtnLayout->addWidget(m_pBg3Btn);
    bgBtnLayout->addWidget(m_pBg4Btn);
    bgBtnLayout->addWidget(m_pBg5Btn);
    bgBtnLayout->addWidget(m_pBgSelectBtn);
    bgWidgetLayout->addLayout(bgBtnLayout);

    bgWidgetLayout->addSpacing(16);

    rightWidgetLayout->addWidget(m_pBgWidget);

    //
    m_pApplySameCkb = new QCheckBox(this);
    m_pResetBtn = new IconButton(this);
    m_pResetBtn->setFixedSize(24, 24);
    m_pResetBtn->setIconSize(24, 24);
    m_pResetBtn->setFourPixmapPath(QString(":/QtmImg/img/%1/v16/icon24/icon24_refresh2.svg").arg(QtmCore::Theme::currentTheme()));

    auto applySameLayout = new QHBoxLayout();
    applySameLayout->setContentsMargins(0, 0, 0, 0);
    applySameLayout->addWidget(m_pApplySameCkb);
    applySameLayout->addStretch();
    applySameLayout->addWidget(m_pResetBtn);
    rightWidgetLayout->addLayout(applySameLayout);
    // rightWidgetLayout->addSpacing(16);
    m_pApplySameCkb->setVisible(false);
    m_pResetBtn->setVisible(false);

    //
    m_pOutputFmtLbl = new QLabel(this);
    m_pOutputFmtLbl->setObjectName("QLbl_LH16_FS12_FW4");
    rightWidgetLayout->addWidget(m_pOutputFmtLbl);
    rightWidgetLayout->addSpacing(4);

    m_pPNGBtn = new QPushButton(this);
    m_pPNGBtn->setObjectName("QPBtn_H32_R8_B1_T14_W7");
    m_pPNGBtn->setFixedSize(50, 32);
    m_pPNGBtn->setCheckable(true);

    m_pJPGBtn = new QPushButton(this);
    m_pJPGBtn->setObjectName("QPBtn_H32_R8_B1_T14_W7");
    m_pJPGBtn->setFixedSize(50, 32);
    m_pJPGBtn->setCheckable(true);

    m_pBMPBtn = new QPushButton(this);
    m_pBMPBtn->setObjectName("QPBtn_H32_R8_B1_T14_W7");
    m_pBMPBtn->setFixedSize(50, 32);
    m_pBMPBtn->setCheckable(true);

    m_pWEBPBtn = new QPushButton(this);
    m_pWEBPBtn->setObjectName("QPBtn_H32_R8_B1_T14_W7");
    m_pWEBPBtn->setFixedSize(50, 32);
    m_pWEBPBtn->setCheckable(true);
    
    m_pOutputFmtBtnGroup = new QButtonGroup(this);
    m_pOutputFmtBtnGroup->setExclusive(true);
    m_pOutputFmtBtnGroup->addButton(m_pPNGBtn, 0);
    m_pOutputFmtBtnGroup->addButton(m_pJPGBtn, 1);
    m_pOutputFmtBtnGroup->addButton(m_pBMPBtn, 2);
    m_pOutputFmtBtnGroup->addButton(m_pWEBPBtn, 3);

    auto bgImgBtnLayout = new QHBoxLayout();
    bgImgBtnLayout->setContentsMargins(0, 0, 0, 0);
    bgImgBtnLayout->setSpacing(4);
    bgImgBtnLayout->addWidget(m_pPNGBtn);
    bgImgBtnLayout->addWidget(m_pJPGBtn);
    bgImgBtnLayout->addWidget(m_pBMPBtn);
    bgImgBtnLayout->addWidget(m_pWEBPBtn);
    bgImgBtnLayout->addStretch();
    rightWidgetLayout->addLayout(bgImgBtnLayout);

    rightWidgetLayout->addSpacing(16);

    //
    m_pOutputFolderLbl = new QLabel(this);
    m_pOutputFolderLbl->setObjectName("QLbl_LH16_FS12_FW4");
    rightWidgetLayout->addWidget(m_pOutputFolderLbl);
    rightWidgetLayout->addSpacing(4);

    m_pOutputFolderCbb = new QComboBox(this);
    m_pOutputFolderCbb->setFixedHeight(24);

    m_pOpenOutputFolderBtn = new IconButton(this);
    m_pOpenOutputFolderBtn->setFixedSize(24, 24);
    m_pOpenOutputFolderBtn->setIconSize(24, 24);
    m_pOpenOutputFolderBtn->setFourPixmapPath(QString(":/QtmImg/img/%1/icon/icon_state/icon24/icon24_file.png").arg(QtmCore::Theme::currentTheme()));

    auto outputFolderLayout = new QHBoxLayout();
    outputFolderLayout->setContentsMargins(0, 0, 0, 0);
    outputFolderLayout->setSpacing(4);

    outputFolderLayout->addWidget(m_pOutputFolderCbb, 1);
    outputFolderLayout->addStretch();
    outputFolderLayout->addWidget(m_pOpenOutputFolderBtn);

    rightWidgetLayout->addLayout(outputFolderLayout);

    //
    rightWidgetLayout->addStretch();

    //
    m_pExportBtn = new QPushButton(this);
    m_pExportBtn->setObjectName("QPBtn_BR16_FS14_FW7");
    m_pExportBtn->setFixedHeight(32);
    rightWidgetLayout->addWidget(m_pExportBtn);

    //
    m_pStackedLayout = new QStackedLayout();
    m_pStackedLayout->addWidget(m_pImportGuideWidget);
    m_pStackedLayout->addWidget(m_pWorkspaceWidget);

    auto stackedMarginLayout = new QVBoxLayout();
    stackedMarginLayout->setContentsMargins(0, 0, 0, 0);
    stackedMarginLayout->addLayout(m_pStackedLayout, 1);

    //
    auto layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addLayout(titleLabLayout, 0);
    layout->addLayout(stackedMarginLayout, 1);
}

void CropView::connectSig() {
    connect(m_pLanguageFilter, &LanguageFilter::sigLanguageChange, this, &CropView::onLanguageChange);
    connect(m_pSmaple1ImageLbl, &ClickableLabel::sigClicked, this, &CropView::onSmaple1ImageLblClicked);
    connect(m_pSmaple2ImageLbl, &ClickableLabel::sigClicked, this, &CropView::onSmaple2ImageLblClicked);
    connect(m_pImportListView, &ImportListView::sigImportListCountChange, this, &CropView::onImportListCountChange);
    connect(m_pImportListView, &ImportListView::sigImportListCurrentChanged, this, &CropView::onImportListCurrentChanged);
    connect(m_pImportGuide, &ImportGuide::sigImportFile, this, &CropView::onGuideImportFile);
    connect(m_pResetBtn, &IconButton::clicked, this, &CropView::onResetBtnClieked);
    connect(m_pCropBtn, &QPushButton::clicked, this, &CropView::onCropBtnClicked);
    connect(m_pResizeBtn, &QPushButton::clicked, this, &CropView::onResizeBtnClicked);
    connect(m_pCropAspectListView, &AbstractListView::sigCurrentChanged, this, &CropView::onCropAspectListCurrentChanged);
    connect(m_pCropResizeListView, &AbstractListView::sigCurrentChanged, this, &CropView::onCropResizeListCurrentChanged);
    connect(m_pStretchToFitCkb, &QCheckBox::stateChanged, this, &CropView::onStretchToFitCkbStateChanged);
}

void CropView::firstShow() {
    static bool firstShow = true;
    if(firstShow) {
        firstShow = false;
        loadSampleImage();
        initOutputFolderCbbItem();

        m_pCropBtn->setChecked(true);
        m_pCropAspectListView->changeData(getCropAspectFormatDatas());
        m_pCropResizeListView->changeData(getCropResizeFormatDatas());
        m_pCropResizeListView->setVisible(false);
        m_pStretchToFitWidget->setVisible(false);
        m_pBgWidget->setVisible(false);
    }
}

void CropView::loadSampleImage() {
    CropPresenter *prst = dynamic_cast<CropPresenter *>(presenter());
    m_pSmaple1ImageLbl->setPixmap(QPixmap(prst->getSampleImage1Path()).scaled(m_pSmaple1ImageLbl->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    m_pSmaple2ImageLbl->setPixmap(QPixmap(prst->getSampleImage2Path()).scaled(m_pSmaple2ImageLbl->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

void CropView::importSampleImage1() {
    CropPresenter *prst = dynamic_cast<CropPresenter *>(presenter());
    QStringList paths;
    paths.append(prst->getSampleImage1Path());
    m_pImportListView->importFile(paths);
}

void CropView::importSampleImage2() {
    CropPresenter *prst = dynamic_cast<CropPresenter *>(presenter());
    QStringList paths;
    paths.append(prst->getSampleImage2Path());
    m_pImportListView->importFile(paths);
}

void CropView::initOutputFolderCbbItem() {
    m_pOutputFolderCbb->addItem(SETTINGS->getCropSetting()->getOutPath());
}

void CropView::gotoImportGuide() {
    m_pStackedLayout->setCurrentWidget(m_pImportGuideWidget);
}

void CropView::gotoWorkspace() {
    m_pStackedLayout->setCurrentWidget(m_pWorkspaceWidget);
}

void CropView::imageViewerLoad(const QString &filePath) {
    m_pImageViewer->workspace()->loadImage(filePath);

    if(m_pCropBtn->isChecked())
    {
        m_pImageViewer->workspace()->setWorkspaceMode(ImageWorkspace::ModeCrop);
        m_pImageViewer->workspace()->setCropAspectRatioMode(ImageWorkspace::CropAspectOriginal);
    }
    else
    {
        m_pImageViewer->workspace()->setWorkspaceMode(ImageWorkspace::ModeResize);
        m_pImageViewer->workspace()->setResizeCanvasSize(CropAspectResizeMode[ECropResizeType_Original]);
    }
    m_pImageViewer->workspace()->setFitView();
}

void CropView::onLanguageChange() {
    m_pTitleLbl->setText(tr("Image Cropper"));
    m_pCropBtn->setText(tr("Crop"));
    m_pResizeBtn->setText(tr("Resize"));
    m_pRotateAndFlipLbl->setText(tr("Rotate and Flip"));
    m_pStretchToFitCkb->setText(tr("Stretch to Fit"));
    m_pBgLbl->setText(tr("Background"));
    m_pApplySameCkb->setText(tr("Apply same to all images"));
    m_pOutputFmtLbl->setText(tr("Output Format"));
    m_pPNGBtn->setText(tr("PNG"));
    m_pJPGBtn->setText(tr("JPG"));
    m_pBMPBtn->setText(tr("BMP"));
    m_pWEBPBtn->setText(tr("WEBP"));
    m_pSmapleTitleLbl->setText(tr("Try with one of our smaples!"));
    m_pOutputFolderLbl->setText(tr("Output folder:"));
    m_pExportBtn->setText(tr("Export"));
}

void CropView::onSmaple1ImageLblClicked() {
    importSampleImage1();
}

void CropView::onSmaple2ImageLblClicked() {
    importSampleImage2();
}

void CropView::onImportListCountChange(int count) {
    if(count > 0) {
        gotoWorkspace();
    } else {
        gotoImportGuide();
    }
}

void CropView::onImportListCurrentChanged(const QString filePath) {
    imageViewerLoad(filePath);
}

void CropView::onGuideImportFile(const QStringList &filePaths) {
    CropPresenter *prst = dynamic_cast<CropPresenter *>(presenter());
    m_pImportListView->importFile(filePaths);
}

void CropView::onResetBtnClieked() {
    m_pImageViewer->workspace()->resetCropRect();
}

void CropView::onCropBtnClicked() {
    m_pCropAspectListView->setVisible(true);
    m_pRotateAndFlipWidget->setVisible(true);
    m_pCropResizeListView->setVisible(false);
    m_pStretchToFitWidget->setVisible(false);
    m_pBgWidget->setVisible(false);
    m_pImageViewer->workspace()->setWorkspaceMode(ImageWorkspace::ModeCrop);
}

void CropView::onResizeBtnClicked() {
    m_pCropAspectListView->setVisible(false);
    m_pRotateAndFlipWidget->setVisible(false);
    m_pCropResizeListView->setVisible(true);
    m_pStretchToFitWidget->setVisible(true);
    if(!m_pStretchToFitCkb->isChecked())
        m_pBgWidget->setVisible(true);
    m_pImageViewer->workspace()->setWorkspaceMode(ImageWorkspace::ModeResize);
}

void CropView::onCropAspectListCurrentChanged(const QModelIndex &current, const QModelIndex &previous) {
    auto aspectData = current.data(Qt::UserRole).value<SCropAspectData>();
    m_pImageViewer->workspace()->setCropAspectRatioMode(CropAspectRatioMode[aspectData.type]);
    m_pImageViewer->workspace()->setFitView();
}

void CropView::onCropResizeListCurrentChanged(const QModelIndex &current, const QModelIndex &previous) {
    auto resizeData = current.data(Qt::UserRole).value<SCropResizeData>();
    m_pImageViewer->workspace()->setResizeCanvasSize(CropAspectResizeMode[resizeData.type]);
    m_pImageViewer->workspace()->setFitView();
}

void CropView::onStretchToFitCkbStateChanged(int state) {
    bool checked = state == Qt::Checked;
    m_pBgWidget->setVisible(!checked);
    m_pImageViewer->workspace()->toggleFillMode();
}