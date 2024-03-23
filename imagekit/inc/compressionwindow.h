/*
 * @Author: weick
 * @Date: 2023-12-09 22:00:37
 * @Last Modified by: weick
 * @Last Modified time: 2024-03-23 22:08:37
 */

#pragma once
#include "../awidget/inc/apushbutton.h"
#include "../awidget/inc/alabel.h"
#include "../awidget/inc/acombobox.h"
#include "../agui/inc/abasewidget.h"
#include "../agui/inc/anavbarwidget.h"
#include "../agui/inc/atopbar.h"
#include "../agui/inc/acanmovewidget.h"
#include "../agui/inc/arotatingpixmapwidget.h"
#include "compressionlistview.h"
#include "models.h"
#include <QListWidget>
#include <QStyledItemDelegate>

class CompressionFormatPopup;
class CompressionWindow : public ABaseWidget {
    Q_OBJECT
public:
    explicit CompressionWindow(QWidget *parent = 0);
    ~CompressionWindow();
    void changeData(QList<imagecompression::Data> datas);

protected:
    void createUi() override;
    void changeLanguage() override;
    void sigConnect() override;
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    void updateCheckAllBtnState(bool checked);
    void updateBtnsEnabledByChangeData(QList<imagecompression::Data> datas);
    void compressStatus(imagecompression::Status state);
    void compressStart();
    void compressFinished();
    void compressCancel();

private:
    ATopbar *m_Topbar = 0;
    ALabel *m_LogoLab = 0;
    ALabel *m_NameLab = 0;
    APushButton *m_SetingBtn = 0;
    CompressionListView *m_CompressionListView = 0;
    APushButton *m_AddGuideBtn = 0;
    APushButton *m_AddFileBtn = 0;
    APushButton *m_DelFileBtn = 0;
    APushButton *m_CheckAllBtn = 0;
    APushButton *m_CompressAllBtn = 0;
    AComboBox *m_OutQualityCob = 0;
    AComboBox *m_OutFormatCob = 0;
};
