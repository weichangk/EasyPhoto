#include "command/funcnavigatecommand.h"
#include <QDebug>

FuncNavigateCommand::FuncNavigateCommand(const QString &prev, const QString &curr, std::function<void(QString)> func) :
    m_strPreviousPage(prev), m_strCurrentPage(curr), m_pNavigateFunc(func) {
    setText(QString("Navigate: %1 → %2").arg(prev, curr)); // 设置命令描述
}

void FuncNavigateCommand::undo() {
    qDebug() << "Undo: Navigating back to" << m_strPreviousPage;
    m_pNavigateFunc(m_strPreviousPage);
}

void FuncNavigateCommand::redo() {
    qDebug() << "Redo: Navigating to" << m_strCurrentPage;
    m_pNavigateFunc(m_strCurrentPage);
}
