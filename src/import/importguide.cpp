#include "import/importguide.h"
#include "core/theme.h"

#include <QFileDialog>
#include <QStandardPaths>

ImportGuide::ImportGuide(QWidget *parent, const QString &filter) :
    QWidget(parent), m_strFilter(filter) {
    createUi();
    connectSig();
    onLanguageChange();
}

void ImportGuide::setIconPixmapPath(const QString &path) {
    m_pIconBtn->setNormalPixmapPath(path);
}

void ImportGuide::setTitle(const QString &title) {
    m_pTitleLab->setText(title);
}

void ImportGuide::setDec(const QString &dec) {
    // m_pDecLab->setText(dec);
}

void ImportGuide::setImportBtnText(const QString &text) {
    m_pImportBtn->setText(text);
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
    QStringList allowedExts = extractExtensions(m_strFilter);
    for (const QUrl &url : urls) {
        // 获取文件路径
        QString filePath = url.toLocalFile();
        QFileInfo fileInfo(filePath);
        if (fileInfo.isDir()) {
            QList<QString> allFiles;
            getAllFilesInDirectory(filePath, allFiles);
            for (const QString &f : allFiles) {
                QFileInfo fi(f);
                if (allowedExts.isEmpty() || allowedExts.contains(fi.suffix().toLower())) {
                    filePaths.append(f);
                }
            }
        } else {
            if (allowedExts.isEmpty() || allowedExts.contains(fileInfo.suffix().toLower())) {
                filePaths.append(filePath);
            }
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

    m_pIconBtn = new IconButton(this);
    m_pIconBtn->setFixedSize(148, 148);
    m_pIconBtn->setIconSize(148, 148);
    m_pIconBtn->setAttribute(Qt::WA_TransparentForMouseEvents);
    m_pIconBtn->setNormalPixmapPath(QString(":/QtmImg/img/%1/v16/icon148/image148_Conversion.png").arg(QtmCore::Theme::currentTheme()));

    m_pTitleLab = new QLabel(this);
    m_pTitleLab->setObjectName("QLbl_LH20_FS14_FW4");

    // m_pDecLab = new QLabel(this);
    // m_pDecLab->setObjectName("ImportGuide_m_m_pDecLab");

    m_pImportBtn = new HorIconTextButton(this);
    m_pImportBtn->setObjectName("ImportGuide_m_pImportBtn");
    m_pImportBtn->setFixedSize(290, 48);
    m_pImportBtn->setAdjustWidth(false);
    m_pImportBtn->setFourPixmapPath(QString(":/QtmImg/img/%1/v16/icon24/icon24_add.svg").arg(QtmCore::Theme::currentTheme()));
    m_pImportBtn->setIconSize(24, 24);

    m_pMainLayout = new QVBoxLayout(this);
    m_pMainLayout->setContentsMargins(0, 0, 0, 0);
    m_pMainLayout->setSpacing(0);
    m_pMainLayout->addStretch();
    m_pMainLayout->addWidget(m_pIconBtn, 0, Qt::AlignHCenter);
    m_pMainLayout->addSpacing(10);
    m_pMainLayout->addWidget(m_pTitleLab, 0, Qt::AlignHCenter);
    m_pMainLayout->addSpacing(40);
    m_pMainLayout->addWidget(m_pImportBtn, 0, Qt::AlignHCenter);
    m_pMainLayout->addStretch();
}

void ImportGuide::connectSig() {
    connect(m_pLanguageFilter, &LanguageFilter::sigLanguageChange, this, &ImportGuide::onLanguageChange);
    connect(m_pImportBtn, &HorIconTextButton::clicked, this, &ImportGuide::openFileDialog);
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
    QStringList filePaths = QFileDialog::getOpenFileNames(this, title, directory, m_strFilter);
    if (!filePaths.isEmpty()) {
        emit sigImportFile(filePaths);
    }
}

QStringList ImportGuide::extractExtensions(const QString &filter) {
    QStringList extensions;

    // 如果包含 All Files 或者通配符 *，直接返回空表示不过滤
    if (filter.contains("*") && !filter.contains("*.")) {
        return extensions; // 空 -> 不过滤
    }

    // 多组过滤器用 ";;" 分割
    QStringList groups = filter.split(";;", Qt::SkipEmptyParts);
    for (const QString &group : groups) {
        int start = group.indexOf("(");
        int end = group.indexOf(")", start);
        if (start != -1 && end != -1 && end > start) {
            QString inside = group.mid(start + 1, end - start - 1);
            // 分割 *.png *.jpg 这种
            QStringList patterns = inside.split(QRegExp("\\s+"), Qt::SkipEmptyParts);
            for (QString p : patterns) {
                if (p.startsWith("*.")) {
                    p.remove("*.");
                }
                extensions.append(p.toLower());
            }
        }
    }
    return extensions;
}

void ImportGuide::onLanguageChange() {
    m_pTitleLab->setText(tr("Add or drag image files here to start converting"));
    // m_pDecLab->setText("");
    m_pImportBtn->setText(tr("Add Files"));
}