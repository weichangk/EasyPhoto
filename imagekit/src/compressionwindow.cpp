/*
 * @Author: weick
 * @Date: 2023-12-09 22:47:15
 * @Last Modified by: weick
 * @Last Modified time: 2024-03-24 21:00:18
 */

#include "inc/compressionwindow.h"
#include "inc/models.h"
#include "inc/signals.h"
#include "inc/settings.h"
#include "../awidget/inc/ahboxlayout.h"
#include "../awidget/inc/avboxlayout.h"
#include "../awidget/inc/ashadoweffect.h"
#include <QPainter>
#include <QPainterPath>

namespace imagecompression {
CompressionWindow::CompressionWindow(QWidget *parent) :
    ABaseWidget(parent) {
    createUi();
    sigConnect();
    changeLanguage();
}

CompressionWindow::~CompressionWindow() {
}

void CompressionWindow::changeData(QList<Data> datas) {
    m_CompressionListView->chageData(datas);
    m_AddGuideBtn->setVisible(m_CompressionListView->count() == 0);

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

void CompressionWindow::createUi() {
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setMinimumSize(800, 540);

    auto mainLayout = new AVBoxLayout(this);

    m_Topbar = new ATopbar(this);
    m_Topbar->setCloseBtnTopRight10Radius();
    mainLayout->addWidget(m_Topbar);

    auto topbarLayout = new AHBoxLayout(m_Topbar->contentWidget());
    topbarLayout->setSpacing(12);
    topbarLayout->addSpacing(12);
    auto logoLayout = new AHBoxLayout();
    logoLayout->setSpacing(4);
    m_LogoLab = new ALabel(this);
    QPixmap logo(":/agui/res/image/Compression-logo-32.png");
    m_LogoLab->setPixmap(logo);
    logoLayout->addWidget(m_LogoLab);
    m_NameLab = new ALabel(this);
    m_NameLab->setObjectName("CompressionWindow_m_NameLab");
    m_NameLab->setText("图片压缩");
    logoLayout->addWidget(m_NameLab);
    topbarLayout->addLayout(logoLayout);
    topbarLayout->addStretch();
    m_SetingBtn = new APushButton(this);
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

    auto bodyLayout = new AVBoxLayout();
    bodyLayout->setContentsMargins(25, 0, 25, 0);

    auto convertListViewBG = new AWidget(this);
    convertListViewBG->setObjectName("CompressionWindow_convertListViewBG");
    bodyLayout->addWidget(convertListViewBG);

    auto convertListViewBGLayout = new AVBoxLayout(convertListViewBG);
    m_CompressionListView = new CompressionListView(this);
    convertListViewBGLayout->addWidget(m_CompressionListView);

    mainLayout->addLayout(bodyLayout);

    auto bottomBG = new AWidget(this);
    bottomBG->setFixedHeight(64);
    auto bottomLayout = new AHBoxLayout(bottomBG);
    bottomLayout->setContentsMargins(25, 0, 25, 0);
    bottomLayout->setSpacing(12);

    m_AddFileBtn = new APushButton(this);
    m_AddFileBtn->setObjectName("FullBGButton_FS14");
    m_AddFileBtn->setFixedSize(80, 32);
    m_AddFileBtn->setText("导入");
    m_AddFileBtn->setIconSize(QSize(24, 24));
    m_AddFileBtn->setIcon(QIcon(":/agui/res/image/add-24.png"));
    bottomLayout->addWidget(m_AddFileBtn);

    m_DelFileBtn = new APushButton(this);
    m_DelFileBtn->setObjectName("FullBGButton_FS14");
    m_DelFileBtn->setFixedSize(80, 32);
    m_DelFileBtn->setText("删除");
    m_DelFileBtn->setIconSize(QSize(24, 24));
    m_DelFileBtn->setIcon(QIcon(":/agui/res/image/delete-24.png"));
    bottomLayout->addWidget(m_DelFileBtn);

    m_CheckAllBtn = new APushButton(this);
    m_CheckAllBtn->setObjectName("FullBGButton_FS14");
    m_CheckAllBtn->setFixedSize(80, 32);
    m_CheckAllBtn->setText("全选");
    m_CheckAllBtn->setIconSize(QSize(24, 24));
    bottomLayout->addWidget(m_CheckAllBtn);

    bottomLayout->addStretch();

    QString outQuality = COMPRESS_OUT_QUALITY;
    auto outQualityList = outQuality.split(' ');
    m_OutQualityCob = new AComboBox(this);
    m_OutQualityCob->setObjectName("");
    m_OutQualityCob->setFixedSize(64, 32);
    m_OutQualityCob->addItems(outQualityList);
    m_OutQualityCob->setCurrentText(QString::number(SETTINGS->compressQuality()));
    bottomLayout->addWidget(m_OutQualityCob);

    QString outFormats = COMPRESS_OUT_FORMATS;
    auto outFormatsList = outFormats.split(' ');
    m_OutFormatCob = new AComboBox(this);
    m_OutFormatCob->setObjectName("");
    m_OutFormatCob->setFixedSize(64, 32);
    m_OutFormatCob->addItems(outFormatsList);
    m_OutFormatCob->setCurrentText(SETTINGS->compressOutPath());
    bottomLayout->addWidget(m_OutFormatCob);

    m_CompressAllBtn = new APushButton(this);
    m_CompressAllBtn->setObjectName("FullBGButton_FS14");
    m_CompressAllBtn->setFixedSize(136, 32);
    m_CompressAllBtn->setText("开始压缩");
    m_CompressAllBtn->setIconSize(QSize(24, 24));
    m_CompressAllBtn->setIcon(QIcon(":/agui/res/image/refresh-24.png"));
    bottomLayout->addWidget(m_CompressAllBtn);

    mainLayout->addWidget(bottomBG);

    auto shadow = new AShadowEffect(this);

    m_AddGuideBtn = new APushButton(this);
    m_AddGuideBtn->setObjectName("CompressionWindow_m_AddGuideBtn");
    m_AddGuideBtn->setFixedSize(96 * 3, 96 * 2);
    m_AddGuideBtn->setIconSize(QSize(96, 96));
    m_AddGuideBtn->setIcon(QIcon(":/agui/res/image/image-file-add-96.png"));

    QList<Data> datas;
    updateBtnsEnabledByChangeData(datas);
    updateCheckAllBtnState(false);
}

void CompressionWindow::changeLanguage() {
}

void CompressionWindow::sigConnect() {
    connect(m_Topbar, &ATopbar::sigMin, this, [=]() { showMinimized(); });
    connect(m_Topbar, &ATopbar::sigMax, this, [=]() { showMaximized(); });
    connect(m_Topbar, &ATopbar::sigNormal, this, [=]() { showNormal(); });
    connect(m_Topbar, &ATopbar::sigClose, this, [=]() {
        close();
        emit ::Signals::getInstance()->sigGotoFunc(ImageFunc::STARTUP);
    });
    connect(m_CompressionListView, &QListView::clicked, this, [=](const QModelIndex &index) {
        auto data = index.data(Qt::UserRole).value<Data>();
        QRect rc = m_CompressionListView->visualRect(index);
        int posx = m_CompressionListView->mapFromGlobal(QCursor::pos()).x();
        int posy = m_CompressionListView->mapFromGlobal(QCursor::pos()).y();
        QRect borderRect = rc.adjusted(1 + 8, 1 + 8, -1, -1);
        QRect delIconRect = QRect(borderRect.x() + borderRect.width() - 16 - 4, borderRect.y() + 4, 16, 16);
        if (posx >= delIconRect.x() && posx <= delIconRect.x() + delIconRect.width()
            && posy >= delIconRect.y() && posy <= delIconRect.y() + delIconRect.height()) {
            emit Signals::getInstance()->sigDeleteFile(data.file_path);
        }
        auto checkedconRect = QRect(borderRect.x() + 4, borderRect.y() + 4, 16, 16);
        if (posx >= checkedconRect.x() && posx <= checkedconRect.x() + checkedconRect.width()
            && posy >= checkedconRect.y() && posy <= checkedconRect.y() + checkedconRect.height()) {
            emit Signals::getInstance()->sigSwitchChecked(data.file_path, data.is_checked);
        }
    });
    connect(m_AddFileBtn, &APushButton::clicked, this, [=]() {
        emit Signals::getInstance()->sigOpenFileDialog(this);
    });
    connect(m_AddGuideBtn, &APushButton::clicked, this, [=]() {
        emit Signals::getInstance()->sigOpenFileDialog(this);
    });
    connect(m_DelFileBtn, &APushButton::clicked, this, [=]() {
        emit Signals::getInstance()->sigDeleteByChecked();
    });
    connect(m_CheckAllBtn, &APushButton::clicked, this, [=]() {
        bool oldChecked = "true" == m_CheckAllBtn->property("is-checked").toString();
        bool newChecked = !oldChecked;
        emit Signals::getInstance()->sigCheckedAll(newChecked);
        updateCheckAllBtnState(newChecked);
    });
    connect(m_CompressAllBtn, &APushButton::clicked, this, [=]() {
        emit Signals::getInstance()->sigStatus(Status::START);
        compressStart();
    });
    connect(Signals::getInstance(), &Signals::sigStatusToView, this, &CompressionWindow::compressStatus);
}

void CompressionWindow::paintEvent(QPaintEvent *event) {
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

void CompressionWindow::resizeEvent(QResizeEvent *event) {
    ABaseWidget::resizeEvent(event);
    m_AddGuideBtn->setGeometry((width() - m_AddGuideBtn->width()) / 2, (height() - m_AddGuideBtn->height()) / 2, m_AddGuideBtn->width(), m_AddGuideBtn->height());
}

void CompressionWindow::updateCheckAllBtnState(bool checked) {
    m_CheckAllBtn->setProperty("is-checked", checked ? "true" : "false");
    m_CheckAllBtn->setIcon(QIcon(checked ? ":/agui/res/image/checked-24.png" : ":/agui/res/image/unchecked-24.png"));
}

void CompressionWindow::updateBtnsEnabledByChangeData(QList<Data> datas) {
    auto allUnchecked = [](const QList<Data> &datas) {
        return std::all_of(datas.begin(), datas.end(), [](const Data &cd) {
            return cd.is_checked == false;
        });
    };

    bool isEnabled = datas.count() > 0;
    m_CheckAllBtn->setEnabled(isEnabled);

    isEnabled = !allUnchecked(datas);
    m_DelFileBtn->setEnabled(isEnabled);
    m_CompressAllBtn->setEnabled(isEnabled);
}

void CompressionWindow::compressStatus(Status state) {
    switch (state) {
    case Status::NONE:
        break;
    case Status::START:
        compressStart();
        break;
    case Status::FINISHED:
        compressFinished();
        break;
    case Status::CANCEL:
        compressCancel();
        break;
    }
}

void CompressionWindow::compressStart() {
}

void CompressionWindow::compressFinished() {
}

void CompressionWindow::compressCancel() {
}
} // namespace imagecompression