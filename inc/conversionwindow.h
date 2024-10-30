#pragma once
#include "inc/conversionlistview.h"
#include "inc/models.h"
#include "component/navbarwidget.h"
#include "component/topbarwidget.h"
#include "component/canmovewidget.h"
#include "component/rotatingpixmapwidget.h"

#include <QPushButton>
#include <QLabel>
#include <QWidget>
#include <QListWidget>
#include <QStyledItemDelegate>

namespace imageconversion {
class ConversionFormatPopup;
class ConversionWindow : public QWidget {
    Q_OBJECT
public:
    explicit ConversionWindow(QWidget *parent = 0);
    ~ConversionWindow();
    void changeData(QList<Data> datas);
    void addFormatListWidgetItems(const QStringList items);
    void changeConvToBtnText(const QString format);

protected:
    void createUi();
    void sigConnect();
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    void updateCheckAllBtnState(bool checked);
    void updateBtnsEnabledByChangeData(QList<Data> datas);
    void formatPopup();
    void showConverting(bool isShow);
    void convStatus(Status state);
    void startConv();
    void finishedConv();
    void cancelConv();

private:
    TopbarWidget *m_Topbar = 0;
    QLabel *m_LogoLab = 0;
    QLabel *m_NameLab = 0;
    QPushButton *m_SetingBtn = 0;
    ConversionListView *m_ConversionListView = 0;
    QPushButton *m_AddGuideBtn = 0;
    QPushButton *m_ConvToBtn = 0;
    QPushButton *m_AddFileBtn = 0;
    QPushButton *m_DelFileBtn = 0;
    QPushButton *m_CheckAllBtn = 0;
    QPushButton *m_ConvAllBtn = 0;
    WidgetWithRotatingItem *m_ConvertingWidget = 0;
    ConversionFormatPopup *m_FormatPopup = 0;
};

class ConversionFormatPopup : public QWidget {
    Q_OBJECT
public:
    explicit ConversionFormatPopup(QWidget *parent = 0);
    void addFormatListWidgetItems(const QStringList items);

protected:
    void paintEvent(QPaintEvent *event) override;

protected:
    void createUi();
    void sigConnect();

private:
    void formatItemClicked(QListWidgetItem *item);

private:
    QListWidget *m_FormatListWidget = 0;
};

class ConversionFormatListDelegate : public QStyledItemDelegate {
    Q_OBJECT
public:
    explicit ConversionFormatListDelegate(QObject *parent);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};
} // namespace imageconversion