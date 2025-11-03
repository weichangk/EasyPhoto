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
    data.thumbnail = QPixmap(QString(":/QtmImg/img/%1/v165/icon24_lock.svg").arg(QtmCore::Theme::currentTheme()));
    datas.append(data);

    data.type = ECropAspectType_Custom;
    data.name = "Custom";
    data.thumbnail = QPixmap(QString(":/QtmImg/img/%1/v165/icon24_lock.svg").arg(QtmCore::Theme::currentTheme()));
    datas.append(data);

    data.type = ECropAspectType_1_1;
    data.name = "1:1";
    data.thumbnail = QPixmap(QString(":/QtmImg/img/%1/v165/icon24_lock.svg").arg(QtmCore::Theme::currentTheme()));
    datas.append(data);

    data.type = ECropAspectType_16_9;
    data.name = "16:9";
    data.thumbnail = QPixmap(QString(":/QtmImg/img/%1/v165/icon24_lock.svg").arg(QtmCore::Theme::currentTheme()));
    datas.append(data);

    data.type = ECropAspectType_9_16;
    data.name = "9:16";
    data.thumbnail = QPixmap(QString(":/QtmImg/img/%1/v165/icon24_lock.svg").arg(QtmCore::Theme::currentTheme()));
    datas.append(data);

    data.type = ECropAspectType_4_3;
    data.name = "4:3";
    data.thumbnail = QPixmap(QString(":/QtmImg/img/%1/v165/icon24_lock.svg").arg(QtmCore::Theme::currentTheme()));
    datas.append(data);

    data.type = ECropAspectType_3_4;
    data.name = "3:4";
    data.thumbnail = QPixmap(QString(":/QtmImg/img/%1/v165/icon24_lock.svg").arg(QtmCore::Theme::currentTheme()));
    datas.append(data);

    data.type = ECropAspectType_3_2;
    data.name = "3:2";
    data.thumbnail = QPixmap(QString(":/QtmImg/img/%1/v165/icon24_lock.svg").arg(QtmCore::Theme::currentTheme()));
    datas.append(data);

    data.type = ECropAspectType_2_3;
    data.name = "2:3";
    data.thumbnail = QPixmap(QString(":/QtmImg/img/%1/v165/icon24_lock.svg").arg(QtmCore::Theme::currentTheme()));
    datas.append(data);

    return datas;
}

