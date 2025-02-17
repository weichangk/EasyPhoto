#include "importguide.h"

#include <QFileDialog>
#include <QStandardPaths>

ImportGuide::ImportGuide(QWidget *parent) :
    QWidget(parent) {
    createUi();
    connectSig();
    onLanguageChange();
}

void ImportGuide::mousePressEvent(QMouseEvent *event) {
    QWidget::mousePressEvent(event);
    if (event->button() == Qt::LeftButton) {
    }
}

void ImportGuide::mouseReleaseEvent(QMouseEvent *event) {
    QWidget::mouseReleaseEvent(event);
    if (event->button() == Qt::LeftButton) {
        openFileDialog();
    }
}

// 拖拽进入事件
void ImportGuide::dragEnterEvent(QDragEnterEvent *event) {
    // 检查拖动的数据类型是否包含文件
    if (event->mimeData()->hasUrls()) {
        // 接受拖拽
        event->acceptProposedAction();
    } else {
        // 如果不是文件或文件夹，忽略拖拽
        event->ignore();
    }
}

// 放下文件或文件夹时的事件
void ImportGuide::dropEvent(QDropEvent *event) {
    const QList<QUrl> urls = event->mimeData()->urls();
    QStringList filePaths;
    for (const QUrl &url : urls) {
        // 获取文件路径
        QString filePath = url.toLocalFile();
        QFileInfo fileInfo(filePath);
        if (fileInfo.isDir()) {
            QList<QString> allFiles;
            getAllFilesInDirectory(filePath, allFiles);
            filePaths.append(allFiles);
        } else {
            filePaths.append(filePath);
        }
    }
    if (!filePaths.isEmpty()) {
        emit sigImportFile(filePaths);
    }
    // 处理完后接受该事件
    event->acceptProposedAction();
}

void ImportGuide::createUi() {
    setObjectName("ImportGuide");
    setAttribute(Qt::WA_StyledBackground);
    // setFixedSize(470, 193);

    // 启用拖放支持
    setAcceptDrops(true);

    QFont iconFont = Font::getIconFont(":/font/iconfont.ttf");

    m_pImportIconLab = new VectorLabel(this);
    m_pImportIconLab->setObjectName("VectorLabel_Size24");
    m_pImportIconLab->setFont(iconFont);
    m_pImportIconLab->setText(QChar(0xe665));
    m_pImportIconLab->setFixedSize(150, 100);

    m_pImportDecLab = new QLabel(this);

    m_pDividingLine = createDividingLine();
    m_pDividingLine->setVisible(false);

    m_pMainLayout = new QVBoxLayout(this);
    m_pMainLayout->setContentsMargins(0, 0, 0, 0);
    m_pMainLayout->setSpacing(0);
    m_pMainLayout->addSpacing(36);
    m_pMainLayout->addWidget(m_pImportIconLab, 0, Qt::AlignHCenter);
    m_pMainLayout->addSpacing(20);
    m_pMainLayout->addWidget(m_pImportDecLab, 0, Qt::AlignHCenter);
    m_pMainLayout->addSpacing(20);
    m_pMainLayout->addWidget(m_pDividingLine, 0, Qt::AlignHCenter);
}

void ImportGuide::connectSig() {
    connect(m_pLanguageFilter, &LanguageFilter::sigLanguageChange, this, &ImportGuide::onLanguageChange);
}

QWidget *ImportGuide::createDividingLine() {
    QWidget *dividingLine = new QWidget(this);
    dividingLine->setAttribute(Qt::WA_StyledBackground);
    dividingLine->setObjectName("ImportGuide_DividingLine");
    dividingLine->setFixedHeight(1);
    return dividingLine;
}

void ImportGuide::getAllFilesInDirectory(const QString &dirPath, QList<QString> &files) {
    QDir dir(dirPath);

    // 获取当前目录下所有文件和子目录（不包括.和..）
    QFileInfoList fileList = dir.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);

    // 遍历文件和目录
    foreach (const QFileInfo &info, fileList) {
        if (info.isDir()) {
            // 如果是子目录，则递归
            getAllFilesInDirectory(info.absoluteFilePath(), files);
        } else if (info.isFile()) {
            // 如果是文件，则加入到文件列表
            files.append(info.absoluteFilePath());
        }
    }
}

void ImportGuide::openFileDialog() {
    QString title = tr("Open");
    QString directory = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    QStringList filePaths = QFileDialog::getOpenFileNames(this, title, directory, "All Files (*)");
    if (!filePaths.isEmpty()) {
        emit sigImportFile(filePaths);
    }
}

void ImportGuide::onLanguageChange() {
    m_pImportDecLab->setText(tr("Output format:"));
}