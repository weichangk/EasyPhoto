#pragma once
#include "globalview.h"

class ModelCard : public QWidget {
    Q_OBJECT
public:
    explicit ModelCard(QWidget *parent = nullptr);
    ~ModelCard() override {
    }

    void setInfo(const QString &name, const QString &desc, const QPixmap &beforeThumb, const QPixmap &afterThumb);

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    QLabel *m_pNameLbl = nullptr;
    QLabel *m_pDescLbl = nullptr;
    QLabel *m_pBeforeThumbLbl = nullptr;
    QLabel *m_pAfterThumbLbl = nullptr;
    QLabel *m_pBeforeLbl = nullptr;
    QLabel *m_pAfterLbl = nullptr;
    QWidget *m_pThumbFrame = nullptr;
};