QList<SCropResizeData> getCropResizeFormatDatas() {
    QList<SCropResizeData> datas;
    SCropResizeData data;

    data.type = ECropResizeType_Original;
    data.name = "Original";
    data.desc = "Keep the original image size";
    data.thumbnail = QPixmap(QString(":/QtmImg/img/%1/v165/icon24_lock.svg").arg(QtmCore::Theme::currentTheme()));
    datas.append(data);

    data.type = ECropResizeType_Custom;
    data.name = "Custom";
    data.desc = "Keep the original image size";
    data.thumbnail = QPixmap(QString(":/QtmImg/img/%1/v165/icon24_lock.svg").arg(QtmCore::Theme::currentTheme()));
    datas.append(data);

    data.type = ECropResizeType_1080_1080;
    data.name = "1080x1080";
    data.desc = "Ideal for Instagram posts";
    data.thumbnail = QPixmap(QString(":/QtmImg/img/%1/v165/icon24_lock.svg").arg(QtmCore::Theme::currentTheme()));
    datas.append(data);

    data.type = ECropResizeType_1080_1920;
    data.name = "1080x1920";
    data.desc = "Perfect for Instagram stories and TikTok videos";
    data.thumbnail = QPixmap(QString(":/QtmImg/img/%1/v165/icon24_lock.svg").arg(QtmCore::Theme::currentTheme()));
    datas.append(data);

    data.type = ECropResizeType_1200_630;
    data.name = "1200x630";
    data.desc = "Recommended for Facebook link shares";
    data.thumbnail = QPixmap(QString(":/QtmImg/img/%1/v165/icon24_lock.svg").arg(QtmCore::Theme::currentTheme()));
    datas.append(data);

    data.type = ECropResizeType_851_315;
    data.name = "851x315";
    data.desc = "Optimal for Facebook cover photos";
    data.thumbnail = QPixmap(QString(":/QtmImg/img/%1/v165/icon24_lock.svg").arg(QtmCore::Theme::currentTheme()));
    datas.append(data);

    data.type = ECropResizeType_1200_675;
    data.name = "1200x675";
    data.desc = "Great for Twitter in-stream photos";
    data.thumbnail = QPixmap(QString(":/QtmImg/img/%1/v165/icon24_lock.svg").arg(QtmCore::Theme::currentTheme()));
    datas.append(data);

    data.type = ECropResizeType_1500_500;
    data.name = "1500x500";
    data.desc = "Suitable for Twitter header images";
    data.thumbnail = QPixmap(QString(":/QtmImg/img/%1/v165/icon24_lock.svg").arg(QtmCore::Theme::currentTheme()));
    datas.append(data);

    data.type = ECropResizeType_1280_720;
    data.name = "1280x720";
    data.desc = "Standard HD video resolution";
    data.thumbnail = QPixmap(QString(":/QtmImg/img/%1/v165/icon24_lock.svg").arg(QtmCore::Theme::currentTheme()));
    datas.append(data);

    data.type = ECropResizeType_1920_1080;
    data.name = "1920x1080";
    data.desc = "Full HD video resolution";
    data.thumbnail = QPixmap(QString(":/QtmImg/img/%1/v165/icon24_lock.svg").arg(QtmCore::Theme::currentTheme()));
    datas.append(data);

        data.type = ECropResizeType_2000_2000;
    data.name = "2000x2000";
    data.desc = "High-resolution square format";
    data.thumbnail = QPixmap(QString(":/QtmImg/img/%1/v165/icon24_lock.svg").arg(QtmCore::Theme::currentTheme()));
    datas.append(data);

    data.type = ECropResizeType_1600_1600;
    data.name = "1600x1600";
    data.desc = "High-resolution square format";
    data.thumbnail = QPixmap(QString(":/QtmImg/img/%1/v165/icon24_lock.svg").arg(QtmCore::Theme::currentTheme()));
    datas.append(data);

    data.type = ECropResizeType_2048_2048;
    data.name = "2048x2048";
    data.desc = "High-resolution square format";
    data.thumbnail = QPixmap(QString(":/QtmImg/img/%1/v165/icon24_lock.svg").arg(QtmCore::Theme::currentTheme()));
    datas.append(data);

    data.type = ECropResizeType_1000_1500;
    data.name = "1000x1500";
    data.desc = "High-resolution portrait format";
    data.thumbnail = QPixmap(QString(":/QtmImg/img/%1/v165/icon24_lock.svg").arg(QtmCore::Theme::currentTheme()));
    datas.append(data);

    data.type = ECropResizeType_1920_1080;
    data.name = "1920x1080";
    data.desc = "Full HD video resolution";
    data.thumbnail = QPixmap(QString(":/QtmImg/img/%1/v165/icon24_lock.svg").arg(QtmCore::Theme::currentTheme()));
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
    if (hover) {
        bgColor = QColor("#ffffff");
    }
    painter->setBrush(bgColor);
    painter->drawRoundedRect(bgRect, radius, radius);
    painter->setBrush(Qt::NoBrush);

    auto pixmapRect = rc.adjusted(4, 4, -4, -28);
    Painter::paintPixmap(painter, pixmapRect, data.thumbnail, 1, radius, true);

    if (selected) {
        QColor borderColor = QColor("#a070ff");
        QPen pen(borderColor);
        painter->setPen(pen);
        painter->drawRoundedRect(bgRect.adjusted(1, 1, -1, -1), radius, radius);
        painter->setPen(Qt::NoPen);
    }

    auto nameRect = bgRect;
    QColor nameColor = QColor("#000000");
    QPen pen(nameColor);
    painter->setPen(pen);
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
    if (hover) {
        bgColor = QColor("#ffffff");
    }
    painter->setBrush(bgColor);
    painter->drawRoundedRect(bgRect, radius, radius);
    painter->setBrush(Qt::NoBrush);

    auto pixmapRect = rc.adjusted(4, 4, -4, -28);
    Painter::paintPixmap(painter, pixmapRect, data.thumbnail, 1, radius, true);

    if (selected) {
        QColor borderColor = QColor("#a070ff");
        QPen pen(borderColor);
        painter->setPen(pen);
        painter->drawRoundedRect(bgRect.adjusted(1, 1, -1, -1), radius, radius);
        painter->setPen(Qt::NoPen);
    }

    auto nameRect = bgRect;
    QColor nameColor = QColor("#000000");
    QPen pen(nameColor);
    painter->setPen(pen);
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
    m_pRightWidget->setFixedWidth(256);
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
    m_pCropBtn->setChecked(true);

    rightWidgetLayout->addWidget(scaleOrSizeBtnWidget);
    rightWidgetLayout->addSpacing(4);

    //
    m_pCropAspectListView = new ListView<SCropAspectData>(this);
    m_pCropAspectListView->setFixedHeight(200);
    m_pCropAspectListView->setSpacing(0);
    m_pCropAspectListDelegate = new CropViewCropAspectListDelegate(m_pCropAspectListView);
    m_pCropAspectListView->setItemDelegate(m_pCropAspectListDelegate);
    m_pCropAspectListView->viewport()->installEventFilter(m_pCropAspectListDelegate);
    rightWidgetLayout->addWidget(m_pCropAspectListView);

    //
    m_pCropResizeListView = new ListView<SCropResizeData>(this);
    m_pCropResizeListView->setFixedHeight(200);
    m_pCropResizeListView->setSpacing(0);
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
    m_pRotateAndFlipLbl = new QLabel(this);
    m_pRotateAndFlipLbl->setObjectName("QLbl_LH16_FS12_FW4");
    rightWidgetLayout->addWidget(m_pRotateAndFlipLbl);
    rightWidgetLayout->addSpacing(4);

    //
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
    rotateBtnLayout->addWidget(m_pRotateRight90Btn);
    rotateBtnLayout->addWidget(m_pRotateLeft90Btn);
    rotateBtnLayout->addWidget(m_pFlipHorBtn);
    rotateBtnLayout->addWidget(m_pFlipVErBtn);
    rightWidgetLayout->addLayout(rotateBtnLayout);

    //
    rightWidgetLayout->addSpacing(16);

    //
    m_pApplySameCkb = new QCheckBox(this);

    //
    m_pResetBtn = new IconButton(this);
    m_pResetBtn->setFixedSize(24, 24);
    m_pResetBtn->setIconSize(24, 24);
    m_pResetBtn->setFourPixmapPath(QString(":/QtmImg/img/%1/v16/icon24/icon24_refresh2.svg").arg(QtmCore::Theme::currentTheme()));

    //
    auto applySameLayout = new QHBoxLayout();
    applySameLayout->setContentsMargins(0, 0, 0, 0);
    applySameLayout->addWidget(m_pApplySameCkb);
    applySameLayout->addStretch();
    applySameLayout->addWidget(m_pResetBtn);
    rightWidgetLayout->addLayout(applySameLayout);
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
}

void CropView::firstShow() {
    static bool firstShow = true;
    if(firstShow) {
        firstShow = false;
        loadSampleImage();
        initOutputFolderCbbItem();

        m_pCropAspectListView->changeData(getCropAspectFormatDatas());
        m_pCropResizeListView->changeData(getCropResizeFormatDatas());
        m_pCropResizeListView->setVisible(false);
        m_pImageViewer->workspace()->setCropAspectRatioMode(ImageWorkspace::CropAspectOriginal);
        m_pImageViewer->workspace()->setFitView();
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
}

void CropView::onLanguageChange() {
    m_pTitleLbl->setText(tr("Image Cropper"));
    m_pCropBtn->setText(tr("Crop"));
    m_pResizeBtn->setText(tr("Resize"));
    m_pRotateAndFlipLbl->setText(tr("Rotate and Flip"));
    m_pApplySameCkb->setText(tr("Apply same to all images"));
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
    m_pCropResizeListView->setVisible(false);
    m_pImageViewer->workspace()->setWorkspaceMode(ImageWorkspace::ModeCrop);
}

void CropView::onResizeBtnClicked() {
    m_pCropAspectListView->setVisible(false);
    m_pCropResizeListView->setVisible(true);
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