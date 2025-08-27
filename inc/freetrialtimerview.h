#pragma once
#include "globalview.h"

#include <QTimer>

using namespace QtmFilter;

class FreeTrialTimerView : public QWidget {
    Q_OBJECT
public:
    explicit FreeTrialTimerView(QWidget *parent = nullptr);
    ~FreeTrialTimerView() override {
    }

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    void createUi();
    void connectSig();
    void timeKeeping();

    void countdownStart(int seconds);
    void updateDisplay();

private slots:
    void onLanguageChanged();
    void onUpdateTime();

private:
    QLabel *m_pDaysLab = nullptr;
    QLabel *m_pDaysTitleLab = nullptr;
    QLabel *m_pFreeTrialLab = nullptr;
    QPushButton *m_pLoginBtn = nullptr;

    QMap<int, QPixmap> m_digitPixmaps;
    QLabel *m_pDigitLabels[8];
    QTimer m_pTimer;
    int m_remainingSeconds = 0;

    LanguageFilter *m_pLang = nullptr;
};