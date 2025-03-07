#include "command/funcnavigatecommand.h"
#include <QDebug>

FuncNavigateCommand::FuncNavigateCommand(EFunc prev, EFunc curr, std::function<void(EFunc)> func) :
    m_ePreviousFunc(prev), m_eCurrentFunc(curr), m_pNavigateFunc(func) {
    setText(QString("Navigate: %1 → %2").arg(prev, curr)); // 设置命令描述
}

void FuncNavigateCommand::undo() {
    qDebug() << "Undo: Navigating back to" << m_ePreviousFunc;
    m_pNavigateFunc(m_ePreviousFunc);
}

void FuncNavigateCommand::redo() {
    qDebug() << "Redo: Navigating to" << m_eCurrentFunc;
    m_pNavigateFunc(m_eCurrentFunc);
}
