#include "freetrialtimerview.h"

FreeTrialTimerView::FreeTrialTimerView(QWidget *parent) :
    QWidget(parent) {
    createUi();
    connectSig();
    onLanguageChanged();
    timeKeeping();
    
    countdownStart(24 * 60 * 60);
}

void FreeTrialTimerView::resizeEvent(QResizeEvent *event) {
    m_pDaysLab->setGeometry(26, 42, 48, 48);
    m_pDaysTitleLab->setGeometry(76, 44, 60, 24);
    m_pFreeTrialLab->setGeometry(76, 44 + 24, 60, 18);
    m_pLoginBtn->setGeometry(8, 230 - 24 - 32, 168 - 16, 32);

    int l = 0;
    int h = 124;
    for (int i = 0; i < 8; ++i) {
        if (i == 0) {
            l += 18;
        } 
        else if (i == 1 || i == 4 || i == 7) {
            l += 14;
        } else {
            l += 20;
        }
        if (i == 2 || i == 5) {
            h = 122;
        } else {
            h = 124;
        }
        m_pDigitLabels[i]->setGeometry(l, h, 10, 16);
    }

    QWidget::resizeEvent(event);
}

void FreeTrialTimerView::createUi() {
    setObjectName("FreeTrialTimerView");
    setAttribute(Qt::WA_StyledBackground);
    setFixedSize(168, 230);

    m_pDaysLab = new QLabel(this);
    m_pDaysLab->setObjectName("FreeTrialTimerView_m_pDaysLab");
    m_pDaysTitleLab = new QLabel(this);
    m_pDaysTitleLab->setObjectName("FreeTrialTimerView_m_pDaysTitleLab");
    m_pFreeTrialLab = new QLabel(this);
    m_pFreeTrialLab->setObjectName("FreeTrialTimerView_m_pFreeTrialLab");
    m_pLoginBtn = new QPushButton(this);
    m_pLoginBtn->setObjectName("FreeTrialTimerView_m_pLoginBtn");

    m_pDaysLab->setAlignment(Qt::AlignCenter);
    m_pDaysTitleLab->setAlignment(Qt::AlignLeft);
    m_pFreeTrialLab->setAlignment(Qt::AlignCenter);

    for (int i = 0; i <= 9; ++i) {
        QString path = QString(":/qtmaterial/img/vcu/dark/trial/small-number-%1.png").arg(i);
        m_digitPixmaps[i] = QPixmap(path);
    }

    for (int i = 0; i < 8; ++i) {
        if (i == 2 || i == 5) {
            QLabel *m_pColonLab = new QLabel(this);
            m_pColonLab->setObjectName("FreeTrialTimerView_m_pColonLab");
            m_pColonLab->setFixedSize(10, 16);
            m_pColonLab->setAlignment(Qt::AlignCenter);
            m_pColonLab->setText(":");
            m_pDigitLabels[i] = m_pColonLab;
        } else {
            QLabel *m_pDigitLab = new QLabel(this);
            m_pDigitLab->setObjectName("FreeTrialTimerView_m_pDigitLab");
            m_pDigitLab->setFixedSize(10, 16);
            m_pDigitLab->setAlignment(Qt::AlignCenter);
            m_pDigitLab->setScaledContents(true);
            m_pDigitLabels[i] = m_pDigitLab;
        }
    }

    m_pLang = new LanguageFilter(this);
}

void FreeTrialTimerView::connectSig() {
    bool bConn = false;
    bConn = connect(m_pLang, &LanguageFilter::sigLanguageChange, this, &FreeTrialTimerView::onLanguageChanged);
    Q_ASSERT(bConn);
    bConn = connect(&m_pTimer, &QTimer::timeout, this, &FreeTrialTimerView::onUpdateTime);
    Q_ASSERT(bConn);
}

void FreeTrialTimerView::timeKeeping() {
    m_pDaysLab->setText("7");
}

void FreeTrialTimerView::countdownStart(int seconds) {
    m_remainingSeconds = seconds;
    updateDisplay();
    m_pTimer.start(1000);
}

void FreeTrialTimerView::updateDisplay() {
    int h = m_remainingSeconds / 3600;
    int m = (m_remainingSeconds % 3600) / 60;
    int s = m_remainingSeconds % 60;

    int digits[6] = {
        h / 10, h % 10,
        m / 10, m % 10,
        s / 10, s % 10
    };

    for (int i = 0, j = 0; i < 8; ++i) {
        if (i == 2 || i == 5) continue;
        if (m_digitPixmaps.contains(digits[j])) {
            m_pDigitLabels[i]->setPixmap(m_digitPixmaps[digits[j]]);
        }
        ++j;
    }
}

void FreeTrialTimerView::onLanguageChanged() {
    m_pDaysTitleLab->setText(tr("Day(s)"));
    m_pFreeTrialLab->setText(tr("Free Trial"));
    m_pLoginBtn->setText(tr("Login"));
}

void FreeTrialTimerView::onUpdateTime() {
    if (m_remainingSeconds > 0) {
        --m_remainingSeconds;
        updateDisplay();
    } else {
        m_pTimer.stop();
    }
}