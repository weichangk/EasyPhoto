/*
 * @Author: weick
 * @Date: 2023-12-09 22:00:37
 * @Last Modified by: weick
 * @Last Modified time: 2023-12-10 00:23:09
 */

#pragma once
#include "../awidget/inc/apushbutton.h"
#include "../awidget/inc/alabel.h"
#include "../agui/inc/abasewidget.h"
#include "../agui/inc/anavbarwidget.h"
#include "../agui/inc/atopbar.h"
#include "../agui/inc/acanmovewidget.h"
#include "../agui/inc/arotatingpixmapwidget.h"
#include "inc/compressionlistview.h"
#include "inc/models.h"
#include <QListWidget>
#include <QStyledItemDelegate>

class CompressionFormatPopup;
class CompressionWindow : public ABaseWidget {
    Q_OBJECT
public:
    explicit CompressionWindow(QWidget *parent = 0);
    ~CompressionWindow();
    void changeData(QList<CompressionData> datas);
    void addFormatListWidgetItems(const QStringList items);
    void changeConvToBtnText(const QString format);

protected:
    void createUi() override;
    void changeLanguage() override;
    void sigConnect() override;
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    void updateCheckAllBtnState(bool checked);
    void updateBtnsEnabledByChangeData(QList<CompressionData> datas);
    void formatPopup();
    void showConverting(bool isShow);
    void convStatus(Models::ConvStatusEnum state);
    void startConv();
    void finishedConv();
    void cancelConv();

private:
    ATopbar *m_Topbar = 0;
    ALabel *m_LogoLab = 0;
    ALabel *m_NameLab = 0;
    APushButton *m_SetingBtn = 0;
    CompressionListView *m_CompressionListView = 0;
    APushButton *m_AddGuideBtn = 0;
    APushButton *m_ConvToBtn = 0;
    APushButton *m_AddFileBtn = 0;
    APushButton *m_DelFileBtn = 0;
    APushButton *m_CheckAllBtn = 0;
    APushButton *m_ConvAllBtn = 0;
    AWidgetWithRotatingItem *m_ConvertingWidget = 0;
    CompressionFormatPopup *m_FormatPopup = 0;
};

class CompressionFormatPopup : public ABaseWidget {
    Q_OBJECT
public:
    explicit CompressionFormatPopup(QWidget *parent = 0);
    void addFormatListWidgetItems(const QStringList items);

protected:
    void paintEvent(QPaintEvent *event) override;

protected:
    void createUi() override;
    void changeLanguage() override;
    void sigConnect() override;

private:
    void formatItemClicked(QListWidgetItem *item);

private:
    QListWidget *m_FormatListWidget = 0;
};

class CompressionFormatListDelegate : public QStyledItemDelegate {
    Q_OBJECT
public:
    explicit CompressionFormatListDelegate(QObject *parent);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};
