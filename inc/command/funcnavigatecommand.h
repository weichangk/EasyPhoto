#pragma once
#include <QUndoCommand>

class FuncNavigateCommand : public QUndoCommand {
public:
    FuncNavigateCommand(const QString &prev, const QString &curr, std::function<void(QString)> func);
    void undo() override;
    void redo() override;

private:
    QString m_strPreviousPage;
    QString m_strCurrentPage;
    std::function<void(QString)> m_pNavigateFunc;
};