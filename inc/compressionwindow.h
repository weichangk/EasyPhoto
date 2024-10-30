#pragma once
#include "component/navbarwidget.h"
#include "component/topbarwidget.h"
#include "component/canmovewidget.h"
#include "component/rotatingpixmapwidget.h"
#include "compressionlistview.h"
#include "models.h"

#include <QPushButton>
#include <QLabel>
#include <QCombobox>
#include <QWidget>
#include <QListWidget>
#include <QStyledItemDelegate>


namespace imagecompression {
class CompressionFormatPopup;
class CompressionWindow : public QWidget {
    Q_OBJECT
public:
    explicit CompressionWindow(QWidget *parent = 0);
    ~CompressionWindow();
    void changeData(QList<Data> datas);

protected:
    void createUi();
    void sigConnect();
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    void updateCheckAllBtnState(bool checked);
    void updateBtnsEnabledByChangeData(QList<Data> datas);
    void compressStatus(Status state);
    void compressStart();
    void compressFinished();
    void compressCancel();

private:
    TopbarWidget *m_Topbar = 0;
    QLabel *m_LogoLab = 0;
    QLabel *m_NameLab = 0;
    QPushButton *m_SetingBtn = 0;
    CompressionListView *m_CompressionListView = 0;
    QPushButton *m_AddGuideBtn = 0;
    QPushButton *m_AddFileBtn = 0;
    QPushButton *m_DelFileBtn = 0;
    QPushButton *m_CheckAllBtn = 0;
    QPushButton *m_CompressAllBtn = 0;
    QComboBox *m_OutQualityCob = 0;
    QComboBox *m_OutFormatCob = 0;
};
} // namespace imagecompression